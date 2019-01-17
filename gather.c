#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#define N 


int main(void){
int size,rank;
  
    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Status status;
    
    double a [N] = {0,0};
    double b [CHUNK] = {0,0};

    



}
