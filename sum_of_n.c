#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{

    int pid, np;
    int n_elements_per_proc, n_elements_recv;
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = 10;
    int a2[1000];

    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);

    if (pid == 0)
    {
        int index, i;
        n_elements_per_proc = n / np;

        if (np > 1)
        {
            for (i = 1; i < np - 1; i++)
            {
                index = i * n_elements_per_proc;

                MPI_Send(&n_elements_per_proc, 1, MPI_INT,
                         i, 0, MPI_COMM_WORLD);
                MPI_Send(&a[index], n_elements_per_proc, MPI_INT,
                         i, 0, MPI_COMM_WORLD);
            }

            index = i * n_elements_per_proc;
            int elements_left = n - index;

            MPI_Send(&elements_left, 1, MPI_INT,
                     i, 0, MPI_COMM_WORLD);
            MPI_Send(&a[index], elements_left, MPI_INT,
                     i, 0, MPI_COMM_WORLD);
        }

        int sum = 0;
        for (i = 0; i < n_elements_per_proc; i++)
            sum += a[i];

        int temp;
        for (int i = 1; i < np; i++)
        {
            MPI_Recv(&temp, 1, MPI_INT,
                     MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            sum += temp;
        }

        printf("Sum is : %d\n", sum);
    }
    else
    {
        MPI_Recv(&n_elements_recv, 1, MPI_INT,
                 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&a2, n_elements_recv, MPI_INT,
                 0, 0, MPI_COMM_WORLD, &status);

        int temp_sum;
        for (int i = 0; i < n_elements_recv; i++)
            temp_sum += a2[i];

        MPI_Send(&temp_sum, 1, MPI_INT,
                 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}