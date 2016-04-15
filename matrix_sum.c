/***************************************************************************/
/* Christopher Celi 661124371 **********************************************/
/* Mark Westerhoff  XXXXXXXXX **********************************************/
/***************************************************************************/

/***************************************************************************/
/* Includes ****************************************************************/
/***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <clcg4.h>
#include <mpi.h>
//#include <hwi/include/bqc/A2_inlines.h>
#include <pthread.h>

/***************************************************************************/
/* Defines *****************************************************************/
/***************************************************************************/

#define SIZE 6
#define PTHREADS 3
#define MAX_INT 32767

/***************************************************************************/
/* Global Vars *************************************************************/
/***************************************************************************/

unsigned int **g_MATRIX = NULL;
unsigned int **g_MATRIX_TRANS = NULL;

/***************************************************************************/
/* Function Decs ***********************************************************/
/***************************************************************************/

void allocate_and_init_cells();

/***************************************************************************/
/* Function: Main **********************************************************/
/***************************************************************************/

int main(int argc, char *argv[])
{
    // allocate initial variables
    int i = 0, j = 0;
    int mpi_myrank;
    int mpi_commsize;
    unsigned long long start_cycle_time = 0;
    unsigned long long end_cycle_time = 0;
    unsigned long long total_cycle_time = 0;

    // begin and setup MPI
    MPI_Init( &argc, &argv);
    MPI_Comm_size( MPI_COMM_WORLD, &mpi_commsize);
    MPI_Comm_rank( MPI_COMM_WORLD, &mpi_myrank);

    // start MPI_Wtime for master
    if(mpi_myrank == 0){
        //start_cycle_time = GetTimeBase();
    }

    // init RNG streams, one for each rank
    InitDefault();

    printf("Params set for %d\n", mpi_myrank);

    MPI_Barrier( MPI_COMM_WORLD );

    // allocate cells randomly
    int rows_per_rank = SIZE / mpi_commsize; 
    allocate_and_init_cells(mpi_myrank, rows_per_rank);

    MPI_Barrier( MPI_COMM_WORLD );

#ifdef DEBUG
    printf("Matrix set\n");
#endif

    // perform barrier sync generation
    MPI_Barrier( MPI_COMM_WORLD );

    // determine transpose of region
    // MPI_Isend(g_GOL_CELL[rows_per_rank], g_y_cell_size, MPI_UNSIGNED, bot_dest, 2*mpi_myrank+1, MPI_COMM_WORLD, &req[1]);
    // receive ghost rows
    // MPI_Irecv(g_GOL_CELL[0], g_y_cell_size, MPI_UNSIGNED, top_dest, 2*top_dest, MPI_COMM_WORLD, &req[2]);

    // spawn threads
    pthread_t threads[PTHREADS];
    for(i = 0; i < PTHREADS; i++){

        int rc = pthread_create(&threads[i], NULL, compute_sum);
        if(rc) exit(-1);
    }

    // compute result and store in place (to not waste memory)


#ifdef DEBUG
    // print matrix for testing
    for(i = 0; i < rows_per_rank; i++){
        int cur_row = (rows_per_rank * mpi_myrank) + i;
        printf("Row %d: ", cur_row);
        for(j = 0; j < SIZE; j++){
            printf("%d ", g_MATRIX[i][j]);
        }
        printf("\n");
    }
#endif

    // export to file

    // end MPI_Wtime for master
    if(mpi_myrank == 0){
        //end_cycle_time = GetTimeBase();
        total_cycle_time = end_cycle_time - start_cycle_time;
    }

    MPI_Finalize();
    return 0;
}


/***************************************************************************/
/* Function: allocate_and_init_cells ***************************************/
/***************************************************************************/

void allocate_and_init_cells(int mpi_myrank, int rows_per_rank)
{
    // allocate rows_per_rank row arrays
    g_MATRIX = (unsigned int**) calloc(rows_per_rank, sizeof(unsigned int*));

    // allocate a column array for each row
    int i, j;
    for(i = 0; i < rows_per_rank; i++){

        // allocate SIZE arrays
        g_MATRIX[i] = (unsigned int*) calloc(SIZE, sizeof(unsigned int));
    }

    // allocate SIZE row arrays for transpose
    g_MATRIX_TRANS = (unsigned int**) calloc(SIZE, sizeof(unsigned int*));

    // allocate a column array for each row
    for(i = 0; i < SIZE; i++){

        // allocate rows_per_rank arrays
        g_MATRIX_TRANS[i] = (unsigned int*) calloc(rows_per_rank, sizeof(unsigned int*));
    }

    int cur_row;

    // iterate over each row
    for(i = 0; i < rows_per_rank; i++){

        // iterate over each column
        for(j = 0; j < SIZE; j++){

            // assign random value to cell
            cur_row = ((mpi_myrank * rows_per_rank) + i);
            g_MATRIX[i][j] = floor(GenVal(cur_row) * MAX_INT);
        }
    }
}


/***************************************************************************/
/* Function: compute_sum ***************************************************/
/***************************************************************************/

void* compute_sum()
{
    

    pthread_exit(NULL);
}
