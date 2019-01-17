#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(void){

int size, rank,genelToplam;

MPI_Init(NULL,NULL);
MPI_Comm_size(MPI_COMM_WORLD,&size);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);

int ortakDizi[5] = {0};
int ortakDiziToplam =0;
int matris[4][5] = {0};
int count = 0;
for(int i = 0;i<4;i++)
    for(int j = 0;j<5;j++){
            count++;            
            matris[i][j] = count;
        }
MPI_Scatter(matris,5,MPI_INT,ortakDizi,5,MPI_INT,0,MPI_COMM_WORLD);

MPI_Barrier(MPI_COMM_WORLD);
printf("myrank: %d => %d %d %d %d %d\n",rank,ortakDizi[0],ortakDizi[1],ortakDizi[2],ortakDizi[3],ortakDizi[4]);

for(int i = 0;i<5;i++)ortakDiziToplam += ortakDizi[i];

MPI_Reduce(&ortakDiziToplam,&genelToplam,1,MPI_INT,MPI_MIN,0,MPI_COMM_WORLD);

MPI_Barrier(MPI_COMM_WORLD);
printf("myrank: %d => TOPLAM = %d \n",rank,genelToplam);



MPI_Finalize();
return 0;
}
