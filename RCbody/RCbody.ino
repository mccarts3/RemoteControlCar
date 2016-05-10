#define lmotor 11
#define rmotor 6
#define led1 4
#define led2 7
#define btRx 1   
#define btTx 0     
 
bool ledState;
int driveState;

void setup() {
  pinMode(lmotor, OUTPUT);
  pinMode(rmotor, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  ledState = false;
//  ledClicked = false;
  driveState = 0;
  Serial.begin(9600);
}

void loop() {
  if( Serial.available() )       // if data is available to read
  {
    //Read bluetooth values
    driveState = (int)Serial.read();
    
    if(driveState >= 10)
      ledState = !ledState;
    
    outputLEDs(ledState);
    outputMotors(driveState%10);
  }
}

/*
 * Outputs the LED headlights
 */
void outputLEDs(bool s) {
  if(s) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
  }
  else {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
  }
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
