/*
* Código desenvolvido para disciplina de Sistemas Operacionais 
* pelo aluno Claudinei Aparecido Alduan Filho GRR20203920
*/

#include <stdio.h>
#include <stdlib.h>
#include "ppos.h"
#include "queue.h"
#include <unistd.h>

/* struct to save the current task */
task_t *CurrentTask;
/* struct to save the main task */
task_t MainTask;
task_t *MTask = &MainTask;
/* struct to save the dispatcher task */
task_t dispat;
task_t *Dispat = &dispat;
/* saves the context of the main */
ucontext_t ContextMain;

/* time related structs UNIX SIGNAL */
struct sigaction action ;
struct itimerval timer;

/* timer global variable */
unsigned int TIME;

/* declaration of dispatcher */
void dispatcher(void* arg);

/* declatarion of routine */
void routine (int signum);
void awake_tasks_time();
/* variable to store the next id */
long int id;

/* longint to store the amount of tasks running */
long int userTasks;

/* queue of ready tasks */
task_t* queueR = NULL;

/* queue of suspended tasks */
task_t* queueS = NULL;

/* print the id, static and dinamic prioirity of a task (USED ONLY IN DEBUG MODE) */
void print_elem(void* ptr){
        task_t *elem = ptr;
    printf("(%i)->[%i]->[%i]", elem->id, elem->static_prio, elem->dinamic_prio);
}


/* print the id, all tasks (USED ONLY IN DEBUG MODE) */
void print_elem_id(void* ptr){
        task_t *elem = ptr;
    printf("(%i) ", elem->id);
}
void ppos_init(){
    #if defined DEBUG
    printf("ppos_init: iniciando as variaveis\n");
    #endif

    TIME = 0;
    action.sa_handler = routine;
    action.sa_flags = 0;

    if (sigaction (SIGALRM, &action, 0) < 0){
        perror ("Erro em sigaction: ") ;
        exit (1) ;
    }

    // ajusta valores do temporizador
    timer.it_value.tv_usec = QUANTA;      // primeiro disparo, em micro-segundos
    timer.it_value.tv_sec = 0;      // primeiro disparo, em segundos
    timer.it_interval.tv_usec = QUANTA;   // disparos subsequentes, em micro-segundos
    timer.it_interval.tv_sec = 0;   // disparos subsequentes, em segundos

    // arma o temporizador ITIMER_REAL
    if (setitimer (ITIMER_REAL, &timer, 0) < 0)
    {
        perror ("Erro em setitimer: ") ;
        exit (1) ;
    }

/*
    MainTask.next = NULL;
    MainTask.prev = NULL;
    MainTask.atomic = 0;
    MainTask.flag = 0;
*/  
    /* set the id of main task as ID_MAIN */
    MTask->id = ID_MAIN;
    
    /* define the id as the initial value (to be used in the next task) */
    id = 0;

    /* set the main as current task */
    CurrentTask = MTask;
    /*
    queue_append((queue_t **)&queueR, (queue_t*) CurrentTask);
    userTasks++;
    */
    task_init(MTask, NULL, NULL);
    /* create the dispatcher task and remove it from the ready queue */
    task_init(Dispat, dispatcher, NULL);
    queue_remove((queue_t **)&queueR, (queue_t*)Dispat);
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
        task->atomic = 0;
        task->flag = 0;
        task->id_espera = -1;
        /* set the birth time of the task */
        task->birth_time = TIME;
        task->running_time = 0;
        task->activations = 0;

        /* fields to manage the context of the task */
        task->context.uc_link = 0;
        task->context.uc_stack.ss_flags = 0;
        task->context.uc_stack.ss_sp = stack;
        task->context.uc_stack.ss_size = STACKSIZE;

        /* create the context of the task */
        if(start_func != NULL){
            makecontext(&task->context, (void*)(* start_func), 1, arg);
            task->id = id;
            
        }
        else{
            task->context = ContextMain;
            task->id = 0;
        }
        id++;
        /* fields to manage the TCB queue */
        task->next = NULL;
        task->prev = NULL;

        /* set the status to READY */
        task->status = READY;

        /* set the id of the task and increment to use in the next task */
        
        
        task->static_prio = 0;
        task->dinamic_prio = 0;

        /* if the task is not the dispatcher */
        if(task == Dispat)
            task->task_nature = SYSTEM;
        else
            task->task_nature = USER;

        /* set the initial amount of quanta */
        task->quanta_left = INITAL_QUANTUM;

        #ifdef DEBUG
        printf("task_init: iniciada a tarefa %i\n", task->id);
        #endif
        

        /* increment the number of user tasks and the id for the next task */
        userTasks++;
        

        /* insert on the ready queue */
        
        queue_append((queue_t **)&queueR, (queue_t*) task);
        
        /* return the id of current task */
        return task->id;
    }
    fprintf(stderr, "ERROR: creating stack\n");
    return 0;
}

int task_switch (task_t *task){
    /* increasce the number of times that the task won the CPU */
    CurrentTask->activations++;

    task_t *temp = CurrentTask;
    #ifdef DEBUG
    printf("task_switch: trocando contexto %i -> %i\n", temp->id, task->id);
    #endif
    CurrentTask = task;
    swapcontext(&temp->context, &task->context);
    return 0;
}
     
void awake_tasks_id (int id){
    task_t *aux = queueS, *aux2;
    int f = 0;
    do{        
        if(aux->id_espera == id){
            aux2 = aux;

            if(aux == aux->next){
                f = 1;
            }
            aux->id_espera = 0;
            aux = aux->next;
            
            #ifdef DEBUG
            printf("acordando a tarefa %i\n", aux->id);
            #endif
            task_resume(aux2, (task_t **) &queueS);
            
        }
        else
            aux = aux->next;

    }while(aux != queueS && f == 0);
    
}
void task_exit (int exit_code) {
    
    /* check if any other tasks must be awaken */
    if(CurrentTask->flag == 1){
        awake_tasks_id(CurrentTask->id);
    }
    CurrentTask->exit_code = exit_code;
    CurrentTask->death_time = TIME;
    printf("Task %d exit: execution time %d ms, processor time %d ms, %d activations\n"
    , CurrentTask->id, CurrentTask->death_time-CurrentTask->birth_time, CurrentTask->running_time,CurrentTask->activations);
    task_t* temp = CurrentTask;
    temp->status = TERMINATED;
    #ifdef DEBUG
    printf("task_exit: tarefa %i sendo encerrada, com exit_code %i \n", temp->id, exit_code);
    #endif
    userTasks--;

    /* if the current task is the dispatcher, back to main */
    if(CurrentTask == Dispat){
        /* free the alocated memory for the dispatcher */
        
        exit(0);
        
    }
    /* else, goes to dispatcher */
    else{
        task_switch(Dispat);
    }
}

/* return the id of the current task*/
int task_id(){
    return CurrentTask->id;
}

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
        /* awake all the tasks on the suspended queue */
        awake_tasks_time();
        
        /* verifies if there any task on the ready queue */
        if(queueR != NULL){
            /* get the task with higher priority */
            task_t *task = scheduler();
    
            if(task != NULL){
                /* set the status as RUNNING */                
                task->status = RUNNING;
                
                /* set the quanta */
                task->quanta_left = INITAL_QUANTUM;
                
                /* switch to the task */
                task_switch(task);

                /* free the memory if the task was terminated */     
                if(task->status == TERMINATED){
                    free(task->context.uc_stack.ss_sp);

                }
        
            }     
        }
        else
            /* if there are not task in the ready queue, sleep */
            sleep(100);
    }
    
    task_exit(0);
}

void task_yield(){
    /* insert the task in the ready queue */
    queue_append((queue_t**)&queueR, (queue_t *)CurrentTask);
    CurrentTask->status = READY;

    #ifdef DEBUG
    printf("task_yield: a tarefa %i chamou a CPU\n", CurrentTask->id);
    #endif
    /* goes to the dispatcher */
    task_switch(Dispat);
    
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

/* its called in every tick of the clock */
void routine (int signum){
    /* increment the global variable TIME */
    TIME++;
    CurrentTask->running_time++;
    /* if is a system task, ignores it */
    if(CurrentTask->task_nature != SYSTEM && CurrentTask->atomic == 0 ){
        CurrentTask->quanta_left--;
        /* the task spent all the quantas */
        if(CurrentTask->quanta_left <= 0){
            /* insert the task in ready queue */
            queue_append((queue_t**)&queueR, (queue_t *)CurrentTask);
            
            /* set the status of the task to ready */
            CurrentTask->status = READY;
            
            /* switch to the dispatcher */
            task_switch(Dispat);
        }
    }
}

unsigned int systime (){
    return TIME;
}

void task_suspended (task_t **queue){
    /* if the task is in the ready queue, remove it */
    if(CurrentTask->status == READY){     
        queue_remove((queue_t **)&queueR, (queue_t*) CurrentTask);
    }
    
    /* set the task status as SUSPENDED*/
    CurrentTask->status = SUSPENDED;

    
    /* insert on the new queue */
    queue_append((queue_t **)&queueS, (queue_t*) CurrentTask);
    #ifdef DEBUG
    queue_print ("task_suspend: Fila de suspensos: ", (queue_t*) queueS, print_elem_id) ;
    #endif
    /* returns to dispatcher*/
    task_switch(Dispat);
}

void task_resume (task_t *task, task_t **queue){
    #ifdef DEBUG
    printf("task_resume: tirando a tarefa %i %i ", task->id, task->wake_time);
    queue_print ("Fila de suspensos: ", (queue_t*) queueS, print_elem_id) ;
    #endif
    /* remove from the suspended queue */
    queue_remove((queue_t**) &queueS, (queue_t*) task);
    /* insert on the ready queue */
    queue_append((queue_t **) &queueR, (queue_t*) task);

    /* set the status back to READY */
    task->status = READY;
    /* set the atomic flag as 1 */
    task->atomic = 0;
}


int task_wait(task_t *task){
    /* check if the task exists */
    if(task == NULL)
        return -1;

    if(CurrentTask->status != SUSPENDED && task->status != TERMINATED){
        CurrentTask->atomic = 1;
        /* saves the id to be awake after */
        CurrentTask->id_espera = task->id;
        task->flag = 1;
        /* SUSPEND THE TASK */
        task_suspended(&queueS);
        CurrentTask->atomic = 0;
        /* the task has already stopped */
        return task->exit_code; 
    }
    /* default error return value */
    return -1;
}

void task_sleep(int t){
    /* prevents that the task is preempted before goes to suspended */
    CurrentTask->atomic = 1;

    CurrentTask->wake_time = TIME + t;
    task_suspended(&queueS); 
}

void awake_tasks_time(){
    task_t *aux = queueS, *aux2;
    int f = 0;
    if(queueS){
        do{
            if(aux->wake_time <= TIME && aux->id_espera < 0){
                aux2 = aux;
                if(aux == aux->next){
                    f = 1;
                }
                aux = aux->next;
                task_resume(aux2, &queueS);
            }
            else
                aux = aux->next;
        }while(aux != queueS && f == 0);
    }
}

