#include <stdio.h>
#include <stdlib.h>
#include "ppos.h"
#include "queue.h"

/* default value for stacksize */
#define STACKSIZE 64*1024

/* upper and lower bound of priorities */
#define UPPER_PRIO 20
#define LOWER_PRIO -20

/* default id of main */
#define ID_MAIN 0

/* status of the task */
#define READY 'R'
#define TERMINATED 'T'
#define SUSPENDED 'S'

/* struct to save the current task */
task_t *CurrentTask;
/* struct to save the main task */
task_t MainTask;
/* struct to save the dispatcher task */
task_t dispat;
/* saves the context of the main */
ucontext_t ContextMain;


void dispatcher(void* arg);

/* variable to store the next id */
long int id;

/* longint to store the amount of tasks running */
long int userTasks;

/* queue of ready tasks */
task_t* queueR = NULL;


/* print the id, static and dinamic prioirity of a task (USED ONLY IN DEBUG MODE) */
void print_elem(void* ptr){
    task_t *elem = ptr;
    printf("(%i)->[%i]->[%i]", elem->id, elem->static_prio, elem->dinamic_prio);
}

void ppos_init(){
    #if defined DEBUG
    printf("ppos_init: iniciando as variaveis\n");
    #endif


    MainTask.next = NULL;
    MainTask.prev = NULL;

    
    /* set the id of main task as ID_MAIN */
    MainTask.id = ID_MAIN;
    
    /* increment id (to be used in the next task) */
    id = 0;
    id++;

    /* set the main as current task */
    CurrentTask = &MainTask;

    /* create the dispatcher task and remove it from the ready queue */
    task_init(&dispat, dispatcher, NULL);
    queue_remove((queue_t **)&queueR, (queue_t*)&dispat);
    userTasks--;

    /* desativa o buffer da saida padrao (stdout), usado pela função printf */
    setvbuf(stdout, 0, _IONBF, 0);
}

int task_init (task_t *task, void  (*start_func)(void *), void   *arg) {
    if(task == NULL)
        return 0;

    /* create the context */
    getcontext(&task->context);
    char *stack;
    stack = malloc(STACKSIZE);
    if(stack){
        /* fields to manage the context of the task */
        task->context.uc_link = 0;
        task->context.uc_stack.ss_flags = 0;
        task->context.uc_stack.ss_sp = stack;
        task->context.uc_stack.ss_size = STACKSIZE;
        /* create the context of the task */
        makecontext(&task->context, (void*)(* start_func), 1, arg);
        
        /* fields to manage the TCB queue */
        task->next = NULL;
        task->prev = NULL;

        /* set the status to READY */
        task->status = READY;

        /* set the id of the task and increment to use in the next task */
        task->id = id;
        task->static_prio = 0;
        task->dinamic_prio = 0;

        #ifdef DEBUG
        printf("task_init: iniciada a tarefa %i\n", task->id);
        #endif
        

        /* increment the number of user tasks and the id for the next task */
        userTasks++;
        id++;

        /* insert on the ready queue */
        queue_append((queue_t **)&queueR, (queue_t*) task);
        
        /* return the id of current task */
        return task->id;
    }
    fprintf(stderr, "ERROR: creating stack\n");
    return 0;
}

int task_switch (task_t *task){
    task_t *temp = CurrentTask;
    #ifdef DEBUG
    printf("task_switch: trocando contexto %i -> %i\n", temp->id, task->id);
    #endif
    CurrentTask = task;
    swapcontext(&temp->context, &task->context);
    return 0;
}

void task_exit (int exit_code) {
    task_t* temp = CurrentTask;
    temp->status = TERMINATED;
    #ifdef DEBUG
    printf("task_exit: tarefa %i sendo encerrada, com exit_code %i \n", temp->id, exit_code);
    #endif
    /* if the current task is the dispatcher, back to main */
    if(CurrentTask == &dispat){
        /* free the alocated memory for the dispatcher */
        free(dispat.context.uc_stack.ss_sp);
        task_switch(&MainTask);
    }
    /* else, goes to dispatcher */
    else{
        task_switch(&dispat);
    }
}

int task_id(){
    return CurrentTask->id;
}

/* FCS scheduler
task_t* scheduler(){
    return queueR;
}*/


task_t* scheduler(){
    /* pointer to iterate the whole queue */
    task_t* aux = queueR;
    task_t* nextTask = NULL;
    
    /* variable that store the max priority (to compare) */
    int min = UPPER_PRIO + 1;

    do{
        /* the dinamic priority is lower than the min */
        if(aux->dinamic_prio < min){
            min = aux->dinamic_prio;
            nextTask = aux;
        }
        /* if the dinamic priority is the same, compare the static priority */
        else if(aux->dinamic_prio == min && aux->static_prio < nextTask->static_prio){
            min = aux->dinamic_prio;
            nextTask = aux;
        }
        aux = aux->next;
    }while (aux != queueR);

    #ifdef DEBUG
    queue_print ("scheduler: Fila de prontos", (queue_t*) queueR, print_elem) ;
    printf("scheduler: A tarefa escolhida foi: ");
    print_elem(nextTask);
    printf("\n");
    #endif

    /* found the task with higher priority (lower number) */

    /* set the dinamic priority of nextTask and remove it from the queue */
    nextTask->dinamic_prio = nextTask->static_prio;
    queue_remove((queue_t**) &queueR, (queue_t*)nextTask);
    
    /* lower the dinamic priority of all other tasks */
    /* check if there are more tasks */
    if(queueR){
        aux = queueR;    
        do{
            /* decrease the dinamic priority of all tasks */
            aux->dinamic_prio--;

            /* prevents that the priority is lower than -20 */
            if(aux->dinamic_prio < LOWER_PRIO)
                aux->dinamic_prio = LOWER_PRIO;

            aux = aux->next;
        }while (aux != queueR);
    }
    return nextTask;
} 

void dispatcher(void* arg){
    /* while has tasks to execute */
    while(userTasks > 0){
        /* get the task with higher priority */
        task_t *task = scheduler();
        if(task != NULL){

            /* decrease the number of ready tasks */
            userTasks--;
            task_switch(task);
                
            /* free the memory if the task was terminated */     
            if(task->status == TERMINATED){
                free(task->context.uc_stack.ss_sp);

            }
        
        }           
    }
    task_exit(0);
}

void task_yield(){
    /* check if the task that called task_yield is the main task */
    if(CurrentTask->id != 0){
        queue_append((queue_t**)&queueR, (queue_t *)CurrentTask);
        userTasks++;
        CurrentTask->status = READY;
    }

    #ifdef DEBUG
    printf("task_yield: a tarefa %i chamou a CPU\n", CurrentTask->id);
    #endif
    /* goes to the dispatcher */
    task_switch(&dispat);
    
}

void task_setprio (task_t *task, int prio){
    /* verifies if prio is in the range */
    if(prio <= 20 && prio >= -20){
        task->static_prio = prio;
        task->dinamic_prio = prio;
    }
    /* if not, set to zero*/
    else{
        task->static_prio = 0;
        task->dinamic_prio = 0;
    }
}

/* return the static priority of task*/
int task_getprio (task_t *task){
    if(task)
        return task->static_prio;
    /* if task is NULL, return the priority of the current task */
    return CurrentTask->static_prio;
}


