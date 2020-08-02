#include <mpi.h>
#include <iostream>
#include <time.h>

using namespace std;

int main(int argc, char* argv[]) {
	srand(time(0));
	MPI_Init(&argc, &argv);
	int rank = 0, processCount = 0;
	MPI_Comm_size(MPI_COMM_WORLD, &processCount);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (!rank) {
		char buffer[1 + MPI_BSEND_OVERHEAD];
		//char buffer2[1 + MPI_BSEND_OVERHEAD];
		int bufferSize = 1 + MPI_BSEND_OVERHEAD;
		MPI_Buffer_attach(buffer, 1 + MPI_BSEND_OVERHEAD);

		int numberToSend1 = rand() % processCount;
		cout << "Process 0 sent number " << numberToSend1 << endl;

		MPI_Request request1, request2;
		MPI_Ibsend(&numberToSend1, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, &request1);
		MPI_Buffer_detach(buffer, &bufferSize);

		bufferSize = 1 + MPI_BSEND_OVERHEAD;
		MPI_Buffer_attach(buffer, 1 + MPI_BSEND_OVERHEAD);

		int numberToSend2 = rand() % processCount;
		cout << "Process 0 sent number " << numberToSend2 << endl;
		MPI_Ibsend(&numberToSend2, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, &request2);
		MPI_Buffer_detach(buffer, &bufferSize);
	}
	else {
		if (rank == 2) {
			int numberToReceive = 0;
			MPI_Recv(&numberToReceive, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
			cout << "Process 2 received number " << numberToReceive << endl;

			MPI_Recv(&numberToReceive, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
			cout << "Process 2 received number " << numberToReceive << endl;
		};
	};

	MPI_Finalize();

	return 0;
};