/*
Coded by Marjan Olesch
Sketch from Insctructables.com
Open source - do what you want with this code!
*/
#include <Servo.h>


int value = 0; // set values you need to zero

Servo firstESC; //Create as much as Servoobject you want. You can controll 2 or more Servos at the same time

void setup() {

  firstESC.attach(11);    // attached to pin 9 I just do this with 1 Servo
  Serial.begin(9600);    // start serial at 9600 baud - make sure that the console has that setting as well 

}

void loop() {

//First connect your ESC WITHOUT Arming. Then Open Serial and follo Instructions
 
  firstESC.writeMicroseconds(0);
  delay(400);

  firstESC.writeMicroseconds(1000);
  delay(400);
  firstESC.writeMicroseconds(1300);

  Serial.println("done");
  while(true){delay(100);}
  if(Serial.available()) 
    value = Serial.parseInt();    // Parse an Integer from Serial
    //Serial.print(value);
}
