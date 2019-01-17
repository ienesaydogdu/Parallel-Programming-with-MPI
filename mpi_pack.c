#include <stdio.h>
#include "mpi.h"

int main() {


MPI_Init(NULL,NULL);

int rank, size;

MPI_Status status;

MPI_Comm_size(MPI_COMM_WORLD, &size);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);

char yazi[14] = "Merhaba Dunya";
int tarih[3] = {25, 4, 2018};
double sayi[10] = {0.0};

char buffer[106];
int position = 0;

if (rank == 0) {
     MPI_Pack(yazi, 14, MPI_CHAR, buffer, 106, &position, MPI_COMM_WORLD);
     printf("position = %d\n", position);
     MPI_Pack(tarih, 3, MPI_INT, buffer, 106, &position, MPI_COMM_WORLD);
     printf("position = %d\n", position);
     MPI_Pack(sayi, 10, MPI_DOUBLE, buffer, 106, &position, MPI_COMM_WORLD);
     printf("position = %d\n", position);

     MPI_Send(buffer, position, MPI_PACKED, 1, 777, MPI_COMM_WORLD);
} else {
     char rbuff[106];
     // printf("position = %d\n", position);
     MPI_Recv(rbuff, 106, MPI_PACKED, 0, 777, MPI_COMM_WORLD, &status);
     char rYazi[14];
     int rTarih[3];
     double rSayi[10];

     MPI_Unpack(rbuff, 106, &position, rYazi, 14, MPI_CHAR, MPI_COMM_WORLD);
     MPI_Unpack(rbuff, 106, &position, rTarih, 3, MPI_INT, MPI_COMM_WORLD);
     MPI_Unpack(rbuff, 106, &position, rSayi, 10, MPI_DOUBLE, MPI_COMM_WORLD);

     printf("%d\n", rTarih[2]);
}


MPI_Finalize();

}
