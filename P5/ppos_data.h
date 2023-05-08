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
#define RUNNING 'L'

/* nature of task */
#define USER 10
#define SYSTEM 20

/* inital amount of quantum that a task receive */
#define INITAL_QUANTUM 20

// Estrutura que define um Task Control Block (TCB)
typedef struct task_t
{
  struct task_t *prev, *next ;		// ponteiros para usar em filas
  int id ;				// identificador da tarefa
  ucontext_t context ;			// contexto armazenado da tarefa
  short status ;			// pronta, rodando, suspensa, ...
  
  //CAMPOS ADICIONADOS
  int static_prio; // prioridade estatica
  int dinamic_prio; // prioridade dinamica
  int quanta_left; // total de quantum que falta para tarefa deixar a CPU
  int task_nature; // indica se a tarefa eh do sistema ou do usuario 
  // ... (outros campos serão adicionados mais tarde)
} task_t ;

// estrutura que define um semáforo
typedef struct
{
  // preencher quando necessário
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
  // preencher quando necessário
} mqueue_t ;

#endif
