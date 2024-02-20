CFLAGS = -g -Wall -Wextra -Wno-unused-parameter
CC = gcc

PROGRAMS = main main2 main3

.PHONY: all clean

all: $(PROGRAMS)

main: main.o biblioLC.o entreeSortieLC.o
	$(CC) -o $@ $^ $(CFLAGS)

main2: exo3.o biblioLC.o entreeSortieLC.o
	$(CC) -o $@ $^ $(CFLAGS)

main.o: main.c
	$(CC) -o $@ -c $^ $(CFLAGS)

main3: exemplaire.o biblioLC.o entreeSortieLC.o 
	$(CC) -o $@ $^ $(CFLAGS)

exemplaire.o: exemplaire.c
	$(CC) -o $@ -c $^ $(CFLAGS) 

exo3.o: exo3.c
	$(CC) -o $@ -c $^ $(CFLAGS)

biblioLC.o: biblioLC.c biblioLC.h
	$(CC) -o $@ -c $< $(CFLAGS)

entreeSortieLC.o: entreeSortieLC.c entreeSortieLC.h biblioLC.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f *.o *~ $(PROGRAMS)
