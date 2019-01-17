#include <stdio.h>
#include "mpi.h"

void printVector(double vctr[], int n, int name) {
     int i;
     for (i = 0; i < n; i++) 
          printf("Process %d: a[%d] = %f\n", name, i, vctr[i]);
}

int main(void) {

MPI_Status status;
// MPI_Request request;

MPI_Init(NULL, NULL);

int rank, size;

MPI_Comm_size(MPI_COMM_WORLD, &size);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);

double a[15] = {0.0};

printVector(a, 15, rank);

if ( rank == 2 ) {
     int i;
     for (i = 0; i < 15; i++)
          a[i] = (double)i;
}

MPI_Barrier(MPI_COMM_WORLD);

printVector(a, 15, rank);

MPI_Barrier(MPI_COMM_WORLD);

MPI_Bcast(a, 15, MPI_DOUBLE, 2, MPI_COMM_WORLD);

printVector(a, 15, rank);

MPI_Finalize();

}

