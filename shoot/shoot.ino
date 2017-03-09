void fireOneShot(){
  while (shot_counter < 1) {
    UpdatePWMDutyCycle();
    int NC = digitalRead(PIN_NC);
  }
    analogWrite(PIN_PWM_OUT, 0);
  }

void shoot(int num_shots){
  startESC();
  for (int i=0; i<num_shots; i++){
    delay(1000);
    Serial.println("calling fire one shot");
    fireOneShot();
    shot_counter = 0;
    turn_counter = 0;
  }
  shot_counter = 0;
  turn_counter = 0;
  turnOffESC();
}

