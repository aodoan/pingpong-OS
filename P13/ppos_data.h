/*
* Código desenvolvido para disciplina de Sistemas Operacionais 
* pelo aluno Claudinei Aparecido Alduan Filho GRR20203920
*/

// PingPongOS - PingPong Operating System
// Prof. Carlos A. Maziero, DINF UFPR
// Versão 1.5 -- Março de 2023

// Estruturas de dados internas do sistema operacional

#ifndef __PPOS_DATA__
#define __PPOS_DATA__

#include <ucontext.h>		// biblioteca POSIX de trocas de contexto
#include <signal.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//#include "ppos_disk.h"

/* default value for stacksize */
#define STACKSIZE 	64*1024

/* upper and lower bound of priorities */
#define UPPER_PRIO 	20
#define LOWER_PRIO -20

/* default id of main */
#define ID_MAIN 	0

/* define the initial value of id */
#define INITIAL_ID 	0

/* status of the task */
#define READY 		'R'
#define TERMINATED 	'T'
#define SUSPENDED 	'S'
#define RUNNING 	'L'

/* nature of task */
#define USER 10
#define SYSTEM 20

/* inital amount of quantum that a task receive */
#define INITAL_QUANTUM 20

/* value of quanta (in ms) */
#define QUANTA 1000


// Estrutura que define um Task Control Block (TCB)
typedef struct task_t
{
	/* campos fornecidos pelo professor */ 
 	struct task_t  *prev, *next;	// ponteiros para usar em filas
  	int 			id;				// identificador da tarefa
  	ucontext_t 		context;		// contexto armazenado da tarefa
  	short 			status;			// pronta, rodando, suspensa, ...
/* ------------------------------------------------------------------------------------------------ */

	/* campos adicionados */
	/* priority related fields */
  	int static_prio; 				// prioridade estatica
  	int dinamic_prio; 				// prioridade dinamica 	
  							/* time related fields */
  	int quanta_left; 		// total de quantum que falta para tarefa deixar a CPU
  	int task_nature; 		// indica se a tarefa eh do sistema ou do usuario 
    int exit_code; 			// indica o exit code passado para tarefa terminar em task_exit
    int wait_id; 			// indica a id da tarefa que ela esta esperando terminar
	int atomic; 			// se for setado como 1 a tarefa nao sofre interrupcao
    unsigned int wake_time;
	unsigned int flag; 				// ZERO indica que nao ha tarefas esperando por ela, UM contrario
    unsigned int birth_time; 		// indica o momento em que a tarefa foi criada
  	unsigned int death_time; 		// indica o momento em que a tarefa foi encerrada
  	unsigned int running_time; 		// indica o tempo que a tarefa gastou sendo processada
  	unsigned int activations; 		// indica o numero de vezes que a tarefa ganhou o processador
	int f;
} task_t ;

// estrutura que define um semáforo
typedef struct
{
	int value; 		// campo que indica a quantidade de vagas do semaforo
	task_t* queue; 	// fila de tarefas 
	int destroyed; 	//setado para 1 quando o semaforo for destruido
} semaphore_t ;

// estrutura que define um mutex
typedef struct
{
  // preencher quando necessário
} mutex_t ;

// estrutura que define uma barreira
typedef struct
{
  // preencher quando necessário
} barrier_t ;

// estrutura que define uma fila de mensagens
typedef struct
{
	int max_msgs; 		// tamanho da fila
	int msg_size;		// tamanho (em bytes) de cada mensagem da fila
	int atual; 			// indica quantas mensagems atualmente estao na fila
	void *buffer; 		// ponteiro para armazenar o buffer

	semaphore_t vagas;  // semaforo que controla as vagas
	semaphore_t items;  // semaforo que controla os items (msg_atual)
	semaphore_t buf; 	// semaforo (mutex) que controla o acesso ao buffer

} mqueue_t ;



void diskDriverBody(void * args);
void wakeTask(task_t * task);
void suspend();
void readyTask(task_t *task);
void imprime_lista_prontos();
void insert_ready_queue(task_t *task);
#endif
