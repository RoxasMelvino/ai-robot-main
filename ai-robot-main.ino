#include "Display.h"
#include "MecanumKinematics.h"

Action actions = {0.00, 0.00, 0.00, 65.8}; // w, vx, vy, motorMax 
Measurement measurements;
MotorPins motorPins = {53, 51, 49, 47, 2, 3, 4, 5}; // only pins 53 (dir) and 2 (pwm) are wired so far
 
const int BUFFER = 20;  // bytes
char actionSpaceString[BUFFER];
int index = 0;  

void setup() {
  Serial.begin(115200);  
  lcdInit(); 
  initGeometry(measurements, 0.0325, 0.0364, 0.102);
}

void loop() { 
  if (Serial.available() > 0) {
    int rawVal = Serial.read();

    if (rawVal != -1) {
      char val = (char)rawVal;
      if (val == '\n') {
        actionSpaceString[index] = '\0';  // the action space is a string of normalized values ranging from -1 to 1
        index = 0;

        parseActionSpace(actionSpaceString, actions); 
        drive(measurements, actions, motorPins); 
      } 
      else if (index < BUFFER - 1) {
        actionSpaceString[index] = val; 
        index++; 
      }
      else {
        index = 0;
      }
    } 
  }

}
