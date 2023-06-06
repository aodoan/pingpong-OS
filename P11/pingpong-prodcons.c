// PingPongOS - PingPong Operating System
// Prof. Carlos A. Maziero, DINF UFPR
// Versão 1.5 -- Março de 2023

// Teste de semáforos (light)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ppos.h"
#include "queue.h"
/* define o limite do numero maximo */
#define UPPER_BOUND 100
task_t      p1, p2, p3, c1, c2;
semaphore_t s_buffer, s_item, s_vaga;


int buffer[5];
int qtd_item;
void insere_item(int item){
	buffer[qtd_item] = item;
	qtd_item++;	
}

int retira_item(){
	int i = buffer[0];
	for(int i = 1; i < qtd_item; i++)
		buffer[i-1] = buffer[i];
	qtd_item--;
	return i;
}

void produtor(void *arg){
   	int item;
	while(1){
	    task_sleep(100);
		item = rand() % UPPER_BOUND;

		sem_down(&s_vaga);
		
		sem_down(&s_buffer);
		insere_item(item);
		sem_up(&s_buffer);
		printf("%s %i\n", (char *) arg, item);
		sem_up(&s_item);
   }
}

void consumidor(void *arg){
	int item;
	while(1){
		sem_down(&s_item);

		sem_down(&s_buffer);
		item = retira_item();
		sem_up(&s_buffer);
		
		sem_up(&s_vaga);

		printf("%s %i\n", (char *) arg, item);
		task_sleep(100);
	}
}

int main (int argc, char *argv[])
{
	printf ("main: inicio\n") ;

	ppos_init () ;
	srand(time(NULL));
	qtd_item = 0;
	//mutex
	sem_init (&s_buffer, 1);
   	//item produzido
	sem_init (&s_item, 0);
	//vagas disponiveis
	sem_init (&s_vaga, 5);

	task_init (&p1, produtor, "p1 produziu") ;
   	task_init (&p2, produtor, "p2 produziu") ;
   	task_init (&p3, produtor, "p3 produziu") ;
   	task_init (&c1, consumidor, "\t\t\t\tc1 consumiu") ;
	task_init (&c2, consumidor, "\t\t\t\tc2 consumiu") ;
	printf ("main: fim\n") ;
	task_exit (0) ;
   /*
   printf ("main: inicio\n") ;

   ppos_init () ;

   // inicia semaforos
   sem_init (&s1, 1) ;
   sem_init (&s2, 0) ;

   // inicia tarefas
   task_init (&a1, TaskA, "A1") ;
   task_init (&a2, TaskA, "\tA2") ;
   task_init (&b1, TaskB, "\t\t\tB1") ;
   task_init (&b2, TaskB, "\t\t\t\tB2") ;

   // aguarda a1 encerrar
   task_wait (&a1) ;

   // destroi semaforos
   sem_destroy (&s1) ;
   sem_destroy (&s2) ;

   // aguarda a2, b1 e b2 encerrarem
   task_wait (&a2) ;
   task_wait (&b1) ;
   task_wait (&b2) ;

   printf ("main: fim\n") ;
   
   task_exit (0) ;
   */

}