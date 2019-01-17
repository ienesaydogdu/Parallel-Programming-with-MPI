#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(void){
    
    int size,rank,count,count2;
    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Status status1, status2;

    if(rank == 0){
       
        double dizi[100]; 
        for(int i = 0; i<100; i++){

            dizi[i] = (double)i+1.0;
        }
        
        MPI_Send(&dizi[0], 50, MPI_DOUBLE, 1, 113, MPI_COMM_WORLD);
        
        MPI_Send(&dizi[50], 25, MPI_DOUBLE, 2, 114, MPI_COMM_WORLD);
    }
    else if(rank == 1){

    double dizi_1[50] = {0}; 
    MPI_Recv(&dizi_1[0], 50, MPI_DOUBLE, 0, 113, MPI_COMM_WORLD, &status1);       
    printf("Birinci mesaj %d numarali mesajdir!\n",status1.MPI_TAG);
    printf("Birinci mesaj %d numarali processten geldi\n!",status1.MPI_SOURCE);

    MPI_Get_count(&status1, MPI_DOUBLE, &count);
    printf("Birinci mesaj %d adet veri yollanmistir\n!",count);

    }
    else {

    double dizi_2[25] = {0}; 
    MPI_Recv(&dizi_2[0], 25, MPI_DOUBLE, 0, 114, MPI_COMM_WORLD, &status2);       
    printf("Ikinci mesaj %d numarali mesajdir!\n",status2.MPI_TAG);
    printf("Ikinci mesaj %d numarali processten geldi\n!",status2.MPI_SOURCE);

    MPI_Get_count(&status2, MPI_DOUBLE, &count);
    printf("Ikinci mesaj %d adet veri yollanmistir\n!",count);
    }

    
    
    MPI_Finalize();


}

