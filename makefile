OBJS	= queue.o testafila.o
SOURCE	= queue.c testafila.c
HEADER	= queue.h
OUT	= saida
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

queue.o: queue.c
	$(CC) $(FLAGS) queue.c 

testafila.o: testafila.c
	$(CC) $(FLAGS) testafila.c 


clean:
	rm -f $(OBJS) $(OUT)
