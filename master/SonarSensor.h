#ifndef HC_SR04_H
#define HC_SR04_H

#include <Arduino.h>

class SonarSensor {
  public:
    SonarSensor(int triggerPin_in, int echoPin_in);
    void setUp();
	float getDistance();
    float newAvgDistance();
	
  private:
	int triggerPin ,echoPin ;
	float prevVal , secondPrevVal;
};

#endif
