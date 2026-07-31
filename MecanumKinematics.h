#ifndef __MECANUMKINEMATICS_H__
#define __MECANUMKINEMATICS_H__

#include <Arduino.h>
#include "string.h"
#include <stdint.h>

/*
  ALL MEASURED IN METERS!!!!!!
  r: radius of omni wheel 
  length: from origin (center) of base to center axis of the wheel
  width: perpendicular distance from center of the wheel to the x axis 
  motorMax: the maximum speed each motor can take, which will be used to scale motor speeds into PWM values. This varies with length and width   
*/
typedef struct {
  float length;
  float width;
  float radius;
} Measurement;

typedef struct {
  float w;
  float vx;
  float vy;
  float motorMax;
} Action;  // w, vx, and vy range from -1.0 to 1.0

typedef struct {
  const uint8_t flDir, frDir, rrDir, rlDir;
  const uint8_t flPwm, frPwm, rrPwm, rlPwm;
} MotorPins;

void initGeometry(Measurement &measurements, float rVal, float lVal, float widthVal); 
void parseActionSpace(char *actionString, Action &actions);                     
void drive(Measurement &measurements, Action &actions, MotorPins &motorPins);

#endif  // __MECANUMKINEMATICS_H__
