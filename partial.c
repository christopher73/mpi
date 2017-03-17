#include <stdio.h>
#include "mpi.h"
#define n 1000// inser 1000 digits 

int main (int argc , char **argv)
{
int rank , nprocs;
int j,i,tsum=0, psum=0 , start, finish;

MPI_Status status;
MPI_Init(&argc,&argv);//start MPI 
MPI_Comm_size(MPI_COMM_WORLD,&nprocs);//set number of proc
MPI_Comm_rank(MPI_COMM_WORLD,&rank);//set number for ranks 

start= n*rank/nprocs+1;// set where to start counting 
finish = n*(rank+1)/nprocs;// last number to count 

for (i=start;i<=finish;i++)//loop to get summation
psum+=i;

if (rank!=0){
MPI_Send(&psum,1,MPI_INT,0,23,MPI_COMM_WORLD);
printf("send %d to process %d by proces %d",psum,0,nprocs);
printf("the total sum is %d \n ",psum);
}
else{
for (j=1;j<nprocs;j++){
MPI_Recv(&tsum,1,MPI_INT,j,23,MPI_COMM_WORLD,&status);
printf("partial sum from process %d of total %d is: %d \n",j,nprocs,tsum);
psum+=tsum;
printf("recieve %d from process %d \n",psum,j);

}
}

MPI_Finalize();//finlize Mpi
return 0;
}
