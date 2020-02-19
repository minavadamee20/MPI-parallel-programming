#include <stdio.h>
#include "mpi.h"

/* Write either a single program or two separate C/C++ programs that use(s) MPI blocking and
   non-blocking commands MPI_Send, MPI_Rcvd, MPI_Isend and MPI_Ircvd to exchange one double value
   between process with rank 0 and process with rank 1. Calculate the execution time using
   MPI_Wtime to compute the execution time
*/
int main(int argc, char *argv[]){
        int rank, size, number; //might not need number lololol
        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

//MPI time stuff
        double start, end, value;
        start = MPI_Wtime();
//start with implementing (blocking) MPI_Send, MPI_Rcvd, AND (non-blocking) MPI_Isend, MPI_Ircvd [need to use MPI_Wait for this one]
        MPI_Request ireq;
        MPI_Status  istatus;


//nonblocking
        if(rank==0){
                value = 12.12;
                MPI_Isend(&value, 1,MPI_DOUBLE, 1,0,MPI_COMM_WORLD, &ireq);
                MPI_Wait(&ireq, &istatus);
                printf("\tProces 0 has sent %f to process 1\n", value);
        }
        else if(rank ==1){
                MPI_Irecv(&value, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &ireq);
                MPI_Wait(&ireq, &istatus);
                printf("\tProcess 1 has recieved number %f from process 0\n", value);
                end = MPI_Wtime();
                printf("\tExecution time of: %f for process of rank %d\n", end-start, rank);
        }
        //end = MPI_Wtime();
        //printf("\tExecution time of: %f for process of rank %d\n", end-start, rank);
        printf("Process %d has the number = %f\n", rank, value);
        MPI_Finalize();
        return 0;
}


