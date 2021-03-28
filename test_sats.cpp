#include <iostream>
#include "Satellite.hpp"

const int EARTH_RADIUS = 6370; //kilometers

int main() {
  int perigee = 80+EARTH_RADIUS;
  int apogee = 160+EARTH_RADIUS;
  Satellite sat = Satellite(perigee, apogee);
  int position[2];
  sat.getPosition(400, position);
  std::cout << position[0] << "," << position[1] << std::endl;
  return 0;
}
