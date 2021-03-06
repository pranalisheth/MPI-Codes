#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

	//INIT MPI World
	MPI_Init(NULL, NULL);

	int rank, world_size;
	//get process rank
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	//get world size
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	int number_amount;
	if (rank == 0) {
		const int MAX_NUMBERS = 100;
		int numbers[MAX_NUMBERS];
		// Pick a random amont of integers to send to process one
		MPI_Send(numbers, MAX_NUMBERS, MPI_INT, 1, 0, MPI_COMM_WORLD);
	}
	else if(rank == 1)
	{
		int dataSize;
		MPI_Status status;
		MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
		MPI_Get_count(&status, MPI_INT, &dataSize);
		//code to recieve data according to sent size
		int* numbersRecieve = new int[dataSize];
		MPI_Recv(numbersRecieve, dataSize, MPI_INT, status.MPI_TAG, status.MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("recieved data size: %d \n", dataSize);
	}


	//Finalize MPI World
	MPI::Finalize();
}
