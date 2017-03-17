#include <stdio.h>
#include <math.h>
#include "mpi.h"

//const int MAX=16;

int main(int argc, char **argv) {

  MPI_Status status;
  int arr[16];//assuming we have 16 nods
  int i,value[1];
  srand(time(0));	
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs); 
  	
  if(rank==0) {
    for (i=0;i<nprocs;i++)
      arr[i]=rand()%257;//creates random numbers 
  }
  MPI_Scatter(&arr,1,MPI_INT,&value, 1, MPI_INT, 0, MPI_COMM_WORLD);//sends value to all nodes
  
  for(i=0;i<nprocs;i++) {
    if(i%2 == 0) {// even 
      if(rank%2 == 0) {
        MPI_Send(&value[0],1,MPI_INT,rank+1,0,MPI_COMM_WORLD);
        MPI_Recv(&value[1],1,MPI_INT,rank+1,0,MPI_COMM_WORLD,&status);
        if(value[1]<value[0]) {
          value[0] = value[1];
        }
      }
      else {
        MPI_Recv(&value[1],1,MPI_INT,rank-1,0,MPI_COMM_WORLD,&status);
        MPI_Send(&value[0],1,MPI_INT,rank-1,0,MPI_COMM_WORLD);
        if(value[1]>value[0])
          value[0] = value[1];
      }
    }
    else {//odd
      if((rank%2 == 1) && (rank != (nprocs-1))) {
        MPI_Send(&value[0],1,MPI_INT,rank+1,0,MPI_COMM_WORLD);
        MPI_Recv(&value[1],1,MPI_INT,rank+1,0,MPI_COMM_WORLD,&status);
        if(value[1]<value[0]) 
          value[0] = value[1];
      }
      else if(rank != 0 && rank != (nprocs-1)) {
        MPI_Recv(&value[1],1,MPI_INT,rank-1,0,MPI_COMM_WORLD,&status);
        MPI_Send(&value[0],1,MPI_INT,rank-1,0,MPI_COMM_WORLD);
        if(value[1]>value[0])
          value[0] = value[1];
      }
    }
  } 
  
   MPI_Gather(&value[0],1,MPI_INT,&arr[0],1,MPI_INT,0,MPI_COMM_WORLD);//gatther vAlues
  if(rank==0) {
    printf("Sorted array: ");
    for (i=0;i<nprocs;i++) {
      printf("%d ", arr[i]);
    }
    printf("\n");
  }
  MPI_Finalize();
  return 0;
}

 