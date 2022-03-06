#include <iostream>
#include<iomanip>
#include<ctime>
#include <mpi.h>

#define MAX 100000000

using namespace std;

int main(int argc, int argv[])
{
	int comm_sz, my_rank;
	double temp = 0;
	double sum = 0;
	double block = 0;

	MPI_Init(0, 0);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	block = (argc != 1) ? argv[1] : MAX / comm_sz;
	double startNum = (my_rank)*block + 1;
	double endNum = (my_rank + 1) * block;

	cout << setprecision(0);
	cout << "my_rank=" << my_rank << setiosflags(ios::fixed) << " start=" << startNum << " end=" << endNum << endl;
	if (my_rank == 0) {
		cout << setiosflags(ios::fixed) << "block size=" << block << endl;
		for (int i = 1; i < comm_sz; i++) {
			MPI_Recv(&temp, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			sum += temp;
			temp = 0;
			//cout << "sum=" << sum << " rank=" << i << " temp=" << temp << endl;
		}
	}

	for (; startNum <= endNum; startNum++) {
		temp += startNum;
	}
	if (my_rank == 0)
		sum += temp;
	else
		MPI_Send(&temp, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	temp = 0;

	if (my_rank == 0) {
		cout << "并行程序 " << comm_sz << "进程" << endl;
		cout << "sum=" << setiosflags(ios::fixed) << sum << endl;
		cout << setprecision(3);
	}
	cout << "Process " << my_rank << " total time " << (double)clock() / CLK_TCK << "s." << endl;
	MPI_Finalize();
}
