#include <stdio.h>
#include "math.h"
#include "mpi.h"
#define N 15000000
#define PI acos(-1)

double f( double x ) { 
     return 4.0 / ( 1.0 + x * x);
}

int main(void) {

double totalTimeStart = 0.0;
double totalTimeFinish = 0.0;

double commTimeStart = 0.0;
double commTimeFinish = 0.0;

double timeElapsed = 0.0;

MPI_Init(NULL, NULL);

totalTimeStart = MPI_Wtime();

int rank, size;

MPI_Comm_size(MPI_COMM_WORLD, &size);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);

double a = 0.0, b = 1.0, toplam = 0.0, sonuc = 0.0;
double h = ( b - a ) / (double)N;
int chunk = N / size;

int i;

for (i = rank * chunk; i < (rank+1)*chunk; i++) {
     toplam += f( i * h );
}

toplam *= h;

// printf("%d no'lu process -> toplam = %1.10f\n", rank, toplam);

commTimeStart = MPI_Wtime();

MPI_Reduce ( &toplam, &sonuc, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD );

commTimeFinish = MPI_Wtime();

//if ( rank == 0) {
//     printf("Gercek PI   = %1.20f\n", PI);          
//     printf("Yaklasik PI = %1.20f\n", sonuc);
//}
     
totalTimeFinish = MPI_Wtime();

if ( rank == 0 ) {
     double a = 0.0;
}

timeElapsed = totalTimeFinish - totalTimeStart;

MPI_Reduce( &timeElapsed, &a, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

if ( rank == 0 ) {
     printf("Total parallel execution time = %f seconds\n", a);  
}

// printf("Proc %d: Total parallel execution time = %f seconds\n", rank, totalTimeFinish - totalTimeStart);
// printf("Proc %d: Total parallel communication time = %f seconds\n", rank, commTimeFinish - commTimeStart);

MPI_Finalize();

}
