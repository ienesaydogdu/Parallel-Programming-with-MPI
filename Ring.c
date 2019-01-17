#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"



int main(void){
    
    
    int size,rank,i,x = 0, TAG = 100;
  
    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Status status;
    
    int first =0;
    int last = size-1;
  
    if(rank == first){

        x = 0;
        x += rank;
        MPI_Send(&x, 1, MPI_INT, first+1, TAG, MPI_COMM_WORLD);
        MPI_Recv(&x, 1, MPI_INT, last, TAG, MPI_COMM_WORLD,&status);
        

    }else  if(rank == last){
        
        MPI_Recv(&x, 1, MPI_INT, last-1, TAG, MPI_COMM_WORLD,&status);  
        x += rank;
        MPI_Send(&x, 1, MPI_INT, first, TAG, MPI_COMM_WORLD);  

    }else{

         MPI_Recv(&x, 1, MPI_INT, rank-1, TAG, MPI_COMM_WORLD,&status);
        x += rank;
        MPI_Send(&x, 1, MPI_INT, rank+1, TAG, MPI_COMM_WORLD);         
    }
   if(rank == first)printf("x = %d\n",x);

    MPI_Finalize();
}
