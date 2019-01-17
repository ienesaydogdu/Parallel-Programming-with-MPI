#include <stdio.h>
#include "mpi.h"

int main(void) {

MPI_Status status;

MPI_Init(NULL, NULL); // begins parallel session

int rank, size, i, j;

MPI_Comm_size(MPI_COMM_WORLD, &size); // each process knows the communicator size
MPI_Comm_rank(MPI_COMM_WORLD, &rank); // each process knows its unique rank

int A[4][4] = {0};

if ( rank == 0 ) {
     for (i = 0; i < 4; i++)
          for (j = 0; j < 4; j++)
               A[i][j] = i * 4 + j + 1;
}

int b[4] = { 0 };

int counts[4] = {4, 3, 2, 1};
int displs[4] = {0, 5, 10, 15};

/*
int MPI_Scatterv(const void *sendbuf, const int *sendcounts, const int *displs,
                 MPI_Datatype sendtype, void *recvbuf, int recvcount,
                 MPI_Datatype recvtype,
                 int root, MPI_Comm comm)
*/

MPI_Scatterv(A, counts, displs, MPI_INT, b, counts[rank], MPI_INT, 0, MPI_COMM_WORLD);

for (i = 0; i < 4; i++)
     printf("rank %d --> b[%d] = %d\n", rank, i, b[i]);

int c[10] = { 0 };

/*
int MPI_Gatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
                void *recvbuf, const int *recvcounts, const int *displs,
                MPI_Datatype recvtype, int root, MPI_Comm comm)
*/

int rdispls[4] = {0, 4, 7, 9};
MPI_Gatherv(b, counts[rank], MPI_INT, c, counts, rdispls, MPI_INT, 0, MPI_COMM_WORLD);

if ( rank == 0 ) {
     for (i = 0; i < 10; i++)
          printf("c[%d] = %d\n", i, c[i]);
}

MPI_Finalize();

return 0;

}





