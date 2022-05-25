#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{

    int pid, np;
    int message = 100, message_recv;

    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);

    if (pid == 0)
    {
        printf("Broadcasting message : %d\n", message);
        MPI_Bcast(&message, 1, MPI_INT,
                  0, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Bcast(&message_recv, 1, MPI_INT,
                  0, MPI_COMM_WORLD);
        printf("Message received at process %d : %d\n", pid, message_recv);
    }

    MPI_Finalize();
    return 0;
}

// Output
//  ryder@ryder-VivoBook-15-ASUS-Laptop-X540UAR:~/Projects/HPC/codes$ mpirun -n 5 ./broadcast
//  Broadcasting message 100
//  Message received is 100
//  Message received is 100
//  Message received is 100
//  Message received is 100