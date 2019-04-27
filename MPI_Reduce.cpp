#include <mpi.h> // MPI library
#include <iostream>
#define M 10 // The number of elements in the array 
// The command to run from the command line:  mpiexec.exe -n 3 MPI.exe
int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);   // Initialize the MPI environment
	int size, rank; // Create variables for the number of threads (size), process numbers (rank)
	int root = 0;    // Create a variable to memorize the main process.
	MPI_Comm_size(MPI_COMM_WORLD, &size); // We get the number of processes
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); // We get the process number (each process has its own number)
	int *send = new int[M]; // Create an array to send items
	int *recv = new int[M]; // Create an array to get the result.
	printf("Mass %d: ", rank);    // Print to the console the number of the array
	for (int i = 0; i < M; i++) {  
		send[i] = rand() % 10;     // Fill the array with random elements
		printf("%d ", send[i]);    
	}
	printf("\n");  
	double time = MPI_Wtime(); // Get the function start time
	/* Reduce - performs element operations on arrays in processes
		send - dispatched array (collected from all processes)
		recv - array for the result
		M - amount of elements
		MPI_INT - data type
		MPI_MAX - Operation "Element Maximum"
		root - variable to specify the main process (0) in which the result of operations is placed
	*/
	MPI_Reduce(send, recv, M, MPI_INT, MPI_MAX, root, MPI_COMM_WORLD); 
	time = MPI_Wtime() - time; // Calculate the function execution time
	if (rank == root) { // If the process is main, then output the result and time to the console.
		printf("Reduce: ");
		for(int i = 0; i < M; i++) {
			printf("%d ", recv[i]);
		}
		printf(" Time: %f", time);
	}
	MPI_Finalize(); // Shut down the library
}