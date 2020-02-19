
#include <stdio.h>
#include "mpi.h"

/* Write either a single program or two separate C/C++ programs that use(s) MPI blocking and
non-blocking commands MPI_Send, MPI_Rcvd, MPI_Isend and MPI_Ircvd to exchange one double $
between process with rank 0 and process with rank 1. Calculate the execution time using
MPI_Wtime to compute the execution time
*/



int main(int argc, char *argv[]) {
        int rank, size, number; //might not need number lololol
        double start, end, value;
        MPI_Request ireq;
        MPI_Status istatus;

                 MPI_Init( &argc, &argv );
                 MPI_Comm_rank( MPI_COMM_WORLD, &rank );
                 MPI_Comm_size( MPI_COMM_WORLD, &size );
                 printf( "I am %d of %d\n", rank, size );
                        start = MPI_Wtime();
                // int number=0;
                 if (rank == 0) {
                           value = 13.13;
                           MPI_Send(&value, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
                           printf("Process 0 sent number %f to process  1\n", value);
                 } else if (rank == 1) {
                         MPI_Recv(&value, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                         end = MPI_Wtime();
                         printf("\tExecution time of: %f for proess rank of %d\n", end-start, rank);
                         printf("Process 1 received number %f from process 0\n", value);
                 }
                        //end = MPI_Wtime();
                        //printf("\t[Execution time of: %f for rank %d\n", end-start, rank);
                // printf(" Process %d has number=%f\n\n\n", rank, value);
                 MPI_Finalize();



return 0;
}

