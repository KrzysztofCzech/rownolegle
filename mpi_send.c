#include <stdio.h>
#include <mpi.h>
#include <time.h>

int main(int argc, char** argv) {
  MPI_Init(NULL, NULL);
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  if (world_size < 2) {
    printf("World size is smaller than 1 for %s\n", argv[0]);
    MPI_Abort(MPI_COMM_WORLD, 1);
  }
  int number;
  if (world_rank == 0) {
    // If we are rank 0, set the number to -1 and send it to process 1
    number = -1;
    MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    printf("Process 0 send number %d to process 1\n", number);
    MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process 0 received number %d from process 1\n", number);
  } else if (world_rank == 1) {
    MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process 1 received number %d from process 0\n", number);
    number += 10;
    MPI_Send(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    printf("Process 1 send number %d to process 0\n", number);

  }
  MPI_Finalize();
}