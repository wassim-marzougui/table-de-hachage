CFLAGS = -g -Wall -Wextra -Wno-unused-parameter
CC = gcc

PROGRAMS = main main2 main3

.PHONY: all clean

all: $(PROGRAMS)

main: main.o biblioH.o EntreeSortieH.o -lm
	$(CC) -o $@ $^ $(CFLAGS)

main2: exo3.o biblioH.o EntreeSortieH.o -lm
	$(CC) -o $@ $^ $(CFLAGS)

main3: exemplaire.o biblioH.o EntreeSortieH.o -lm
	$(CC) -o $@ $^ $(CFLAGS)

exemplaire.o: exemplaire.c
	$(CC) -o $@ -c $^ $(CFLAGS) -lm

exo3.o: exo3.c
	$(CC) -o $@ -c $^ $(CFLAGS) -lm

main.o: main.c
	$(CC) -o $@ -c $^ $(CFLAGS) -lm

biblioH.o: biblioH.c biblioH.h -lm
	$(CC) -o $@ -c $< $(CFLAGS)

EntreeSortieH.o: EntreeSortieH.c EntreeSortieH.h biblioH.h -lm
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f *.o *~ $(PROGRAMS)
