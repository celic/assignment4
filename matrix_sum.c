/***************************************************************************/
/* Christopher Celi 661124371 **********************************************/
/* Mark Westerhoff  XXXXXXXXX **********************************************/
/***************************************************************************/

/***************************************************************************/
/* Includes ****************************************************************/
/***************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<math.h>
#include<clcg4.h>
#include<mpi.h>
#include<hwi/include/bqc/A2_inlines.h>

/***************************************************************************/
/* Defines *****************************************************************/
/***************************************************************************/

#define SIZE 3

/***************************************************************************/
/* Global Vars *************************************************************/
/***************************************************************************/

unsigned int **g_MATRIX=NULL;

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
    int i = 0;
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
        start_cycle_time = GetTimeBase();
    }

    // init RNG streams, one for each rank
    InitDefault();

    MPI_Barrier( MPI_COMM_WORLD );

    int rows_per_rank = SIZE / mpi_myrank;
    allocate_and_init_cells(mpi_myrank);

    // perform barrier to end parallel commands
    MPI_Barrier( MPI_COMM_WORLD );

    // end MPI_Wtime for master
    if(mpi_myrank == 0){
        end_cycle_time = GetTimeBase();
        total_cycle_time = end_cycle_time - start_cycle_time;
    }

    MPI_Finalize();
    return 0;
}

/***************************************************************************/
/* Function: allocate_and_init_cells ***************************************/
/***************************************************************************/

void allocate_and_init_cells(int mpi_myrank)
{
    // allocate SIZE row arrays
    g_MATRIX = (unsigned int**)calloc(SIZE, sizeof(unsigned int*));

    // allocate SIZE column arrays
    int i, j;
    for(i = 0; i < SIZE; i++){

        // allocate SIZE arrays of size SIZE
        g_MATRIX[i] = (unsigned int*) calloc(SIZE, sizeof(unsigned int));
    }

    int cur_row;

    // iterate over each row
    for(i = 0; i < SIZE; i++){

        // do not assign a value to the ghost rows
        if(i == 0 || i == rows_per_rank-1) continue;

        // iterate over each column
        for(j = 0; j < g_y_cell_size; j++){

            // assign random value to cell
            cur_row = ((mpi_myrank * (rows_per_rank-2)) + i);
            g_MATRIX[i][j] = ((GenVal(cur_row) >= .5) ? DEAD : ALIVE);
        }
    }
}



