#include "MecanumKinematics.h"

float w = 0.00, vx = 0.00, vy = 0.00; 
float radius, length, width, motorMax = 65.8; 
int flDirPin = 53, flPwmPin = 2;

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
    w = atof(wStr);
    velX = atof(xStr); 
    velY = atof(yStr); 
  } 
}

void drive(float l, float width, float r, float w, float velX, float velY, float motorMax) {
  pinMode(flDirPin, OUTPUT);  
      
  float flMotor = (1/r) * (-w * (l + width) + velX - velY);
  digitalWrite(flMotor, flMotor >= 0 ? HIGH : LOW);
  
  float scaled = fabs(flMotor * (255/motorMax)); 
  analogWrite(flPwmPin, scaled); 
}
