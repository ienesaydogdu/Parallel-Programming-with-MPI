#include <stdio.h>
#include "mpi.h"
#define ROW 12
#define COL 20

int main() {


MPI_Init(NULL,NULL);

int rank, size, i, j, A[ROW][COL] = {0}, B[60] = {0}, C[60] = {0};

MPI_Status status;

MPI_Comm_size(MPI_COMM_WORLD, &size);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);

if (rank == 0 ) {

    for (i=0; i<ROW; i++)
        for (j=0; j<COL; j++)
            A[i][j] = i*COL + j + 1;


}

MPI_Datatype rowType, colType;
// MPI_Type_contiguous(ROW*COL/size, MPI_INT, &rowType);
MPI_Type_contiguous(COL, MPI_INT, &rowType); // row by row
MPI_Type_commit(&rowType);

int count = ROW;
int blocklength = 1;
int stride = COL;
MPI_Type_vector(count, blocklength, stride, MPI_INT, &colType);
MPI_Type_commit(&colType);

// Row distribution
// MPI_Scatter(A, 1, rowType, B, 1, rowType, 0, MPI_COMM_WORLD);
// MPI_Scatter(A, ROW/size, rowType, B, ROW/size, rowType, 0, MPI_COMM_WORLD);

if (rank == 0) {
     for (i = 0; i < COL/size; i++)
          MPI_Send(&A[0][i], 1, colType, 1, 777+i, MPI_COMM_WORLD);
} else if (rank == 1) {
     // MPI_Recv(C, 1, colType, 0, 777, MPI_COMM_WORLD, &status);
     for (i = 0; i < COL/size; i++)
          MPI_Recv(&C[i*ROW], 60, MPI_INT, 0, 777+i, MPI_COMM_WORLD, &status);
}

if (rank == 1) {
     for (i=0; i<60; i++)
          printf("rank: %d and C[%d] = %d\n", rank, i, C[i]);
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
