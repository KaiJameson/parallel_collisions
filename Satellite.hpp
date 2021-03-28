#pragma once
class Satellite {
  public:
    Satellite(float perigee, float apogee, float perigeeAngle, float startingAngle);
    float getApogee() {return m_apogee;}
    float getPerigee() {return m_perigee;}
    float getPerigeeAngle() {return m_perigeeAngle;}
    float getStartingAngle() {return m_startingAngle;}
    void getPosition(int time, int position[]);
  private:
    float m_perigee;
    float m_apogee;
    float m_perigeeAngle;
    float m_startingAngle;
    float m_sma;
    double m_eccentricity;
    double m_meanMotion;
    int m_orbitalPeriod; //in seconds
    void setEccentricity();
    void setSMA(); //semi major axis
    void setMeanMotion();
    void setOrbitalPeriod();
    double meanAnomaly(int time);
    double eccentricAnomaly(double mAnomaly); //doing 100 iterations because there is no closed form solution
    double trueAnomaly(double eAnomaly);
    double altitude(double eAnomaly);

};



