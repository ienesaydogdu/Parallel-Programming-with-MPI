#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(void){

int size,rank;
MPI_Init(NULL,NULL);
MPI_Comm_size(MPI_COMM_WORLD,&size);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Status status;

int arraySize = 12;
int chunk = arraySize / size;

int *b = (int*) malloc(chunk * sizeof(int)); // programı dinamik yapmak için yaptık. veriye göre memoryde alan açıyor.

if (rank == 0){
    int *a = (int*) malloc(arraySize * sizeof(int));
    for(int i = 0; i < arraySize; i++)a[i] = i+1;
    for(int i = 0; i < chunk; i++) b[i] = a[i];
    for(int i = 1; i < size; i++) MPI_Send(&a[i*chunk], chunk, MPI_INT, i, 770+i, MPI_COMM_WORLD);
 //   MPI_Send(&a[4], 4, MPI_INT, 1, 771, MPI_COMM_WORLD); //771 = tag istediğimiz sayıyı verebilriiz
 //   MPI_Send(&a[8], 4, MPI_INT, 2, 772, MPI_COMM_WORLD); //772 = tag istediğimiz sayıyı verebilriiz
}else{
    MPI_Recv(b, 4, MPI_INT, 0, 770+rank, MPI_COMM_WORLD, &status);
}

for(int i = 0; i < 12/size; i++)printf("Proc %d --> b[%d] = %d\n",rank, i, b[i]);


MPI_Finalize();
}
