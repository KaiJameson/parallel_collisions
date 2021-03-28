#include <iostream>
#include <fstream>
#include <mpi.h>
#include <unistd.h>
#include <stdlib.h>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <map>
#include <string>
#include <vector>
#include "Satellite.hpp"
#define MCW MPI_COMM_WORLD
using namespace std;

const int EARTH_RADIUS = 6370; //kilometers

// generates random val from 0 to 
float randomFloat(float min, float max) {
  float range = max - min;
  float offset = range * (float)rand() / RAND_MAX;
  return min + offset;
}

// determines whether 2 points are in a threshold distance
bool collision(float point1[], float point2[], float threshold) {
  float x = point2[0] - point1[0];
  float y = point2[1] - point1[1];
  float dist = x*x + y*y;
  return dist < threshold*threshold; // square threshold instead of using sqrt (which has poor performance)
}

int getSatNum(int rank, int size, int num) {
  return rank*size + num;
}

int coordToString(int arr[]) {
  return to_string(arr[0]) + ", " + to_string(arr[1]);
}

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);
  int rank, size;
  MPI_Status mystatus;
  MPI_Comm_rank(MCW, &rank);
  MPI_Comm_size(MCW, &size);
  srand(rank);

  int numSats = 100; // number of satellites per processor
  int coords[2]; // coord array for sending sat positions
  int cycles = 100; // number of time positions per run of the program

  if (rank == 0) {
    for (int i = 0; i < cycles; ++i) {
      map<string, int> locations; // map for detecting collisions
      for (int j = 0; j < size; ++j) {
        for (int k = 0; k < numSats; ++k) {
          MPI_Recv(coords, 2, MPI_INT, j, 0, MCW, MPI_STATUS_IGNORE);
          string coordString = coordToString(coords);
          if (map.count(coordString) != 0) {
            // collision occurred, split satellite up and store collision somewhere
            // if size is used, it would be easier to send a 'split' flag back to the processor with the satellite
            // since the original satellite would also have to be modified (to be smaller) or removed
          }
          else {
            map[coordString] = getSatNum(rank, size, k); // add sat location to map
          }
        }
      }
    }
  }
  else {
    // create satellites
    float minOrbit = 180;
    float maxOrbit = 2000;
    Satellite sats[numSats]
    for (int i = 0; i < numSats; ++i) {
      float perigee = randomFloat(minOrbit, maxOrbit);
      float apogee = randomFloat(minOrbit, maxOrbit);
      float perigeeAngle = randomFloat(0, 2*M_PI);
      float startingAngle = randomFloat(0, 2*M_PI);
      if (perigee > apogee) {
        float tmp = apogee;
        apogee = perigee;
        perigee = tmp;
      }
      sats[i] = Satellite(perigee+EARTH_RADIUS, apogee+EARTH_RADIUS, perigeeAngle, startingAngle); // satSize??? - would not be an actual size, but a unit for collision dist
    }

    for (int i = 0; i < cycles; ++i) {
      for (int j = 0; j < numSats; ++j) {
        sats[j].getPosition(i, coords);
        MPI_Send(coords, 2, MPI_INT, 0, 0, MCW); // send position back to p0 for collision detection
      }
    }
    //receive the satellite information from rank 0
    
    //create satellite objects

    //using this as a guide for determing update information https://www.orbiter-forum.com/threads/so-you-want-to-calculate-orbits.24431/




  }
  MPI_Finalize();

  return 0;
}