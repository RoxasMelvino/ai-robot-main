#include "Display.h"
#include "string.h"

float w = 0.0, x = 0.0, y = 0.0 ; // ranges from -1.0 to 1.0

// all should be measured in meters 
float r;      // radius of omni wheel 
float length; // from origin (center) of base to center axis of the wheel
float width;  //  perpendicular distance from center of the wheel to the base's long axis 

/*
inverse kinematics of 4 mecanum wheels
float flMotor = (1/r) * (-w * (length + width) + x - y);
float frMotor = (1/r) * (w * (length + width) + x + y);
float rrMotor = (1/r) * (w * (length + width) + x - y);
float rlMotor = (1/r) * (-w * (length + width) + x + y);
*/

const int BUFFER = 20;  // bytes
char actionSpace[BUFFER];
int index = 0;  

void setup() {
  Serial.begin(115200);  
  lcdInit(); 
}

void loop() { 
  if (Serial.available() > 0) {
    int rawVal = Serial.read();

    if (rawVal != -1) {
      char val = (char)rawVal;
      if (val == '\n') {
        actionSpace[index] = '\0';  // the action space is a string of normalized values ranging from -1 to 1
        index = 0;

        // parse strings here
        char* wStr = strtok(actionSpace, ",");
        char* xStr = strtok(NULL, ","); 
        char* yStr = strtok(NULL, ",");

        if (wStr != NULL && xStr != NULL && yStr != NULL) {
          w = strtof(wStr, NULL); 
          x = strtof(xStr, NULL); 
          y = strtof(yStr, NULL); 

          Serial.print(w);
          Serial.print(" ");
          Serial.print(x);
          Serial.print(" ");
          Serial.println(y);
        }
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

