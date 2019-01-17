#include <stdio.h>
#include "mpi.h"
#define ROW 4
#define COL 4
#define SIZE 4

int main() {


MPI_Init(NULL,NULL);

int rank, size, i, j, A[ROW][COL] = {0}, upp[10] = {0}, low[10] = {0};

MPI_Status status;

MPI_Comm_size(MPI_COMM_WORLD, &size);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);

if (rank == 0 ) {

    for (i=0; i<ROW; i++)
        for (j=0; j<COL; j++)
            A[i][j] = i*COL + j + 1;

}

MPI_Datatype uppType, lowType;

int countU = ROW;
int blengthsU[SIZE] = {4, 3, 2, 1};
int displsU[SIZE] = {0, 5, 10, 15};
MPI_Type_indexed(countU, blengthsU, displsU, MPI_INT, &uppType);
MPI_Type_commit(&uppType);

int countL = ROW;
int blengthsL[SIZE] = {1, 2, 3, 4};
int displsL[SIZE] = {0, 4, 8, 12};
MPI_Type_indexed(countL, blengthsL, displsL, MPI_INT, &lowType);
MPI_Type_commit(&lowType);



if (rank == 0) {
          MPI_Send(A, 1, uppType, 1, 777, MPI_COMM_WORLD);
          MPI_Send(A, 1, lowType, 1, 778, MPI_COMM_WORLD);
} else if (rank == 1) {
          MPI_Recv(upp, 10, MPI_INT, 0, 777, MPI_COMM_WORLD, &status);
          MPI_Recv(low, 10, MPI_INT, 0, 778, MPI_COMM_WORLD, &status);
}

MPI_Type_free(&uppType);
MPI_Type_free(&lowType);

if (rank == 1) {
     for (i=0; i<10; i++)
          printf("upp[%d] = %d\n", i, upp[i]);

     printf("*********************************\n");
     
     for (i=0; i<10; i++)
          printf("low[%d] = %d\n", i, low[i]);

}

// Col distribution
/*
if ( rank == 0) {
     for (i = 1; i < size; i++) {
          MPI_Send( &A[0][COL/size*i], 5, colType, i, 55+i, MPI_COMM_WORLD );
     }
}
else {
     MPI_Recv(C, 5, colType, 0, 55+rank, MPI_COMM_WORLD, &status);
}
*/


MPI_Finalize();

}

// bu kod uhemde çalışacak..
