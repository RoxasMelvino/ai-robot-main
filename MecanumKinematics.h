#ifndef __MECANUMKINEMATICS_H__
#define __MECANUMKINEMATICS_H__

#include <Arduino.h>
#include "string.h"

/*
  inverse kinematics of 4 mecanum wheels
  float flMotor = (1/r) * (-w * (length + width) + vx - vy);
  float frMotor = (1/r) * (w * (length + width) + vx + vy);
  float rrMotor = (1/r) * (w * (length + width) + vx - vy);
  float rlMotor = (1/r) * (-w * (length + width) + vx + vy);
*/


/*
  ALL MEASURED IN METERS!!!!!!
  r: radius of omni wheel 
  length: from origin (center) of base to center axis of the wheel
  width: perpendicular distance from center of the wheel to the x axis 
  motorMax: the maximum speed each motor can take, which will be used to scale motor speeds into PWM values. This varies with length and width   
*/
extern float radius, length, width, motorMax;

extern float w, vx, vy;  // action space values range from -1.0 to 1.0

void initGeometry(float &r, float &l, float &width, float rVal, float lVal, float widthVal); // measure the robot in meters! 
void parseActionSpace(char *action, float &w, float &velX, float &velY);  // action space is a string, so we need to parse it 
void drive(float l, float width, float r, float w, float velX, float velY, float motorMax); 

#endif // __MECANUMKINEMATICS_H__