all: clcg4.h clcg4.c matrix_sum.c
	gcc -I. -Wall -O3 -c clcg4.c -o clcg4.o
	mpicc -I. -Wall -O3 matrix_sum.c clcg4.o -o matrix_sum 

.PHONY: all-run
all-run: clcg4.h clcg4.c matrix_sum.c
	gcc -I. -Wall -O3 -c clcg4.c -o clcg4.o
	mpicc -I. -Wall -O3 matrix_sum.c clcg4.o -o matrix_sum
	mpirun -np $(RANKS) matrix_sum $(SIZE)

.PHONY: clean	
clean: 
	rm output*
