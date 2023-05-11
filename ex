Alguns exercicios feitos por mim do livro da disciplina.
CAPS FEITOS 1, 2, 4, 5, 6, 7, 8, 9, 10


uma de escalonamento, uma de threads vs processos, uma de semaforos, uma de impasse

Cap 1 - Conceitos Basicos
1)
1- fornecer as aplicacoes uma forma de acesso aos dipositivos de baixo nivel de uma forma homogenea:
Suponha que uma aplicacao e feita para o computador A e acessa um HD para seu funcionamento. Se a tarefa for para outro computador, digamos o B, ela funcionara igual, mesmo se o computador usar um SSD por exemplo.
O SO abstrai o acesso de dados para as aplicacoes.

2 - gerenciar multiplas tarefas e garantir o funcionamento "simultaneo" delas

2)
Para garantir que a mesma aplicacao funcione em diferentes computadores.
Alem do mais o desenvolvedor nao se preocupa com as tecnologias em baixo nivel do computador, ja que o sistema operacional abstrai essas questoes.

3)
vantagens: permitir o uso de diversas tarefas simultaneamente no processador. Interface grafica, editor de texto, navegador sao tarefas diferentes que nos computadores de hoje em dia sao executadas simultaneamente. Se nao tivessemos esse conceito somente uma tarefa poderia ser executada por vez.
desafios: implementar o conceito e gerenciar as diversas tarefas; garantir que as tarefas recebam um tempo justo para rodarem (isto eh, uma tarefa prioritaria e de alta importancia para o computador execute ao inves de tarefas de menos importancia)

4)
um sistema de tempo-real nao eh um sistema onde as respostas sao ultra-rapidas, mas sim seu comportamento eh previsivel. Eh necessario que o melhor e o pior caso respondam dentro de um tempo limite.
nesse sistema o tempo eh essencial, seja em uma aplicacao hard real-time system (como o funcionamento de motoroes de aviao) ou de (soft real-time system) um reprodutor de musicas por exemplo.

5)
distribuído (D), multi-usuário (M), desktop (K), servidor (S), embarcado (E) ou de
tempo-real (T):
[T] Deve ter um comportamento temporal previsível, com prazos de resposta
claramente definidos.
[S] Sistema operacional usado por uma empresa para executar seu banco de
dados corporativo.
[ ] São tipicamente usados em telefones celulares e sistemas eletrônicos
dedicados.
[D] Neste tipo de sistema, a localização física dos recursos do sistema computacional é transparente para os usuários.
[M] Todos os recursos do sistema têm proprietários e existem regras controlando
o acesso aos mesmos pelos usuários.
[E] A gerência de energia é muito importante neste tipo de sistema.
[K] Sistema que prioriza a gerência da interface gráfica e a interação com o
usuário.
[S] Construído para gerenciar de forma eficiente grandes volumes de recursos.
[K] O MacOS X é um exemplo típico deste tipo de sistema.
[S] São sistemas operacionais compactos, construídos para executar aplicações
específicas sobre plataformas com poucos recursos.

6)
A) Sim
O sistema deve responder de forma previsivel, nao o mais rapido possivel

B) Sim

C) Nao
Esse eh o sistema distribuído

D) Nao
Esse eh o sistema dekstop.

E) Sim

Cap 2 -
1) O que diferencia o núcleo do restante do sistema operacional?
Resposta:
O nucleo do sistema operacional eh onde esta o coracao do sistema. O que contem nele depende do tipo do sistema.
Em sistemas mono-liticos o nucleo eh o sistema operacional inteiro. Ja nos sistemas microkernel o nucleo contem somente os mecanismos, onde as politicas sao implementadas fora dele (como aplicativos no user-space)

2) Seria possível construir um sistema operacional seguro usando um processador
que não tenha níveis de privilégio? Por quê?
Resposta: Nao.
Um sistema operacional sem nenhum nivel de privilegio significa que qualquer codigo executando no user space tem controle total sobre a maquina, logicamente gerando um sistema facilmente manipulavel.

3)  Os processadores da família x86 possuem dois bits para definir o nível de
privilégio, resultando em 4 níveis distintos. A maioria dos sistemas operacionais
para esses processadores usam somente os níveis extremos (0 e 3, ou 002 e 112).
Haveria alguma utilidade para os níveis intermediários?
Resposta:
Nao. A maioria do sistemas so usam os niveis extremos. Uma aplicacao precisa rodar em nivel usuario ou nivel kernel, logo o intermediario nao faria diferenca.


4) Quais as diferenças entre interrupções, exceções e traps?
Resposta:
Interrupcao: MECANISMO que interrompe a execucao de uma tarefa
exceções: erros em que acontecem na execucao e atraves da interrupcao sao desviados para areas de codigo especializadas em lidar com exceções.
traps: n tem nada no livro sobre

5) O comando em linguagem C fopen é uma chamada de sistema ou uma função
de biblioteca? Por quê?
Resposta: fopen eh uma funcao de bilbioteca que realiza uma chamada de sistema.
Assim como o malloc() que eh uma funcao e realiza a system call brk() para aumentar a pilha do programa.

6) A operação em modo usuário permite ao processador executar somente parte
das instruções disponíveis em seu conjunto de instruções. Quais das seguintes
operações não deveriam ser permitidas em nível usuário? Por quê?
Resposta:

(a) Ler uma porta de entrada/saída
Nao deve ser permitida. Esse acesso deve ser feito por drivers que rodam em modo privilegiado

(b) Efetuar uma divisão inteira
Pode

(c) Escrever um valor em uma posição de memória
Pode desde que a posicao seja valida

(d) Ajustar o valor do relógio do hardware
Nao. Somente o kernel pode fazer isso

(e) Ler o valor dos registradores do processador
Sim.

(f) Mascarar uma ou mais interrupções
Nao.

7) Considerando um processo em um sistema operacional com proteção de
memória entre o núcleo e as aplicações, indique quais das seguintes ações do
processo teriam de ser realizadas através de chamadas de sistema, justificando
suas respostas:
(a) Ler o relógio de tempo real do hardware.
Systemcall. A aplicacao nao tem acesso.

(b) Enviar um pacote através da rede.
Systemcall. A aplicacao precisa enviar para a placa de rede, onde o nucleo administra

(c) Calcular uma exponenciação.
Nao. O processador oferece instrucoes que nao precisam de systemcall para realizar uma exponenciação.

(d) Preencher uma área de memória do processo com zeros.
Nao entendi. Mas acho que nao precisa de systemcall.

(e) Remover um arquivo do disco.
Precisa de systemcall.


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
N: nova, P: pronta, E: executando, S: suspensa, T: terminada
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

Cap 6 -
1. round-robin eh uma forma de escalonar com interrupcoes. Cada tarefa recebe uma fatia de processamento e apos o fim desse tempo da lugar a outra tarefa.
exemplo de RR.
    |
    |
    |
    |
ta  |+++++++++----------++++++++++
    |
tb  |   ------++++++++++----------
    |

as tarefas ta e tb recebem um quantum de 10 ticks (quando a tarefa esta executando "+") e volta para fila de prontos esperando CPU "-" quando seu quantum acaba.

3. aging eh a tecnica de "envelhecer" a tarefa.
Suponha que em um sistema de prioridades tenha uma tarefa com uma prioridade muito baixa. Dependendo do sistema essa tarefa pode levar um tempo muito grande para rodar (conhecido como "starvation"), assim a tecnica de aging aumenta a prioridade dinamica das tarefas, fazendo com que tarefas menos prioritarias possam executar ocasionalmente.

4.
trocar o pdprox = max N (pdi) por -> pdprox = min N(pdi)
e trocar o pdi = pdi + aging_factor por -> pdi = pdi - aging_factor (ou usar um aging_factor negativo)

fazer 5 e 6 no papel

Cap 7
1.
inversao de prioridade
Suponha que uma tarefa A precisa de um dado para continuar a execucao de uma tarefa B.
No nosso caso a tarefa A tem prioridade muito alta e B nao.
heranca de prioridade (solucao da inversao de prioridade)
Como A precisa de B, B herda a prioridade de A.




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


Cap 10 -
1. condicoes de disputa.
Vamos supor que uma aplicacao eh um jogo interativo com inimigos.
Os inimigos sao lancados em threads A e B e ambos podem atacar o personagem principal. Digamos que ambos os inimigos acertem o golpe simultaneamente, ocorreria uma condicao de disputa em cima da variavel "vida" do personagem.

thread A                       thread B
|                                |
|                                |
+ comeca o ataque HP = 20        |
-                                |
-                                + comeca o ataque HP = 20
-                                -
-                                -
-                                -
+ HP = 15 termina o atk          -
|                                -
|                                + HP = 15 termina o atk
|                                |
|                                |
|                                |

O personagem tem vida igual a 20 e cada ataque diminui 5 pontos de vida.
As threads tentaram acessar o dado ao mesmo tempo, sem nenhum mecanismo de sincronia, logo as operacoes foram de coordenaçao causaram um erro (HP = 15 ao inves do HP = 10)

2.
A) Nao
Ao inibir interrupcoes a preempcao por tempo deixa de funcionar (entre outros mecanismos que gerenciam a tarefa). E pode em sistemas multiprocessados, duas tarefas que acessam a mesma regiao critica podem entrar ao mesmo tempo em dois nucleos de processamento diferentes. Invalidando a abordagem.

B) Sim

C) Sim

D) Nao
Eles ocorrem ao acesar uma seçao critica com duas tarefas simultaneamente e operar em variaveis que nao foram atualizadas.

E) Nao necessariamente
Se a mesma parte do codigo nao for uma secao critica, nao havera condicao de disputa.

F) Nao
Elas sao implementadas pelo programado

H) Nao
Muito pelo contrario, eles consomem CPU desnecessariamente.

I) Nao

3. Espera-ocupada
Suponha que a tarefa A precisa acessar uma area que esta sendo acessada pela tarefa B.
O que queremos eh que a tarefa A fique suspensa, sem tomar tempo da CPU. Logo a espera-ocupada eh quando a tarefa "espera" algo enquanto esta rodando na cpu (em um loop por exemplo) tomando tempo de outras tarefas.
Uma espera boa eh quando a tarefa fica suspensa, sem tomar tempo de processamento.

cap 11
1) Por que não existem operações read(s) e write(s) para ler ou ajustar o valor atual
de um semáforo?
Resposta: por questao de seguranca. Uma aplicacao nao pode controlar os valores internos de um semaforo, eles devem ser submetidos a funcoes que administram o semaforo internamente.

2) Mostre como pode ocorrer violação da condição de exclusão mútua se as
operações down(s) e up(s) sobre semáforos não forem implementadas de forma
atômica.
Resposta: podem ocorrer race conditions das variaveis internas do semaforo.
Imagine que internamente o semaforo tenha uma variavel que seja count (responsavel por administar quantas vagas tem para determinada area de memoria. Se uma tarefa entrar nessa area e for interrompida podera ocorrer problemas com a variavel counter.

3) Em que situações um semáforo deve ser inicializado em 0, 1 ou n > 1?
Resposta:
Mutex -> inicia com 0 ou 1 .Semaforos simplficados para exclusao mutua (dai vem o nome Mutual Exclusion)
No restante dos casos o semaforo eh inicializado com n > 1


