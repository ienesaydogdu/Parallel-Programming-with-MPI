#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(void){
int size, rank;

MPI_Init(NULL,NULL);
MPI_Comm_size(MPI_COMM_WORLD,&size);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);

int chunk = 40/size;
int dizia[40] = {0};
int dizib[10] = {0};

for(int i = 0;i<40;i++)dizia[i] = i+1;

MPI_Scatter(dizia,chunk,MPI_INT,dizib,chunk,MPI_INT,0,MPI_COMM_WORLD);
MPI_Barrier(MPI_COMM_WORLD);
for(int i = 0;i<10;i++){


printf("my rank: %d, mydizib[%d] = %d\n",rank,i,dizib[i]);
}

MPI_Finalize();
return 0;

}
