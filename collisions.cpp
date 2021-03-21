#include <iostream>
#include <fstream>
#include <mpi.h>
#include <unistd.h>
#include <stdlib.h>
#include <chrono>
#include <cmath>
#include <map>
#include <algorithm>
#include <vector>
#define MCW MPI_COMM_WORLD
using namespace std;
int main(int argc, char **argv){
  MPI_Init(&argc, &argv);
  int rank, size;
  MPI_Status mystatus;
  MPI_Comm_rank(MCW, &rank); 
  MPI_Comm_size(MCW, &size); 

  MPI_Finalize();

  return 0;
}