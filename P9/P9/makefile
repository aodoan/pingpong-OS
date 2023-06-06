# Código desenvolvido para disciplina de Sistemas Operacionais 
# pelo aluno Claudinei Aparecido Alduan Filho GRR20203920

TARGET = ppos-saida
PROGRAM-TEST = test-program
CC = gcc 
CFLAGS = -Wall 
CORE = ppos_core
default: $(TARGET)
all: default

debug: CFLAGS += -DDEBUG
debug: default

$(TARGET): $(CORE).o queue.o $(PROGRAM-TEST).o
	$(CC) $(CFLAGS) -o $(TARGET) $(DEBUG) $(CORE).o queue.o $(PROGRAM-TEST).o

$(CORE).o: $(CORE).c ppos.h ppos_data.h queue.h
	$(CC) $(CFLAGS) $(DEBUG) -c $(CORE).c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) $(DEBUG) -c queue.c

$(PROGRAM-TEST).o: $(PROGRAM-TEST).c ppos.h
	$(CC) $(CFLAGS) $(DEBUG) -c $(PROGRAM-TEST).c

clean:
	rm -f *.o $(TARGET)
