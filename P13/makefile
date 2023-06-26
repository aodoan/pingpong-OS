TARGET = ppos_saida
CC = cc
CFLAGS = -Wall
LIBS = -lrt

OBJS = queue.o ppos_core.o ppos_disk.o disk.o test-program.o

default: $(TARGET) clean
all: default 

debug: CFLAGS += -DDEBUG
debug: default

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o saida -lm

queue.o: queue.c
	$(CC) $(CFLAGS) -c queue.c -lm

ppos_core.o: ppos_core.c
	$(CC) $(CFLAGS) -c ppos_core.c -lm

ppos_disk.o: ppos_disk.c
	$(CC) $(CFLAGS) -c ppos_disk.c -lm

disk.o: disk.c
	$(CC) $(CFLAGS) -c disk.c -lm

test-program.o: test-program.c
	$(CC) $(CFLAGS) -c test-program.c -lm

clean:
	rm -f *.o 

purge:
	rm -f *.o $(TARGET)
