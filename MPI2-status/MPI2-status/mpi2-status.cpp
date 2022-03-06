#include <iostream>
#include <mpi.h>

using namespace std;


int main()
{
	int comm_sz, my_rank;
	int msg;
	MPI_Status status;
	int count;
	MPI_Init(0, 0);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	if (my_rank == 0) {
		for (int i = 1; i <= 3; i++) {
			MPI_Recv(&msg, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
			MPI_Get_count(&status, MPI_INT, &count);
			cout << "from " << status.MPI_SOURCE << " msg: " << msg << endl;
		}
	}
	else if (my_rank != 0 && my_rank <= 3) {
		MPI_Send(&my_rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();
}
