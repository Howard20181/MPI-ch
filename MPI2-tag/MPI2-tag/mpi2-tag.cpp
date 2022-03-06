#include <iostream>
#include <mpi.h>

using namespace std;

int main()
{
	int comm_sz, my_rank;
	int msg;
	int sum = 0;
	MPI_Init(0, 0);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	if (my_rank == 0) {
		for (int i = 1; i <= 3; i++)
			for (int j = 0; j <= 1; j++) {
				MPI_Recv(&msg, 1, MPI_INT, i, j, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				if (j == 0)
					cout << "from " << i << " msg: " << msg << endl;
				else if (j == 1)
					sum += msg;
			}
		cout << "sum=" << sum << endl;
	}
	else if (my_rank != 0 && my_rank <= 3) {
		MPI_Send(&my_rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		int data = my_rank * 10;
		MPI_Send(&data, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
	}

	MPI_Finalize();
}
