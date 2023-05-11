Alguns exercicios feitos por mim do livro da disciplina.
CAPS FEITOS 4, 5, 8, 9

uma de escalonamento, uma de threads vs processos, uma de semaforos, uma de impasse

Cap 4
1.
time sharing -> cada tarefa recebe uma "fatia" de tempo - chamado de quantum - e apos esse tempo expirar ela da lugar para outra tarefa.
isso previne que uma tarefa domine completamente a CPU permitindo que varias tarefas rodem "simultaneamente" no computador.

2.
pela prioridade da tarefa.
(nao faco ideia dessa)

3.nao entendi nada do diagrama

4.
N: nova, P: pronta, E: executando, S: suspensa, T: terminada
E->P sim [quando ocorre a preempcao por tempo]
E->S sim [quando a aplicacao espera algo (sleep)]
S->E nao ocorre [ela vai de supensa para fila de prontos]
P->N nao ocorre
S->T nao ocorre normalmente [a nao ser que alguma tarefa externa termine com ela (kill por exemplo)]
E->T sim [quando ela termina sua execucao]
N->S nao ocorre
P->S nao ocorre

5.
[N] O código da tarefa está sendo carregado.
[P] A tarefas são ordenadas por prioridades.
[E] A tarefa sai deste estado ao solicitar uma operação de entrada/saída. (nao entendi ela sai do pronto e vai para o suspenso)
[T] Os recursos usados pela tarefa são devolvidos ao sistema.
[P] A tarefa vai a este estado ao terminar seu quantum.
[P] A tarefa só precisa do processador para poder executar.
[S] O acesso a um semáforo em uso pode levar a tarefa a este estado.
[E] A tarefa pode criar novas tarefas.
[E] Há uma tarefa neste estado para cada processador do sistema.
[S] A tarefa aguarda a ocorrência de um evento externo.

Cap 5
1. O TCB - Task Control Block eh uma struct que contem informacoes relevantes para a exeucacao de uma tarefa.
Seu ID, sua prioridade, contexto, etc sao armazenadas no TCB.

4.
thread - do ingles fio - e uma forma de implementar tarefa. uma thread e um fio de execucao que ao juntar com outras threads formam uma aplicacao maior
uma das usabilidades sao nos processos, que podem criar varias threads e executar mais de um fluxo de codigo por vez

5.
Vantagens de threads em relacao a procesos:
+criar uma thread eh mais barato (ocupa menor espaco) e eh mais rapida (mais simples no geral)
+permite a comunicacao de tarefas no mesmo processo - comunicacao entre duas threads eh facil e rapida
Desvantagens
-uma thread em uma aplicacao pode danificar o processo inteiro se algum problema ocorrer (um erro no processo fica contido nele)

Geralmente as aplicaçoes usam um hibrido (varios processos com varias threads)

6.
suponha que as threads A e B façam parte do processo P
a thread A calcula a nota dos alunos em uma disciplina e a thread B calcula a media total da sala
logicamente a thread B nao consegue executar sem os dados gerados pela thread A, logo multi-thread nesse caso nao seria melhor que a aplicacao sequencial

7.
(N:1) Tem a implementação mais simples, leve e eficiente.
(N:M) Multiplexa os threads de usuário em um pool de threads de núcleo.
(1:1) Pode impor uma carga muito pesada ao núcleo.
(N:1) Não permite explorar a presença de várias CPUs pelo mesmo processo.
(N:M) Permite uma maior concorrência sem impor muita carga ao núcleo.
(1:N) Geralmente implementado por bibliotecas.
(1:1) É o modelo implementado no Windows NT e seus sucessores.
(1:N) Se um thread bloquear, todos os demais têm de esperar por ele.
(1:1) Cada thread no nível do usuário tem sua correspondente dentro do núcleo.
(N:M) É o modelo com implementação mais complexa.


Cap 8 - Comunicaçao entre tarefas
1)
a)
vantagens da comunicaçao bloqueante:
+mais facil de implementar
+uma aplicaçao pode depender dos dados para continuar o processamento, assim bloqueala deve pode ser o certo a melhor opcao
desvantagens da comunicacao bloqueante
-uma tarefa pode ficar desnecessariamente travada

vantagens da comunicacao nao bloqueante
+impede que as tarefas fiquem paradas

desvantagens da comunicacao nao bloqueante
-e quase impossivel duas tarefas estarem (enviando ou recebendo) dados ao mesmo tempo, logo raramente ocorreria a comunicacao

b)
vantagens de canal com buffering
+fica a cargo do RECEPTOR decidir quando as informacoes serao processadas
+possibilita a comunicacao indireta (atraves de um canal com capacidade maior que 0)


2)
Na comunicaçao assincrona (nao bloqueante) eh necessario um buffer entre eles (com capacidade maior que 0). Sem o canal de comunicacao fica inviavel a comunicacao entre eles

Ja na comunicacao sincrona (bloqueante), um canal pode ter o buffer igual a zero, ja que ambas as tarefas estarao sincronizadas (criando o "rendez-vous")

3)
a) Sim
 Em algums casos pode ocorrer as comunicacoes intersistemas, e um buffer (que agiria como um canal) eh indispensavel para essa comunicacao.

b) Nao
Canal com capacidade infinita sao usados para projetar algoritmos e na pratica so existem canais com capacidade finita.

c) Nao
na comunicacao direta o emissor envia dados diretamente para o receptor, sem o intermedio de um canal - o que transformaria a comunicacao em uma comunicacao indireta

d) nao entendi

e) Sim
O kernel e responsavel pela transferencia de mensagens de tarefas

5)
a) Nao
na semi-bloqueante o emissor espera um tempo - "timeout" - se o receptor nao pediu nenhuma informacao continua com sua execucao.
a comunicacao que a tarefa espera um tempo indeterminado eh a comunicacao nao bloqueante.

b) Nao
na comunicacao nao-bloqueante ela nao espera, se nao houverem dados para receber, ela continua seu fluxo de execucao

c) Sim

d) Nao
na comunicacao sincronia (bloqueante) o emissor espera ate que o receptor consuma os dados que ele ira transmitir

Cap 9

1.
mq_send: "caso a fila esteja cheia, o emissor fica bloqueado ate alguma mensagem seja retirada da fila"
logo: comunicacao bloqueante ou sincrona

mq_receive: "caso a fila esteja vazia, receptor e bloqueade ate que surja uma mensage"
logo: tambem eh bloqueante

2.
Os pipes sao uma forma de comunicacao sincrona com canal de buffer (finito).

suponha a execucao do seguinte comando

ls | grep codigo_aleatorio.c

as duas tarefas "ls" e "grep" sao criadas e adicionados a fila de prontos, porem a tarefa "grep" nao tera nenhum dado para executar sua rotina, logo fica bloqueada ate que o "ls" termine sua execucao

3. Nao ha nenhuma sincronia na comunicacao de memoria compartilhada

4.
A) Nao
As filas de mensagens POSIX tem canais com capacidade finita (comunicacao indireta)

B) Nao ou Sim n sei
A memoria compartilhada nao possui qualquer mecanismo de sincronizacao entre as tarefas
Por isso eh necessario a adicao de mecanismos de controle da area (semaforos por exemplo) para garantir consistencia

D) Sim
A area de memoria compartilhada eh na RAM

E) Nao
O pipe eh uma comunicacao 1:1

F) Sim
Nesses casos o custo de comunicar sempre passando pelo kernel fica muito alto (um grande numero de chamadas de sistema) logo, a comunicacao sem o intermedio - ficando somente para os processos - eh proveitoso nesses casos.


























