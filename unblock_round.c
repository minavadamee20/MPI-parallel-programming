#include <stdio.h>
#include "mpi.h"
//MINA TREVIZO + VIRAAT UDAR
/* Write either a single program or two separate C/C++ programs that use(s) MPI blocking and
non-blocking commands MPI_Send, MPI_Rcvd, MPI_Isend and MPI_Ircvd to exchange one double $
between process with rank 0 and process with rank 1. Calculate the execution time using
MPI_Wtime to compute the execution time
*/

int main(int argc, char *argv[]) {
        int rank, size, number; //might not need number lololol
        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        //MPI time stuff
        double start, end, value;
        start = MPI_Wtime();

        //start with implementing (blocking) MPI_Send, MPI_Rcvd, AND (non-blocking) MPI_Isen$

        MPI_Request ireq;
        MPI_Status  istatus;


        //nonblocking
        if (rank == 0) {
                value = 12.12;
                MPI_Isend(&value, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, &ireq);
                printf("++SENDING : Process %d has sent %f to procces  1++\n", rank, value);

                //PROCESS 0 recieving a new value from PROCESS 1
                MPI_Irecv(&value, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, &ireq);
                MPI_Wait(&ireq, &istatus);
                printf("|| RECIVING: Process %d has recieved %f from process 1||\n", rank ,value);

                //calculating end time
                end = MPI_Wtime();
                printf("\t[Execution time of: %f for process of rank %d\n", end-start, rank);

        }
        else if (rank == 1) {
                MPI_Irecv(&value, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &ireq);
                MPI_Wait(&ireq, &istatus);
                printf("|| RECIVING: Process 1 has recieved number %f from process 0 ||\n", value);

                //PROCESS 1 sending a new value to PROCESS 1
                value = 19.19;
                MPI_Isend(&value, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &ireq);
                //printf("++SENDING: Process %d has sent %f to process 0++\n", rank, value);
                MPI_Wait(&ireq, &istatus);
                printf("++SENDING: Process %d has sent %f to process 0++\n", rank, value);  

                //calculating the time needed to execute this round progression
                //end = MPI_Wtime();
                //printf("\tExecution time of: %f for process of rank %d\n", end - start, rank);

        }
        //end = MPI_Wtime();
        //printf("\tExecution time of: %f for process of rank %d\n", end-start, rank);
        MPI_Finalize();
        return 0;
}



