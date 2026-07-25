#include "MecanumKinematics.h"

float w = 0.00, vx = 0.00, vy = 0.00; 
float radius, length, width, motorMax = 65.8; 

void initGeometry(float &r, float &l, float &width, float rVal, float lVal, float widthVal) {
  r = rVal;
  l = lVal;
  width = widthVal;
}

void parseActionSpace(char *action, float &w, float &velX, float &velY) {
  char* wStr = strtok(action, ",");
  char* xStr = strtok(NULL, ","); 
  char* yStr = strtok(NULL, ",");

  if (wStr != NULL && xStr != NULL && yStr != NULL) {
    w = strtof(wStr, NULL); 
    velX = strtof(xStr, NULL); 
    velY = strtof(yStr, NULL); 
  } 
}

void drive(float l, float width, float r, float w, float velX, float velY, float motorMax) {
  float frMotor = (1/r) * (w * (l + width) + velX + velY);
  float scaled = frMotor * (255/motorMax); 
  analogWrite(10, scaled); // pin 10 is hardcoded for now because this is the only motor we have that is connected to a pin
}
