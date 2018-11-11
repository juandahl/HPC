PROGRAMS = main
CFLAGS = -Wall -g
CC = gcc 
COMPILE = $(CC) $(CFLAGS) -c 

all: $(PROGRAMS)

main: main.o mouvement.o mouvement_SSE2.o morpho.o morpho_SSE2.o test_mouvement.o test_mouvement_SSE2.o test_morpho.o test_morpho_SSE2.o
	$(CC) -o main main.o mouvement.o mouvement_SSE2.o morpho.o morpho_SSE2.o test_mouvement.o test_mouvement_SSE2.o test_morpho.o test_morpho_SSE2.o -L/usr/lib/x86_64-Linux-gnu/

mouvement.o: mouvement.c nrutil.h nrdef.h
	$(COMPILE) mouvement.c 

main.o: main.c
	$(COMPILE) main.c

mouvement_SSE2.o: mouvement_SSE2.c
	$(COMPILE) mouvement_SSE2.c

morpho.o: morpho.c  
	$(COMPILE) morpho.c

morpho_SSE2.o: morpho_SSE2.c
	$(COMPILE) morpho_SSE2.c

test_mouvement.o: test_mouvement.c 
	$(COMPILE) test_mouvement.c

test_mouvement_SSE2.o: test_mouvement_SSE2.c 
	$(COMPILE) test_mouvement_SSE2.c

test_morpho.o: test_morpho.c
	$(COMPILE) test_morpho.c

test_morpho_SSE2.o: test_morpho_SSE2.c
	$(COMPILE) test_morpho_SSE2.c

clean:
	rm -f $(PROGRAMS) *.o

.PHONY: all clean
