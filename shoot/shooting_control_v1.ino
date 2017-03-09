#include <Timers.h>
#include <Pulse.h>

//pins
#define PIN_NO      7 //probably not necesary
#define PIN_DIR     9
#define PIN_PWM_OUT 5
#define PIN_NC      3
#define PIN_POT     4

//constants
#define ONE_SEC     1000
#define FULL_POWER  10
#define TIMER_0     0
#define TIME_CONST  5

volatile int shot_counter = 0; // will be incremented by rising edges on pin 2, decremented when we shoot
volatile bool motor_state = false;
volatile bool shoot_mode = false;
volatile int motor_speed = 0;
volatile int turn_counter;
volatile unsigned int counter;

bool disable;
static unsigned int potVal;
static unsigned int signalToggle;

void shotFired(void);
void RespToKey(void);
void UpdatePWMDutyCycle(void);
//void SetupTimerInterrupt(void);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PIN_NO, INPUT);
  pinMode(PIN_NC, INPUT);
  pinMode(PIN_POT, INPUT);
  pinMode(PIN_PWM_OUT, OUTPUT);
  pinMode(PIN_DIR, OUTPUT);
  setupESC();

  potVal = 0;
  motor_state = true;
  counter = 0;
  signalToggle = 0;
  attachInterrupt(0,shotFired,RISING); // pin 2
  //attachInterrupt(1,incrementShot,RISING); // pin 3
}

void loop() {
  int num_shots = 4;
  if(num_shots > 0 ){
    shoot(num_shots);
    while(true){
      delay(100);
    }
  }
  else{
    delay(100);  
  }
}

//Interrupt handler for limit switch
void shotFired(){
 // Serial.println("Switch triggered");
  turn_counter++;
  shot_counter = turn_counter/4;
  delay(100);
}

//void shotFired(){
 // Serial.println("Switch triggered");
  //shot_counter++;
//}


//Only used with potentiometer. Removing POT allows us to move past this piece of code
void UpdatePWMDutyCycle() {
  potVal = analogRead(PIN_POT); //read the value from the potentiometer
  if (motor_state == false) {
     analogWrite(PIN_PWM_OUT, 0);
  } else {
    //Serial.println("updating PWM cycle");
    analogWrite(PIN_PWM_OUT, potVal/4); //analog Read goes from 0 to 1023, analogWrite only goes to 255
   }
  //Serial.println(potVal);
}


//Timer for PWM Duty Cycle to Stepper Motor
ISR(TIMER2_COMPA_vect) {
  if(((counter <= potVal && signalToggle == 1)) && (motor_state == true)) { //duty cycle control, turn the signal high
    digitalWrite(PIN_PWM_OUT, HIGH);
    signalToggle = 0;
  }
  else if(counter > potVal && signalToggle == 0) { //duty cycle control, turn the signal low
    digitalWrite(PIN_PWM_OUT, LOW);
    signalToggle = 1;
  }
  counter++; //increment your counter
  if(counter > 1023) counter = 0; //reset the counter to make sure it stays at 10 bit resolution

}

void SetupTimerInterrupt() {
  cli();                               // Stop interrupts

  //Set Timer2 interrupt at 8kHz
  TCCR2A = 0;                          // Set entire TCCR2A register to 0
  TCCR2B = 0;                          // Same for TCCR2B
  TCNT2  = 0;                          // Initialize counter value to 0

  // Set compare match register to some initial value
  // 199 = (16*10^6) / (1250*64) - 1 (must be <256)
  OCR2A = 99;//199;
  TCCR2A |= (1 << WGM21);              // Turn on CTC mode
  TCCR2B |= (1 << CS22);               // Set CS22 bit for 64 prescaler
  TIMSK2 |= (1 << OCIE2A);             // Enable timer compare interrupt

  sei();                               //Allow interrupts
}
