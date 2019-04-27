#include <mpi.h> 
#include <iostream>
#define M 15 
int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);   
	int rank, size; 
	MPI_Status status;
	int root = 0;   
	MPI_Comm_size(MPI_COMM_WORLD, &size); 
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
	int *send = new int[M]; 
	int *recv = new int[M]; 
	if (rank == root) { 
		printf("Send: ");
		for (int i = 0; i < M; i++) {
			send[i] = i * rand() % 10;
			printf("%d ", send[i]); 
		}
	}
	printf("\n");  
	double time = MPI_Wtime(); 
	if(rank == root)
		for(int i = 1; i < size; i++)
		/* Send - sends a message to a specific process.
			send - send array
			M - the number of elements
			MPI_INT - data type
			i - the number of the process to which we send the message
			1 - tag, needed to separate the processes by tags
		*/
		MPI_Send(send, M, MPI_INT, i, 1, MPI_COMM_WORLD); 
	if (rank != root) {
		/* Recv - accepts a message from a specific process
			recv - the array in which we accept
			M - the number of elements
			MPI_INT - data type
			0 - the number of the process from which we receive the message
			1 - tag, needed to separate the processes by tags (not interesting in our case)
		*/
		MPI_Recv(recv, M, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		printf("Recv: "); //выводим результат и время на консоль
		for (int i = 0; i < M; i++) {
			printf("%d ", recv[i]);
		}
	}
	time = MPI_Wtime() - time; 
		if(rank == root)
			printf(" Time: %f", time);
	
	MPI_Finalize(); 
}