#include <stdio.h>
#include "mpi.h"

int main(void) {
MPI_Init(NULL, NULL); // begins parallel session

int rank, size, i, j;

MPI_Comm_size(MPI_COMM_WORLD, &size); // each process knows the communicator size
MPI_Comm_rank(MPI_COMM_WORLD, &rank); // each process knows its unique rank
MPI_Status status;
int color = ( rank%2==0 ) ? 0 : 1;
MPI_Comm newcomm;
MPI_Comm_split(MPI_COMM_WORLD, color, 0, &newcomm);

int newRank, newSize;
MPI_Comm_size(newcomm, &newSize);
MPI_Comm_rank(newcomm, &newRank);

int matris[4][4] = {0};
int dizi [4] = {0};
int sonuc,ij=10;

if ( rank == 0 ) {// matris rank 0 tarafından dolduruluyor
     for (int i = 0; i < 4; i++)
          for (int j = 0; j < 4; j++){
               matris[i][j] = ij;
                ij+=10;
            }
}
if ( rank == 0 ) {// matrisi ekrana yazdırmak için yazıldı
     for (int i = 0; i < 4; i++){
          for (int j = 0; j < 4; j++){
              printf("%d ",matris[i][j]);  
                
            }
        printf("\n"); 
    }
}

int counts[4] = {1, 2, 3, 4};
int displs[4] = {0, 4, 8, 12};

MPI_Scatterv(matris, counts, displs, MPI_INT, dizi, counts[newRank], MPI_INT, 0, newcomm);// matris elemanları dağıtılıyor.

if(rank == 6){printf("rank 6 gonderiyor..\n");//rank 6 dan rank 1 e satır gönderiliyor
for (int i = 0; i < 4; i++){ 
    MPI_Send(dizi,4,MPI_INT,1,666,MPI_COMM_WORLD);
    } 
}
if(rank == 1){printf("rank 1 aliyor..\n");
for (int i = 0; i < 4; i++){
    MPI_Recv(dizi,4,MPI_INT,6,666,MPI_COMM_WORLD,&status);
    } 
}

MPI_Scatter(dizi,1,MPI_INT,&sonuc,1,MPI_INT,0,newcomm);// rank 1 kendi kümesine sayıları dağıtıyor.

if(rank%2!=0){
     printf("rank: %d => sonuc = %d\n",rank,sonuc);
    
}

MPI_Finalize();

return 0;
}
