#define JSClick 13
#define JSx A1
#define JSy A0
int x;
int y;

void setup() {
  pinMode(JSClick, INPUT);
  pinMode(JSx, INPUT);
  pinMode(JSy, INPUT);
  Serial.begin(9600);

  x = 0;
  y = 0;
}

void loop() {
  x = analogRead(JSx);
  y = analogRead(JSy);

  bool left = x < 450;
  bool right = x > 520;
  bool forward = y > 520;
  bool back = y < 450;
  bool clicked = !digitalRead(JSClick);
  
  //Serial write for motor state
  writeMotorState(forward, back, left, right, clicked);
}

/*
 * Writes the motor state value to the serial port
 * which is then sent to the other Arduino via Bluetooth
 * 
 * Diagaram of states:
 *          s == 2
 * s == 1              s == 3
 *          s == 0 
 * s == 4  If time     s == 6  If time   
 *          s == 5  If time
 */
void writeMotorState(bool forward, bool back, bool left, bool right, bool clicked) {
  int driveState = 0;
  
  if(!left && !right && !forward && !back)
    driveState = 0;
  else if(left && !forward && !back)
    driveState = 1;
  else if(right && !forward && !back)
    driveState = 3;
  else if(left && forward)
    driveState = 1;
  else if(right && forward)
    driveState = 3;
  else if(forward && !left && !right)
    driveState = 2;
  else if(back && !left && !right)
    driveState = 5;
  else if(back && left)
    driveState = 4;
  else
    driveState = 6;

  if(clicked)
    driveState += 10;

  Serial.write(driveState);
}

