#include <stdio.h>
#include "mpi.h"

int main(void) {

MPI_Init(NULL, NULL); // begins parallel session

int rank, size, i, j;

MPI_Comm_size(MPI_COMM_WORLD, &size); // each process knows the communicator size
MPI_Comm_rank(MPI_COMM_WORLD, &rank); // each process knows its unique rank

int color = ( rank < size/2 ) ? 0 : 1;
MPI_Comm newcomm;
MPI_Comm_split(MPI_COMM_WORLD, color, 0, &newcomm);

int newRank, newSize;
MPI_Comm_size(newcomm, &newSize);
MPI_Comm_rank(newcomm, &newRank);

printf("Old rank is %d out of %d. New rank is %d out of %d\n", rank, size, newRank, newSize);

int a = 0;

if ( rank == 0 ) {
        a = 6;
}

if ( rank == 4 ) {
        a = 7;
}

MPI_Bcast( &a, 1, MPI_INT, 0, newcomm );

printf("rank %d --> a = %d\n", rank, a);

MPI_Finalize();

return 0;
}

