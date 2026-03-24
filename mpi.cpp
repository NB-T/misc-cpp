#include <cassert>
#include <iostream>
#include <mpi.h>

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    int rank;
    int size;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Status status;

    double msg[2] = {1, 1};

    if (rank > 0)
    {
        double fibs[2];

        MPI_Recv(fibs, 2, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        double next = fibs[0] + fibs[1];
        msg[0] = fibs[1];
        msg[1] = next;

        std::cout << rank + 2 << "th Fib is " << next << std::endl;
    }

    if (rank + 1 < size)
    {
        int ret = MPI_Send(msg, 2, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD);
        assert(ret == MPI_SUCCESS);
    }

    MPI_Finalize();
    return 0;
}
