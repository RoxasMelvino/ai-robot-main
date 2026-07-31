#include "MecanumKinematics.h"

void initGeometry(Measurement &measurements, float rVal, float lVal, float widthVal) {
  measurements.radius = rVal;
  measurements.length = lVal;
  measurements.width = widthVal;
}

void parseActionSpace(char *actionString, Action &actions) {
  char* wStr = strtok(actionString, ",");
  char* xStr = strtok(NULL, ","); 
  char* yStr = strtok(NULL, ",");

  if (wStr != NULL && xStr != NULL && yStr != NULL) {
    actions.w = atof(wStr);
    actions.vx = atof(xStr); 
    actions.vy = atof(yStr); 
  }

  actions.motorMax = 65.8; // hardcode this for now
}

void drive(Measurement &measurements, Action &actions, MotorPins &motorPins) {
  pinMode(motorPins.flDir, OUTPUT);  
  pinMode(motorPins.frDir, OUTPUT);  
  pinMode(motorPins.rrDir, OUTPUT);  
  pinMode(motorPins.rlDir, OUTPUT);  
      
  float flMotor = (1/measurements.radius) * (-actions.w * (measurements.length + measurements.width) + actions.vx - actions.vy);
  float frMotor = (1/measurements.radius) * (actions.w * (measurements.length + measurements.width) + actions.vx + actions.vy);
  float rrMotor = (1/measurements.radius) * (actions.w * (measurements.length + measurements.width) + actions.vx - actions.vy);
  float rlMotor = (1/measurements.radius) * (-actions.w * (measurements.length + measurements.width) + actions.vx + actions.vy);
  
  digitalWrite(motorPins.flDir, motorPins.flDir >= 0 ? HIGH : LOW);
  digitalWrite(motorPins.frDir, motorPins.frDir >= 0 ? HIGH : LOW);
  digitalWrite(motorPins.rrDir, motorPins.rrDir >= 0 ? HIGH : LOW);
  digitalWrite(motorPins.rlDir, motorPins.rlDir >= 0 ? HIGH : LOW);
  
  float scaled = fabs(flMotor * (255/actions.motorMax)); 
  analogWrite(motorPins.flPwm, scaled); 
}
