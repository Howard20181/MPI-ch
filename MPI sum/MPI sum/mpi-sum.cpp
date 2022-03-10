#include <iostream>
#include<iomanip>
#include<ctime>
#include <mpi.h>
#include <cstdlib>

#define MAX 100000000

using namespace std;

int main(int argc, char* argv[])
{
	int comm_sz, my_rank;
	double temp = 0;
	double sum = 0;
	double block = 0;

	char p_name[MPI_MAX_PROCESSOR_NAME];
	int p_namelen;

	MPI_Init(0, 0);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	MPI_Get_processor_name(p_name, &p_namelen);

	cout << "rank " << my_rank << " on " << p_name << endl;

	double tp = (argc != 1) ? atof(argv[1]) : MAX;
	block = tp / comm_sz;

	double startNum = my_rank * block + 1;
	double endNum = (my_rank + 1) * block;

	cout << setprecision(0);
	//cout << "my_rank=" << my_rank << setiosflags(ios::fixed) << " start=" << startNum << " end=" << endNum << endl;
	if (my_rank == 0) {
		cout << setiosflags(ios::fixed) << "block size=" << block << endl;
		for (int i = 1; i < comm_sz; i++) {
			MPI_Recv(&temp, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			sum += temp;
			temp = 0;
			//cout << "sum=" << sum << " rank=" << i << " temp=" << temp << endl;
		}
	}

	while (startNum <= endNum)
	{
		temp += startNum;
		startNum++;
	}

	if (my_rank == 0)
		sum += temp;
	else
		MPI_Send(&temp, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	temp = 0;

	if (my_rank == 0) {
		cout << "Comm_size " << comm_sz << endl;
		cout << "sum=" << setiosflags(ios::fixed) << sum << endl;
		cout << setprecision(3);
	}
	cout << "Rank " << my_rank << " total time " << (double)clock() / CLK_TCK << "s." << endl;
	MPI_Finalize();
}
