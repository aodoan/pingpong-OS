/*
  minha solucao p/ o problema proposto:
  Suponha três robôs (Bart, Lisa, Maggie), cada um controlado por sua própria
  thread. Você deve escrever o código das threads de controle, usando semáforos
  para garantir que os robôs se movam sempre na sequência Bart → Lisa →
  Maggie → Lisa → Bart → Lisa → Maggie → · · ·, um robô de cada vez. Use
  a chamada move() para indicar um movimento do robô. Não esqueça de
  definir os valores iniciais das variáveis e/ou dos semáforos utilizados. Soluções envolvendo espera ocupada (busy wait) não devem ser usadas.

 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>
#include <stdlib.h>


pthread_mutex_t bart, lisa, maggie;


void *Bart(void *id){
  while(1){
    pthread_mutex_lock(&bart);
    printf("Bart\n");
    
    pthread_mutex_unlock(&lisa);
  }
}

void *Lisa(void *id){
  while(1){
    pthread_mutex_lock(&lisa);
    printf("Lisa\n");
    pthread_mutex_unlock(&maggie);

    pthread_mutex_lock(&lisa);
    printf("Lisa\n");
    pthread_mutex_unlock(&bart);
  }
}
void *Maggie(void *id){
  while(1){
    pthread_mutex_lock(&maggie);
    printf("Maggie\n");
    
    
    pthread_mutex_unlock(&lisa);
  }
}


int main (int argc, char *argv[])
{
  pthread_mutex_init(&bart, NULL);
  pthread_mutex_lock(&lisa);
  pthread_mutex_lock(&maggie);

  pthread_t a, b, c;
  long i = 0;
   
  pthread_create(&a, NULL, Bart, (void *) i);
  pthread_create(&b, NULL, Lisa, (void *) i);
  pthread_create(&c, NULL, Maggie, (void *) i);
  
  printf ("Main: fim\n") ;
  pthread_exit (NULL) ;
}
