#include <mpi.h>
#include <stdio.h>
#include <math.h>

int isprime(int n)
{
    int top, d;
    top = (int)(sqrt((double)n) + 0.0001);
    for (d = 2; d <= top; d++)
        if (n % d == 0)
            return 0;
    return 1;
}

int main(int argc, char **argv)
{

    int pid, np;
    int n = 10000000;

    int temp[2];

    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);

    if (pid == 0)
    {
        int i;
        int a[2];
        int n_size_per_proc = n / np;
        if (np > 1)
        {
            for (i = 1; i < np - 1; i++)
            {
                a[0] = i * (n_size_per_proc) + 1;
                a[1] = a[0] + n_size_per_proc - 1;
                MPI_Send(&a, 2, MPI_INT,
                         i, 0, MPI_COMM_WORLD);
                printf("%d, %d, %d \n", a[0], a[1], i);
            }

            a[0] = a[1] + 1;
            a[1] = n;

            MPI_Send(&a, 2, MPI_INT,
                     i, 0, MPI_COMM_WORLD);

            int count = 0;
            int max_prime = 2;
            for (i = 2; i <= n_size_per_proc; i++)
            {
                if (isprime(i))
                {
                    count++;
                    if (max_prime < i)
                    {
                        max_prime = i;
                    }
                }
            }

            printf("Process %d reports %d primes between 2 and %d", pid, count, n_size_per_proc);

            int a2[4];
            for (int i = 1; i < np; i++)
            {
                MPI_Recv(&a2, 4, MPI_INT,
                         i, 0, MPI_COMM_WORLD, &status);
                printf("Process %d reports %d primes between %d and %d", i, a2[0], a2[2], a2[3]);
                if (max_prime < a2[1])
                {
                    max_prime = a2[1];
                }
            }

            printf("The maximum value of prime number between 2 and %d is %d", n, max_prime);
        }
        else
        {
            MPI_Recv(&temp, 2, MPI_INT,
                     0, 0, MPI_COMM_WORLD, &status);

            printf("%d, %d, %d", pid, temp[0], temp[1]);
            int ans[] = {0, 2, temp[0], temp[1]};

            for (int j = temp[0]; j <= temp[1]; j++)
            {
                if (isprime(j))
                {
                    ans[0]++;
                    if (ans[1] < j)
                        ans[1] = j;
                }
            }

            printf("Process %d reports %d primes between %d and %d", pid, ans[0], ans[2], ans[3]);
            MPI_Send(&ans, 4, MPI_INT,
                     0, 0, MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
    return 0;
}