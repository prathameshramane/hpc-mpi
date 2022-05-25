#include<mpi.h>
#include<stdio.h>

int main(int argc, char **argv){
    int num_proc;
    int rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    printf("Hello World from RANK : %d\n", rank);

    MPI_Finalize();
}