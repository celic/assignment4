all: clcg4.h clcg4.c matrix_sum.c
	gcc -I. -Wall -O3 -c clcg4.c -o clcg4.o
	mpicc -I. -Wall -O3 matrix_sum.c clcg4.o -lm -o matrix_sum 

.PHONY: all-run
all-run: clcg4.h clcg4.c matrix_sum.c
	gcc -I. -Wall -O3 -c clcg4.c -o clcg4.o
	mpicc -I. -Wall -O3 matrix_sum.c clcg4.o -lm -o matrix_sum
	mpirun -np $(RANKS) matrix_sum $(NUM_THREADS)

.PHONY: all-run-debug
all-run-debug: clcg4.h clcg4.c matrix_sum.c
	gcc -I. -Wall -O3 -c clcg4.c -o clcg4.o
	mpicc -I. -Wall -O3 matrix_sum.c clcg4.o -lm -DDEBUG -o matrix_sum
	mpirun -np $(RANKS) matrix_sum $(NUM_THREADS)

.PHONY: clean	
clean: 
	rm output*
