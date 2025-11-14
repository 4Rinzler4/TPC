#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    int A[15] = {3, -2, 7, -5, 9, -1, 4, -8, 6, 2, -3, 5, -6, 1, -4};

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        if (rank == 0)
            printf("Need program with 2 process\n");
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        int S1 = 0;
        for (int i = 0; i < 15; i++)
            if (A[i] > 0)
                S1 += A[i];

        int S2;
        MPI_Recv(&S2, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Positive sum S1 = %d\n", S1);
        printf("Negative product S2 = %d\n", S2);
    }
    else if (rank == 1) {
        int S2 = 1;
        for (int i = 0; i < 15; i++)
            if (A[i] < 0)
                S2 *= A[i];

        MPI_Send(&S2, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
