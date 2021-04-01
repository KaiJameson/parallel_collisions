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

struct SatId {
    int rank;
    int num;
};

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


string coordToString(int arr[]) {
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
  int cycles = 365; // number of time positions per run of the program
  int collisionCount = 0;
  if (rank == 0) {
    for (int i = 0; i < cycles; ++i) {
      map<string, SatId> locations; // map for detecting collisions
      for (int j = 1; j < size; ++j) {
        for (int k = 0; k < numSats; ++k) {
          //flagging as i to make sure that things are on the same cycle
          MPI_Recv(coords, 2, MPI_INT, j, i, MCW, MPI_STATUS_IGNORE);
          string coordString = coordToString(coords);
          if (locations.count(coordString) != 0) {
            collisionCount ++;
            // collision occurred, split satellite up and store collision somewhere
            // if size is used, it would be easier to send a 'split' flag back to the processor with the satellite
            // since the original satellite would also have to be modified (to be smaller) or removed

          }
          else {
            //when the processes have a different number of satellites, this formula will break
            //actually isn't this formula always broken when k > size?
            SatId si;
            si.rank = j;
            si.num = k;
            locations[coordString] = si; // add sat location to map
          }
        }
      }
    }
    cout << "There were " << collisionCount << " collisions in the year" << endl;
  }
  else {
    // create satellites
    float minOrbit = 180;
    float maxOrbit = 2000;
    Satellite sats[numSats];
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
      sats[i] = Satellite(perigee+EARTH_RADIUS, apogee+EARTH_RADIUS, perigeeAngle, startingAngle, 10); // satSize??? - would not be an actual size, but a unit for collision dist
    }

    for (int i = 0; i < cycles; ++i) {
      for (int j = 0; j < numSats; ++j) {
        sats[j].getPosition(i, coords);
        //tagging as i to make sure the cycle information is understood
        MPI_Send(coords, 2, MPI_INT, 0, i, MCW); // send position back to p0 for collision detection
      }
      //get all collision information
      //make the new satellites/split old ones
      //MPI_RECV() //end flag
    }
    //receive the satellite information from rank 0
    
    //create satellite objects

    //using this as a guide for determing update information https://www.orbiter-forum.com/threads/so-you-want-to-calculate-orbits.24431/




  }
  MPI_Finalize();

  return 0;
}