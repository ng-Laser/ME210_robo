 #include <Timers.h> // for sonar

// Sonar sensor Pins/variables
const int TRIG_PIN = 3;
const int ECHO_PIN = 2;
volatile float previous = 100.0;
volatile float second_previous = 101.0;
volatile float running_average = 100;
volatile float minimum_average = 1000;

// Anything over 400 cm (23200 us pulse) is "out of range"
const unsigned int MAX_DIST = 23200;
const float THRESHOLD = 0.2;

void determineMinimum(void);
void turnToMinimum(void);
float getDistance(void);

// end sonar sensor stuff 

void setupSonar(){
  // The Trigger pin will tell the sensor to range find
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
}

void alignWithWall(){
  determineMinimum();    
  turnToMinimum();
}
  
void determineMinimum(){
  TMRArd_InitTimer(0,5000);
  while(!((unsigned char)TMRArd_IsTimerExpired(0))){
    float inches = getDistance();
    running_average = (second_previous+previous+inches)/3;
    if (running_average < minimum_average) minimum_average = running_average;
    second_previous = previous;
    previous = inches;
    Serial.print("average: ");
    Serial.print(running_average);
    Serial.print("minimum: ");
    Serial.print(minimum_average);
  }     
}

void turnToMinimum(){
  while(true){
    float inches = getDistance();
    running_average = (second_previous+previous+inches)/3;
    if (running_average < minimum_average + THRESHOLD) {
      Serial.println("Stop");
      driveForward(0);   //Stop motors
      break;
    }
    Serial.print("average: ");
    Serial.print(running_average);
    Serial.print("minimum: ");
    Serial.print(minimum_average);
       
    second_previous = previous;
    previous = inches;      
  }
}

float getDistance(){
  unsigned long t1;
  unsigned long t2;
  unsigned long pulse_width;
  float cm;
  float inches;
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  while ( digitalRead(ECHO_PIN) == 0 );
  t1 = micros();
  while ( digitalRead(ECHO_PIN) == 1);
  t2 = micros();
  pulse_width = t2 - t1;
  inches = pulse_width / 148.0;
  return inches; 
}
