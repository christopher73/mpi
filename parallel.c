#include "mpi.h"

#include <stdio.h>

#define N 1000

main(int argc, char *argv[]) {

 MPI_Status status;

 MPI_Request request;

 int send_buf[N], recv_buf[N];

 int send_sum = 0, recv_sum = 0;

 int rank, left, nprocs, msg_id, i;

 MPI_Init(&argc, &argv);

 MPI_Comm_rank(MPI_COMM_WORLD, &rank);

 MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

 left = (rank+ nprocs - 1) % nprocs;

 for (i=0; i<N; i++) 
send_buf[i] = rank*N + i;


MPI_Irecv(recv_buf, N, MPI_INT, MPI_ANY_SOURCE, 777, MPI_COMM_WORLD,&request); /* Post a receive */


MPI_Send(send_buf, N, MPI_INT, left, 777, MPI_COMM_WORLD);

for (i=0; i<N; i++) send_sum += send_buf[i];
MPI_Wait(&request, &status); /* Complete the receive */

 /* Now it's safe to use recv_buf */

for (i=0; i<N; i++)
recv_sum += recv_buf[i];

printf("Node %d: Send %d Recv %d\n", rank, send_sum, recv_sum);

MPI_Finalize();

}
