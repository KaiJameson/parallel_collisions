#pragma once

class Satellite {
  public:
    Satellite(int perigee, int apogee);
    int getApogee();
    int getPerigee();
    void getPosition(int time, double position[]);
  private:
    int m_perigee;
    int m_apogee;
    int m_sma;
    double m_eccentricity;
    double m_meanMotion;
    double m_orbitalPeriod; //in seconds
    void setEccentricity();
    void setSMA(); //semi major axis
    void setMeanMotion();
    void setOrbitalPeriod();
    double meanAnomaly(int time);
    double eccentricAnomaly(double mAnomaly); //doing 100 iterations because there is no closed form solution
    double trueAnomaly(double eAnomaly);
};



