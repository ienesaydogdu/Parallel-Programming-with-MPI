#include <stdio.h>
#include "mpi.h"

int main(void){

int size,rank;
MPI_Init(NULL,NULL);
MPI_Comm_size(MPI_COMM_WORLD,&size);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Status status;

int a = 13;
int MASTER = 0;

if (rank == MASTER){
    a++;
    for(int i = 1; i<size; i++) MPI_Send(&a, 1, MPI_INT, i, 990+i, MPI_COMM_WORLD);
}
else{

    MPI_Recv(&a, 1, MPI_INT, 0, 990+rank, MPI_COMM_WORLD, &status);
a+=10;
}

printf("Proc %d: a = %d\n", rank, a);
MPI_Finalize();
}
