// PingPongOS - PingPong Operating System
// Prof. Carlos A. Maziero, DINF UFPR
// Versão 1.4 -- Janeiro de 2022

// interface do gerente de disco rígido (block device driver)

#ifndef __DISK_MGR__
#define __DISK_MGR__

#include "ppos.h"
// estruturas de dados e rotinas de inicializacao e acesso
// a um dispositivo de entrada/saida orientado a blocos,
// tipicamente um disco rigido.
typedef struct request_t{
	struct request_t *prev, *next;
	int CMD;
	int block;
	void *buffer;
}request_t;

// estrutura que representa um disco no sistema operacional
typedef struct
{
	int num_blocks;
	int block_size;	
	int sinal; //quando ta em 1, indica que recebeu um sinal
	int livre; //quando ta em 1, indica que o disco esta livre
	task_t* queue; 	//fila de tarefas
	request_t* rqueue; //fila de pedidos
	semaphore_t acesso; //semaforo para acesso ao disco 
  // completar com os campos necessarios
} disk_t ;



// inicializacao do gerente de disco
// retorna -1 em erro ou 0 em sucesso
// numBlocks: tamanho do disco, em blocos
// blockSize: tamanho de cada bloco do disco, em bytes
int disk_mgr_init (int *numBlocks, int *blockSize) ;

// leitura de um bloco, do disco para o buffer
int disk_block_read (int block, void *buffer) ;

// escrita de um bloco, do buffer para o disco
int disk_block_write (int block, void *buffer) ;

void diskDriverBody(void * args);
#endif