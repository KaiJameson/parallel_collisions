#include "Satellite.hpp"
#include <cmath>
//g as gravitational constant from https://en.wikipedia.org/wiki/Gravitational_constant
const double G = 6.674 * pow(10,-11);
const int M_EARTH = 5.972 * pow(10,24);
Satellite::Satellite(int perigee, int apogee) {
  m_perigee = perigee;
  m_apogee = apogee;
  setSMA();
  setEccentricity();
  setMeanMotion();
  setOrbitalPeriod();
}
int Satellite::getApogee() {
  return m_apogee;
}
int Satellite::getPerigee() {
  return m_perigee;
}
void Satellite::setEccentricity() {
  m_eccentricity = static_cast<double>(m_apogee-m_perigee) / static_cast<double>(m_apogee+m_perigee);
}
void Satellite::setSMA() {
  m_sma = (m_apogee+m_perigee)/2;
}
void Satellite::setMeanMotion() {
  m_meanMotion = sqrt(static_cast<double>(G*M_EARTH) / pow(m_sma,3));
}
void Satellite::setOrbitalPeriod() {
  m_orbitalPeriod = (2*M_PI) * sqrt( static_cast<double>(pow(m_sma,3)) / (G*M_EARTH));
}
double Satellite::meanAnomaly(int time) {
  return m_meanMotion * time;
}
double Satellite::eccentricAnomaly(double mAnomaly) {
  double e0 = mAnomaly;
  for (int i=0; i<100; i++) {
    e0 = e0 - ((e0-(m_eccentricity*sin(e0))-mAnomaly)/(1-(m_eccentricity * cos(e0))));
  }
  return e0;
}
double Satellite::trueAnomaly(double eAnomaly) {
  return acos((cos(eAnomaly)-m_eccentricity)/(1-(m_eccentricity*cos(eAnomaly))));
}
void Satellite::getPosition(int time, double position[]) {
  //working on understanding this part
  double mAnomaly = meanAnomaly(time);
  double eAnomaly = eccentricAnomaly(mAnomaly);
  position[0] = trueAnomaly(eAnomaly);
}







