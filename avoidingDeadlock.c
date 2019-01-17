#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(void){

    int a[10], b[10], rank, size;
    MPI_Status status;
    MPI_Request request;
    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if(rank == 0){
    int a[10000] = {0};
    int b[10000] = {0};
    MPI_Send(a, 10, MPI_INT, 1, 100, MPI_COMM_WORLD);
    MPI_Send(b, 10, MPI_INT, 1, 200, MPI_COMM_WORLD);

    }else if(rank == 1){
    int a[10000],b[10000];
    MPI_Recv(b, 10, MPI_INT,0 , 200, MPI_COMM_WORLD,&status);
    MPI_Recv(a, 10, MPI_INT, 0, 100, MPI_COMM_WORLD,&status);

    }


MPI_Finalize();
















}
