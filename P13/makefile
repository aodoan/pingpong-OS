TARGET = ppos_saida
CC = cc
CFLAGS = -Wall
LIBS = -lrt -lm

OBJS = queue.o ppos_core.o ppos_disk.o disk.o test-program.o

default: $(TARGET) clean
all: default 

debug: CFLAGS += -DDEBUG
debug: default

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o saida 

queue.o: queue.c
	$(CC) $(CFLAGS) -c queue.c 

ppos_core.o: ppos_core.c
	$(CC) $(CFLAGS) -c ppos_core.c 

ppos_disk.o: ppos_disk.c
	$(CC) $(CFLAGS) -c ppos_disk.c 

disk.o: disk.c
	$(CC) $(CFLAGS) -c disk.c 

test-program.o: test-program.c
	$(CC) $(CFLAGS) -c test-program.c 

clean:
	rm -f *.o 

purge:
	rm -f *.o $(TARGET)
