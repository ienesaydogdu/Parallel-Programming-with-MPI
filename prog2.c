#include <stdio.h>
#include <mpi.h>

int main(void)
{

    MPI_Init(NULL,NULL);

    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int dizi[7]= {1,2,3,4,5,6,7};
    
    int i=0, sum =1;
   
    printf("Benim rankım: %d Size: %d\n",rank,size );
    switch (rank)
    {
        case 0: 
            printf("Master işlemci\n");
            break;
        case 1:
            for(i=0; i<=6; i++)
            sum += dizi[i];
            
            printf("Toplam: %d\n",sum);
            break;
        case 2:
            for(i=0; i<=6; i++)
            sum -= dizi[i];
            printf("Cıkarma: %d\n",sum);
            break;
        case 3:
            for(i=0; i<=6; i++)
            sum *= dizi[i];
            printf("Carpim: %d\n",sum);
            break;


    }
    MPI_Finalize();

    return 0;
}
