#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int num_proc;
    int rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    printf("Hello World from RANK : %d\n", rank);

    MPI_Finalize();
}

// Output
// ryder@ryder-VivoBook-15-ASUS-Laptop-X540UAR:~/Projects/HPC/codes$ mpirun -n 8 ./hello_world
// Hello World from RANK : 0
// Hello World from RANK : 1
// Hello World from RANK : 3
// Hello World from RANK : 4
// Hello World from RANK : 5
// Hello World from RANK : 6
// Hello World from RANK : 2
// Hello World from RANK : 7