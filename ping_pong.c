#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

enum Players{Federer, Nadal};

int main(void){
    
    int size,name,i,number = 0, TAG = 100;
    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&name);
    MPI_Status status;
    
    int playCount = 10;

    for(int i = 0; i<10; i++){

    if(name == Federer){
        number++;
        MPI_Send(&number, 1, MPI_INT, Nadal, TAG+i, MPI_COMM_WORLD);
        printf("Federer %d sayisini Nadal'a gonderdi!\n",number);
        MPI_Recv(&number, 1, MPI_INT, Nadal, TAG+playCount+i, MPI_COMM_WORLD, &status);
    }else if(name == Nadal){
    
         MPI_Recv(&number, 1, MPI_INT, Federer, TAG+i, MPI_COMM_WORLD, &status);
         number++;
         MPI_Send(&number, 1, MPI_INT, Federer, TAG+playCount+i, MPI_COMM_WORLD);  
        printf("Nadal %d sayisini Federer'e gonderdi!\n",number);

     }
    }
    MPI_Finalize();
}
