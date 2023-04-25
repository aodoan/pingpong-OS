TARGET = ppos-saida
PROGRAM-TEST = test-program
CC = gcc 
CFLAGS = -Wall 

default: $(TARGET)
all: default

debug: CFLAGS += -DDEBUG
debug: default

$(TARGET): ppos-core.o queue.o $(PROGRAM-TEST).o
	$(CC) $(CFLAGS) -o $(TARGET) $(DEBUG) ppos-core.o queue.o $(PROGRAM-TEST).o

ppos-core.o: ppos-core.c ppos.h ppos_data.h queue.h
	$(CC) $(CFLAGS) $(DEBUG) -c ppos-core.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) $(DEBUG) -c queue.c

$(PROGRAM-TEST).o: $(PROGRAM-TEST).c ppos.h
	$(CC) $(CFLAGS) $(DEBUG) -c $(PROGRAM-TEST).c

clean:
	rm -f *.o $(TARGET)
