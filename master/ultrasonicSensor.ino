
//function declarations
void setupPins(void);
float getDistance(int TRIG_PIN, int ECHO_PIN);
void alignWithSideWalls(void);
void alignWithRearWall(void);
void setupSonar(void);
void alignWithWall(void);
void findStartPosition(void);


//pins
//These values can change as necessary
const int TRIG_PIN_RIGHT = 2;
const int ECHO_PIN_RIGHT = 3;
const int TRIG_PIN_FRONT = 9;
const int ECHO_PIN_FRONT = 8;
const int TRIG_PIN_LEFT = 12;
const int ECHO_PIN_LEFT = 10;

//constants
const float FRONT_WALL_THRESHOLD = 6.0;       //Need to determine empirically
const float RIGHT_LEFT_SUM_THRESHOLD = 30.0;  //Need to determine empirically
const float RIGHT_THRESHOLD = 15.0;           //Need to determine empirically
const float LEFT_THRESHOLD = 15.0;            //Need to determine empirically
const unsigned int MAX_DIST = 23200;          //farthest range of ultrasonic sensor

//Helper variables
volatile float leftAverage = 100.0;
volatile float leftPrev = 100.0;
volatile float leftSecond_prev = 100.0;
volatile float rightAverage = 100.0;
volatile float rightPrev = 100.0;
volatile float rightSecond_prev = 100.0;
volatile float frontAverage = 100.0;
volatile float frontPrev = 100.0;
volatile float frontSecond_prev = 100.0;


void setupSonar() {
  setupPins();
}


void setupPins(){
  //Trigger pins
  pinMode(TRIG_PIN_FRONT, OUTPUT);
  digitalWrite(TRIG_PIN_FRONT, LOW);
  pinMode(TRIG_PIN_LEFT, OUTPUT);
  digitalWrite(TRIG_PIN_LEFT, LOW);
  pinMode(TRIG_PIN_RIGHT, OUTPUT);
  digitalWrite(TRIG_PIN_RIGHT, LOW);
  //Echo pins
  pinMode(ECHO_PIN_FRONT, INPUT);
  pinMode(ECHO_PIN_LEFT, INPUT);
  pinMode(ECHO_PIN_RIGHT, INPUT);
}

float getDistance(int TRIG_PIN, int ECHO_PIN){
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

void alignWithFrontWall(){
  while (frontAverage > FRONT_WALL_THRESHOLD) {
    float inches = getDistance(TRIG_PIN_FRONT, ECHO_PIN_FRONT);
    frontAverage = (frontSecond_prev + frontPrev + inches)/3;
    frontSecond_prev = frontPrev;
    frontPrev = inches;
  }
  driveForward(0);
}

void alignWithSideWalls(){
  float rightLeftSum = 100;
  while(rightLeftSum > RIGHT_LEFT_SUM_THRESHOLD) {
    float leftInches = getDistance(TRIG_PIN_LEFT, ECHO_PIN_LEFT);
    float rightInches = getDistance(TRIG_PIN_RIGHT, ECHO_PIN_RIGHT);
    leftAverage = (leftInches + leftPrev + leftSecond_prev)/3;
    rightAverage = (rightInches + rightPrev + rightSecond_prev)/3;
    float rightLeftSum = rightAverage+leftAverage;
    
    rightSecond_prev = rightPrev;
    leftSecond_prev = leftPrev;
    rightPrev = rightInches;
    leftPrev = leftInches;
  }
  driveForward(0);
}

void alignWithWall(){
  alignWithFrontWall();
  delay(1000);
  turn(-105, -1); // Not sure if these values are correct
  alignWithSideWalls();
  while(true){
    delay(100);
  }
}

void findStartPosition(){
  bool positionFound = false;
  while (positionFound == false) {
    float rightInches = getDistance(TRIG_PIN_RIGHT, ECHO_PIN_RIGHT);
    //Serial.println("got distance1");
    float leftInches = getDistance(TRIG_PIN_LEFT, ECHO_PIN_LEFT);
    //Serial.println("got distance2");
    float frontInches = getDistance(TRIG_PIN_FRONT, ECHO_PIN_FRONT);
    //Serial.println("got distance3");
    frontAverage = (frontSecond_prev + frontPrev + frontInches)/3;
    leftAverage = (leftSecond_prev + leftPrev + leftInches)/3;
    rightAverage = (rightSecond_prev + rightPrev + rightInches)/3;
    Serial.print("right distance: ");
    Serial.print(rightAverage);
    Serial.print(" left distance: ");
    Serial.print(leftAverage);
    Serial.print(" front distance: ");
    Serial.println(frontAverage);
    if ((rightAverage >= RIGHT_THRESHOLD) && (frontAverage < 10) && (leftAverage >= LEFT_THRESHOLD)) {
        positionFound = true;
        driveForward(0);
        Serial.println("Start position found");
    }
    //update values for next average
    frontSecond_prev = frontPrev;
    frontPrev = frontInches;
    leftSecond_prev = leftPrev;
    leftPrev = leftInches;
    rightSecond_prev = rightPrev;
    rightPrev = rightInches;
  }
}

