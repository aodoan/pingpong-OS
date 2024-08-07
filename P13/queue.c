/*
* Código desenvolvido para disciplina de Sistemas Operacionais 
* pelo aluno Claudinei Aparecido Alduan Filho GRR20203920
*/
#include <stdio.h>
#include "queue.h"
int queue_size(queue_t *queue){
    //start the counter
    int counter = 0;
    if(queue){
        queue_t *aux = queue;
        //iterates until get back to the first element
        do{
            counter++;
            aux = aux->next;
        }while(aux != queue);
    
    }
    return counter;
}


//------------------------------------------------------------------------------
// Percorre a fila e imprime na tela seu conteúdo. A impressão de cada
// elemento é feita por uma função externa, definida pelo programa que
// usa a biblioteca. Essa função deve ter o seguinte protótipo:
//
// void print_elem (void *ptr) ; // ptr aponta para o elemento a imprimir

void queue_print(char *name, queue_t *queue, void print_elem(void *))
{
    printf("%s: ", name);
    if(queue){
        queue_t *aux = queue;
        printf("[");
        do{
            print_elem(aux);
            
            aux = aux->next;
            if(aux != queue)
                printf(" ");
        }while(aux != queue);
        printf("]\n");
    }
    else{
        printf("[]\n");
    }
}

//------------------------------------------------------------------------------
// Insere um elemento no final da fila.
// Condicoes a verificar, gerando msgs de erro:
// - a fila deve existir
// - o elemento deve existir
// - o elemento nao deve estar em outra fila
// Retorno: 0 se sucesso, <0 se ocorreu algum erro
int queue_append (queue_t **queue, queue_t *elem){
    //check if the element exists
    if(elem == NULL){
        fprintf(stderr, "ERRO: o elemento nao existe.\n");
        return 1;
    }

    //check if the element is in another queue
    if(elem->prev != NULL || elem->next != NULL){
        fprintf(stderr, "ERRO: o elemento esta em outra fila.\n");
        return 1;
    }

    queue_t *cmp = *queue;
    //if the queue is empty
    if(*queue == NULL){
        *queue = elem;
        elem->next = elem;
        elem->prev = elem;

        return 0;
    }

    //the queue is not empty
    //has just one element
    else if(cmp == cmp->next){
        queue_t *first = *queue;
        first->next = elem;
        first->prev = elem;
        elem->prev = first;
        elem->next = first;

        return 0;
    }
    //has more than one element
    else{  
        queue_t *aux = *queue;
        queue_t *last = aux->prev;
        last->next = elem;
        elem->prev = last;
        elem->next = aux;
        aux->prev = elem;

        return 0;
    }


    return 0; 
}



//------------------------------------------------------------------------------
// Remove o elemento indicado da fila, sem o destruir.
// Condicoes a verificar, gerando msgs de erro:
// - a fila deve existir
// - a fila nao deve estar vazia
// - o elemento deve existir
// - o elemento deve pertencer a fila indicada
// Retorno: 0 se sucesso, <0 se ocorreu algum erro

int queue_remove(queue_t **queue, queue_t *elem){
    //check if the element exists
    if(elem == NULL){
        fprintf(stderr, "ERRO: o elemento nao existe.\n");
        return 1;
    }

    queue_t *aux = *queue;
    queue_t *first = *queue;
    queue_t *next, *prev;
    //iterates the queue trying to find the element
    if(aux != elem){
        while(aux != elem){
            aux = aux->next;
            //if reaches the first element again
            //that means that the element is not in the queue
            if(aux == first){
                fprintf(stderr, "ERRO: O elemento nao pertence a fila indicada\n");
                return 1;
            }
        }
    }
    //if the element was found
    if(aux == elem){
        //the queue has just one element
        if(elem->next == elem && elem->prev == elem){
            (*queue) = NULL;
            elem->next = NULL;
            elem->prev = NULL;
            return 0;
        }
        //the element is the first in queue (has to change the pointer of **queue)
        if(*queue == elem){
            *queue = elem->next;
        }

        //change the other queue elements
        next = elem->next;
        prev = elem->prev;
        next->prev = prev;
        prev->next = next;
        elem->next = NULL;
        elem->prev = NULL;
        return 0;

    }
    return 1;
}