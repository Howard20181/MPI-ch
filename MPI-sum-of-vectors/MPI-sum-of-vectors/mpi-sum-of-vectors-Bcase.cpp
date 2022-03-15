#include <iostream>
#include <mpi.h>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc == 1) {
		cout << "ERROR: Parameter is empty" << endl;
		return -1;
	}
	if (atoi(argv[1]) % 2 != 0) {
		cout << "WARN: Matrix elements not even" << endl;
		return -2;
	}
	int comm_sz, my_rank;
	int vector_size = 0;
	vector<int> x;
	vector<int> y;
	vector<int> z;

	char p_name[MPI_MAX_PROCESSOR_NAME];
	int p_namelen;

	MPI_Init(0, 0);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	MPI_Get_processor_name(p_name, &p_namelen);

	//cout << "rank " << my_rank << " on " << p_name << endl;

	if (my_rank == 0) {
		vector_size = atoi(argv[1]);

		for (int i = 2; i <= atoi(argv[1]) + 1; i++)
			x.push_back(atoi(argv[i]));

		for (int i = atoi(argv[1]) + 2; i <= atoi(argv[1]) * 2 + 1; i++)
			y.push_back(atoi(argv[i]));

		cout << "x=";
		for (int c : x) cout << c << " ";
		cout << endl;

		cout << "y=";
		for (int c : y) cout << c << " ";
		cout << endl;
	}

	MPI_Bcast(&vector_size, 1, MPI_INT, 0, MPI_COMM_WORLD);
	x.resize(vector_size);
	y.resize(vector_size);

	MPI_Bcast(x.data(), vector_size, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(y.data(), vector_size, MPI_INT, 0, MPI_COMM_WORLD);

	vector<int> temp_vector;
	temp_vector.resize(2);
	for (int i = 0; i <= 1; i++) {
		temp_vector[i] = x[my_rank * 2 + i] + y[my_rank * 2 + i];
	}
	if (my_rank == 0) z.resize(comm_sz * temp_vector.size());
	MPI_Gather(temp_vector.data(), 2, MPI_INT, z.data(), 2, MPI_INT, 0, MPI_COMM_WORLD);
	if (my_rank == 0) {
		cout << "z=";
		for (int c : z) cout << c << " ";
		cout << endl;
	}
	//cout << "Rank " << my_rank << " total time " << (double)clock() / CLK_TCK << "s." << endl;
	MPI_Finalize();
}