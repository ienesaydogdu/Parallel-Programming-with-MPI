#include "mpi.h"
#include <stdio.h>

int main(void) {

int rank, size;

MPI_Init(NULL, NULL);

MPI_Status status;

MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);

int i, a[20], b[10];
if ( rank == 0) {
     for (i = 0; i < 20; i++)
          a[i] = 2 * ( i + 1 );
}

MPI_Datatype arrayType;
MPI_Type_contiguous (10, MPI_INT, &arrayType);
MPI_Type_commit(&arrayType);

if ( rank == 0) {
     for (i = 0; i < 10; i++)
          a[i] = 2 * ( i + 1 );
}

if (rank == 0) {
     MPI_Send(a, 1, arrayType, 1, 777, MPI_COMM_WORLD);
} else if ( rank == 1 ){
     MPI_Recv(b, 1, arrayType, 0, 777, MPI_COMM_WORLD, &status);
}

MPI_Barrier(MPI_COMM_WORLD);

if (rank == 0) {
     MPI_Send(&a[10], 1, arrayType, 2, 666, MPI_COMM_WORLD);
} else if ( rank == 2 ){
     MPI_Recv(b, 1, arrayType, 0, 666, MPI_COMM_WORLD, &status);
}

if (rank != 0) {
     for (i = 0; i < 10; i++)
          printf("rank %d --> b[%d] = %d\n", rank, i, b[i]);
}

MPI_Finalize();
return 0;
}








