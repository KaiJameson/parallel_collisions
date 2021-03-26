#include <iostream>
#include "Satellite.hpp"

const int EARTH_RADIUS = 6370; //kilometers

int main() {
  int perigee = 80+EARTH_RADIUS;
  int apogee = 160+EARTH_RADIUS;
  Satellite sat = Satellite(perigee, apogee);
  double position[1];
  sat.getPosition(400, position);
  std::cout << position[0] << std::endl;
  return 0;
}
