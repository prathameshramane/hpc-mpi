#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{

    int num_proc;
    int rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int rand_mine = rank * 54 + 28;
    int rand_prev;
    int rank_prev = rank == 0 ? num_proc - 1 : rank - 1;
    int rank_next = (rank + 1) % num_proc;
    MPI_Status status;

    printf("I %d have rand value : %d\n", rank, rand_mine);

    if (rank % 2 == 0)
    {

        printf("%d sending value %d to %d\n", rank, rand_mine, rank_next);
        MPI_Send((void *)&rand_mine, 1, MPI_INT, rank_next, 1, MPI_COMM_WORLD);

        printf("%d receving value %d from %d\n", rank, rand_prev, rand_prev);
        MPI_Recv((void *)&rand_prev, 1, MPI_INT, rank_prev, 1, MPI_COMM_WORLD, &status);
    }
    else
    {

        printf("%d receving value %d from %d\n", rank, rand_prev, rand_prev);
        MPI_Recv((void *)&rand_prev, 1, MPI_INT, rank_prev, 1, MPI_COMM_WORLD, &status);

        printf("%d sending value %d to %d\n", rank, rand_mine, rank_next);
        MPI_Send((void *)&rand_mine, 1, MPI_INT, rank_next, 1, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}