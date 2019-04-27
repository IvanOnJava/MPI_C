#include <mpi.h> 
#include <iostream>
#define M 5 
int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);   
	int size, rank; 
	int root = 0;     
	MPI_Comm_size(MPI_COMM_WORLD, &size); 
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
	int *send = new int[M]; 
	int *recv = new int[M * size]; 
	printf("Mass %d: ", rank);    
	for (int i = 0; i < M; i++) {  
		send[i] = rand() % 10;  
		printf("%d ", send[i]);    
	}
	printf("\n");  
	double time = MPI_Wtime(); 
	/* Allgather - collects data from all processes (send) and puts this data in (recv) of each process
		send - sent array (Collected from all processes)
		M - the number of sent items
		MPI_INT - data type
		recv - array for the result
	*/
	MPI_Allgather(send, M, MPI_INT, recv, M, MPI_INT, MPI_COMM_WORLD); 
	
	time = MPI_Wtime() - time; 
	printf("Allgather: "); 
	for(int i = 0; i < M * size; i++) {
		printf("%d ", recv[i]);
	}
	if (rank == root) {
		printf(" Time: %f", time);
	}
	
	
	MPI_Finalize(); 
}