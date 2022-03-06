#include <iostream>
#include <mpi.h>

using namespace std;

int main()
{
	int comm_sz, my_rank;
	char msg[20];
	MPI_Init(0, 0);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	if (my_rank == 1) {
		MPI_Send("hello", 5 + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
	}
	else if (my_rank == 0) {
		MPI_Recv(msg, 20, MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		cout << msg << endl;
	}

	MPI_Finalize();
}
