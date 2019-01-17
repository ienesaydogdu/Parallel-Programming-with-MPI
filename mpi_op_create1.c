#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include "math.h"
#include "time.h"

void oneNorm(double *in, double *inout, int *boy, MPI_Datatype *type) {
     int i;
     for (i = 0; i < *boy; i++) {
          *inout = fabs(*in) + fabs(*inout);
          in++; inout++;
     }
}

int main(void) {

MPI_Init(NULL, NULL); // begins parallel session

int rank, size, i, j;

MPI_Comm_size(MPI_COMM_WORLD, &size); // each process knows the communicator size
MPI_Comm_rank(MPI_COMM_WORLD, &rank); // each process knows its unique rank

srand(time(NULL)+rank);

MPI_Op newOp;
// int MPI_Op_create(MPI_User_function *user_fn, int commute, MPI_Op *op)
MPI_Op_create(oneNorm, 1, &newOp);

double a[400];
if (rank == 0) {
     for (i = 0; i < 400; i++)
          a[i] = (double)rand() / (double)RAND_MAX;
}

double b[100] = { 0 };

MPI_Scatter(a, 100, MPI_DOUBLE, b, 100, MPI_DOUBLE, 0, MPI_COMM_WORLD);

double toplam = 0.0;
for (i = 0; i < 100; i++)
     toplam += fabs(b[i]);

double result = 0.0;
MPI_Allreduce(&toplam, &result, 1, MPI_DOUBLE, newOp, MPI_COMM_WORLD);

printf("rank %d --> %f\n", rank, result);

MPI_Finalize();

return 0;

}









