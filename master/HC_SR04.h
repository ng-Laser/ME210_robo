#ifndef HC_SR04_H
#define HC_SR04_H

#include <Arduino.h>

class HC_SR04 {
  public:
    HC_SR04(int triggerPin_in, int echoPin_in);
    void setUp();
	float HC_SR04::getDistance();
    
  private:
	int triggerPin ,echoPin ;
	float prevVal , secondPrevVal;
};

#endif
