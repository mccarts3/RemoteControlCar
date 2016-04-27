#define lmotor 11
#define rmotor 6
#define leds 2
#define btRx 1      // Need to implement
#define btTx 0      // Need to implement
bool ledState;
bool ledClicked;
int motorState;

void setup() {
  pinMode(lmotor, OUTPUT);
  pinMode(rmotor, OUTPUT);
  pinMode(leds, OUTPUT);
  ledState = false;
  ledClicked = false;
  motorState = 0;
}

void loop() {
  //Read bluetooth values
  //motorState = Serial.read();
  //ledClicked = Serial.read();
  
  if(ledClicked) {
    ledState = !ledState;
    outputLEDs(ledState);
    delay(500);
  }
  
  outputMotors(motorState);
}

/*
 * Outputs the LED headlights
 */
void outputLEDs(bool s) {
  if(s) 
    digitalWrite(leds, HIGH);
  else
    digitalWrite(leds, LOW);
}

/*
 * Diagaram of states:
 *          s == 2
 * s == 1              s == 3
 *          s == 0 
 * s == 4  If time     s == 6  If time   
 *          s == 5  If time
 */
void outputMotors(int s) {
  if(s == 0) {                // No movement
    analogWrite(lmotor, 0);
    analogWrite(rmotor, 0);
  } else if(s == 1) {         // Turn left
    analogWrite(lmotor, 75);
    analogWrite(rmotor, 255);
  } else if(s == 2) {         // Move forward
    analogWrite(lmotor, 255);
    analogWrite(rmotor, 255);
  } else if(s == 3) {         // Turn right
    analogWrite(lmotor, 255);
    analogWrite(rmotor, 75);
  } else {
    analogWrite(lmotor, 0);
    analogWrite(rmotor, 0);
  }
}
