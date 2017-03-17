#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
//#define n 1000// inser 1000 digits 

int main (int argc , char **argv)
{
int max, rank, nprocs,n,x=0;
int j,i,tsum=0, psum=0 , start, finish;
FILE *fp;
int numbers[200];
MPI_Status status;
MPI_Init(&argc,&argv);//start MPI 
MPI_Comm_size(MPI_COMM_WORLD,&nprocs);//set number of proc
MPI_Comm_rank(MPI_COMM_WORLD,&rank);//set number for ranks 

//start= n*rank/nprocs+1;// set where to start counting 
//finish = n*(rank+1)/nprocs;// last number to count 

//for (i=start;i<=finish;i++)//loop to get summation
//psum+=i;

if (rank==0){

for(i=0;i<200;i++)
numbers[i]=0;


if (NULL ==(fp=fopen("input.txt","r"))){
printf("cant open");
exit(1);
}
fscanf(fp,"%d",&max);

for (i=0;i<max;i++)
fscanf(fp,"%d",&numbers[i]); 

//for (i=1;i<=100;i++)
//numbers[i-1]=numbers[i];

//for (i=0;i<100;i++)
//printf("%d\n",numbers[i]);
}
MPI_Bcast(&max,1,MPI_INT,0,MPI_COMM_WORLD);
MPI_Bcast(&numbers,max,MPI_INT,0,MPI_COMM_WORLD);

start=max*rank/nprocs;
finish=start+(max/nprocs);

for (i=start;i<finish;i++)
psum+=numbers[i];

if (rank!=0){
MPI_Send(&psum,1,MPI_INT,0,23,MPI_COMM_WORLD);
printf("send %d to process %d by proces %d\n",psum,0,rank);
}
if (rank==0){
for (j=1;j<nprocs;j++){
MPI_Recv(&tsum,1,MPI_INT,j,23,MPI_COMM_WORLD,&status);
psum+=tsum;
printf("recieve %d from process %d \n",tsum,j);
}
printf("the total sum is %d \n ",psum);
}

printf("partial sum from process %d of total %d is : %d\n",rank,nprocs,psum);

MPI_Finalize();//finlize Mpi
return 0;
} 

