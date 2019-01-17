#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include "math.h"

typedef struct {
     double real;
     double imag;
} Complex;

void complexProd(Complex *in, Complex *inout, int *len, MPI_Datatype *type) {
     int i;
     Complex c;
     
     for (i = 0; i < *len; i++) {
          c.real = inout->real * in->real - inout->imag * in->imag;
          c.imag = inout->real * in->imag + inout->imag * in->real;
          
          *inout = c;
          in++; inout++;
     }
}

int main(void) {

MPI_Init(NULL, NULL); // begins parallel session

int rank, size, i, j;

MPI_Comm_size(MPI_COMM_WORLD, &size); // each process knows the communicator size
MPI_Comm_rank(MPI_COMM_WORLD, &rank); // each process knows its unique rank

MPI_Op newOp;
MPI_Op_create(complexProd, 0, &newOp);

Complex cc;
cc.real = 3.0;
cc.imag = 2.0;

Complex result;
result.real = 0.0;
result.imag = 0.0;

MPI_Datatype ctype;
MPI_Type_contiguous(2, MPI_DOUBLE, &ctype);
MPI_Type_commit( &ctype );

MPI_Reduce(&cc, &result, 1, ctype, newOp, 0, MPI_COMM_WORLD);

printf("rank %d --> result.real = %f\n", rank, result.real);
printf("rank %d --> result.imag = %f\n", rank, result.imag);

MPI_Finalize();

return 0;

}









