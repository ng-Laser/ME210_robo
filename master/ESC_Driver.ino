#include <Servo.h>

Servo firstESC; 

void setupESC() {
  firstESC.attach(6); 
  firstESC.writeMicroseconds(0);
}
void test_ESC() { 
  while(!Serial.available()){
    delay(100); 
  }
  int  value = Serial.parseInt();    // Parse an Integer from Serial
  firstESC.writeMicroseconds(value);
}

void shootESC(int time){
    firstESC.writeMicroseconds(1000);
    delay(1000);
    firstESC.writeMicroseconds(1300);
    delay(time);
    firstESC.writeMicroseconds(1000);
    // doesn't currently stop the ESC, if you want to stop write 1000
}
