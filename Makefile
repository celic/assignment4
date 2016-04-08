all: clcg4.h clcg4.c assignment4.c
	gcc -I. -Wall -O3 -c clcg4.c -o clcg4.o
	mpicc -I. -Wall -O3 assignment4.c clcg4.o -o assignment4 

.PHONY: all-run
all-run: clcg4.h clcg4.c assignment4.c
	gcc -I. -Wall -O3 -c clcg4.c -o clcg4.o
	mpicc -I. -Wall -O3 assignment4.c clcg4.o -o assignment4
	mpirun -np $(RANKS) assignment4 $(SIZE)

.PHONY: clean	
clean: 
	rm output*
