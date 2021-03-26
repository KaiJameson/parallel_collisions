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
#include "Satellite.hpp"
#define MCW MPI_COMM_WORLD
using namespace std;


const int EARTH_RADIUS = 6370; //kilometers

int main(int argc, char **argv){
  MPI_Init(&argc, &argv);
  int rank, size;
  MPI_Status mystatus;
  MPI_Comm_rank(MCW, &rank); 
  MPI_Comm_size(MCW, &size); 
  if (rank == 0) {
    //determine perigee and apogee for each satellite
    //can generate 2 numbers between 100 and 160 and just call the larger number apogee, smaller number perigee
  }
  else {
    //receive the satellite information from rank 0
    
    //create satellite objects

    //using this as a guide for determing update information https://www.orbiter-forum.com/threads/so-you-want-to-calculate-orbits.24431/




  }
  MPI_Finalize();

  return 0;
}