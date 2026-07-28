#include "Display.h"
#include "MecanumKinematics.h"

const int BUFFER = 20;  // bytes
char actionSpace[BUFFER];
int index = 0;  

void setup() {
  Serial.begin(115200);  
  lcdInit(); 
  initGeometry(radius, length, width, 0.0325, 0.0364, 0.102);
}

void loop() { 
  if (Serial.available() > 0) {
    int rawVal = Serial.read();

    if (rawVal != -1) {
      char val = (char)rawVal;
      if (val == '\n') {
        actionSpace[index] = '\0';  // the action space is a string of normalized values ranging from -1 to 1
        index = 0;

        parseActionSpace(actionSpace, w, vx, vy); 
        drive(length, width, radius, w, vx, vy, motorMax); 
      } 
      else if (index < BUFFER - 1) {
        actionSpace[index] = val; 
        index++; 
      }
      else {
        index = 0;
      }
    } 
  }

}
