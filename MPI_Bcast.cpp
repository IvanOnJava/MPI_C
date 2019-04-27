#include <mpi.h> 
#include <iostream>
#define M 5 // The number of elements in the array
// The command to run from the command line:  mpiexec.exe -n 4 MPI.exe
int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);   // Initialize the MPI environment
	int rank; 
	int root = 0;    
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
	int *send = new int[M]; 
	if (rank == root) { 
		printf("Send: ");
		for (int i = 0; i < M; i++) {
			send[i] = rand() % 10;
			printf("%d ", send[i]); 
		}
	}
	printf("\n");  
	double time = MPI_Wtime(); 
	/*Bcast - sends data from the main process (root) to everyone else
		send - send array
		M - the number of elements
		MPI_INT - data type
		root - our variable to specify the main process (0)
	*/
	MPI_Bcast(send, M, MPI_INT, root, MPI_COMM_WORLD); 
	
	time = MPI_Wtime() - time; 
	if (rank != root) { 
		printf("Recv: "); 
		for (int i = 0; i < M; i++) {
			printf("%d ", send[i]);
		}
		printf(" Time: %f", time);
	} 
	MPI_Finalize(); 
}