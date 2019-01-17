#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include "time.h"

int main(void){
    
    
    int size,rank;
  
    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
   
    srand(time(NULL)+rank);
    
     
    

    int dizi[100], toplam = 0 ,min =301;
    for(int i = 0; i<100;i++){
     
      int random = 200+rand()%100;
       dizi[i] = random;
    }

     for(int i = 0; i<100; i++){

        if(min>dizi[i]) min = dizi[i];
        
    }
    
    printf("Minimum Sayilar = %d\n",min);
    MPI_Reduce(&min, &toplam, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD); 

    if(rank == 0)printf("Sonuc = %d\n",toplam);   

    MPI_Finalize();       

}
