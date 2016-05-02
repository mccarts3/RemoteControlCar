#define JSClick 13
#define JSx A1
#define JSy A0
byte beginBluetooth;
int x;
int y;

void setup() {
  pinMode(JSClick, INPUT);
  pinMode(JSx, INPUT);
  pinMode(JSy, INPUT);
  Serial.begin(9600);

  x = 0;
  y = 0;
  beginBluetooth = B11110000;
}

void loop() {
  x = analogRead(JSx);
  y = analogRead(JSy);

  bool left = x < 450;
  bool right = x > 520;
  bool forward = y > 520;
  bool back = y < 450;

  
  Serial.write(beginBluetooth);
  writeMotorState(forward, back, left, right);

  bool clicked = digitalRead(JSClick);
  if(clicked) 
    Serial.write(true);
  else
    Serial.write(false);
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
void writeMotorState(bool forward, bool back, bool left, bool right) {
   if(!left && !right && !forward && !back) {
    Serial.write(0);
  }
  else if(left && !forward && !back) {
    Serial.write(1);
  }
  else if(right && !forward && !back) {
    Serial.write(3);
  }
  else if(left && forward) {
    Serial.write(1);
  }
  else if(right && forward) {
    Serial.write(3);
  }
  else if(forward && !left && !right) {
    Serial.write(2);
  }
  else if(back && !left && !right) {
    Serial.write(5);
  }
  else if(back && left) {
    Serial.write(4);
  }
  else {
    Serial.write(6);
  }
}

