#include <stdio.h>
#include <mpi.h>
#include <math.h>
int main(void){

MPI_Init(NULL,NULL);

int size;
MPI_Comm_size(MPI_COMM_WORLD,&size);

int rank;
MPI_Comm_rank(MPI_COMM_WORLD,&rank);

int dizi[7] = {2,4,6,8,10,12,14};
int i, sum = 0;

for(i=0;i<7;i++) 

/*
switch(rank){
case 0: puts("I am master\n");break;
case 1: for(i=0;i<7;i++)sum += dizi[i];
        printf("Sayilarin toplami = %d\n",sum);break;
case 2: for(i=0;i<7;i++)sum += dizi[i]*dizi[i];
        printf("Sayilarin karesinin toplami = %d\n",sum);break;
case 3: for(i=0;i<7;i++)sum += dizi[i]*dizi[i]*dizi[i];
        printf("Sayilarin küpünün toplami = %d\n",sum);break;
};
*/

MPI_Finalize();

}
