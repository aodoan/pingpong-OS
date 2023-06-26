#include "ppos_disk.h"
#include "disk.h"
#include "ppos.h"
#include "queue.h"

disk_t disk;
struct sigaction daction;

task_t diskT;
task_t *taskDisk = &diskT;

void diskHandler(int signum){

    disk.sinal = 1;
    if(taskDisk->status == SUSPENDED)
        wakeTask(taskDisk);
}

int disk_mgr_init(int *numBlocks, int *blockSize){
    int nBlocks, bSize;

    
    nBlocks = disk_cmd(DISK_CMD_DISKSIZE, 0, 0);
    bSize = disk_cmd(DISK_CMD_BLOCKSIZE, 0, 0);
    
    /* error reading the disk */
    if(nBlocks < 0 || bSize < 0){
        return -1;
    }
    *numBlocks = nBlocks;
    *blockSize = bSize;

    task_init(taskDisk, diskDriverBody, NULL);
    
    /* set the initial values of disk */
    disk.block_size = bSize;
    disk.num_blocks = nBlocks;
    disk.queue = NULL;
    disk.rqueue = NULL;
    disk.sinal = 0;
    disk.livre = 1;
    sem_init(&(disk.acesso), 1);

    /* set the signal action */
    daction.sa_handler = diskHandler;
    daction.sa_flags = 0;
    
    if (sigaction(SIGUSR1, &daction, 0) < 0)
    {
        perror("Erro em sigaction: ");
        exit(1);
    }


    return 0;
}

int disk_block_read (int block, void *buffer){
    if(sem_down(&disk.acesso) == -1)
        return -1;
    /* create the request and add to the queue */
    request_t *request = malloc(sizeof(request_t));
    /* error alocating memory*/
    if(request == NULL)
        return -1;
    request->CMD = DISK_CMD_READ;
    request->block = block;
    request->buffer = buffer;
    request->prev = NULL; request->next = NULL;

    queue_append((queue_t **)&disk.rqueue, (queue_t*) request);
    /* if the task disk is suspended, wake the task */
    if(taskDisk->status == SUSPENDED){
        wakeTask(taskDisk);
    }


    if(sem_up(&disk.acesso) == -1)
        return -1;
    task_suspend(&(disk.queue));

    task_yield();
    return 0;
}

int disk_block_write (int block, void *buffer){
    if(sem_down(&disk.acesso) == -1)
        return -1;

    /* create the request and add to the queue */
    request_t *request = malloc(sizeof(request_t));
    /* error alocating memory*/
    if(request == NULL)
        return -1;
    request->CMD = DISK_CMD_WRITE;
    request->block = block;
    request->buffer = buffer;
    /* fields for manage the queue */
    request->prev = NULL; request->next = NULL;

    queue_append((queue_t **)&(disk.rqueue), (queue_t*) request);
    /* if the task disk is suspended, wake the task */
    if(taskDisk->status == SUSPENDED){
        wakeTask(taskDisk);
    }

    if(sem_up(&disk.acesso) == -1)
        return -1;
        
    task_suspend(&(disk.queue));
    task_yield();
    return 0;
}




void diskDriverBody(void * args){
    task_t *task;
    request_t *request;
    while(1){       
        if(sem_down(&disk.acesso) == -1)
            exit(0);
        if(disk.sinal == 1){
            disk.sinal = 0;
            disk.livre = 1;
            task = disk.queue;
           
            task_resume(task, &(disk.queue));
        }

        if(disk.livre && ((disk.rqueue) != NULL)){
            request = disk.rqueue;
            queue_remove((queue_t **)&disk.rqueue, (queue_t*) request);
            /* error accessing the disk */
            if(disk_cmd(request->CMD, request->block, request->buffer) < 0)
                exit(0);
            disk.livre = 0;
            free(request);
        }  
        if(sem_up(&disk.acesso) == -1)
            exit(0);
        /* suspend the task */
        suspend();
    }
}
