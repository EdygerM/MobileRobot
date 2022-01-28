#include "Parameter.h"

// Motors Parameters
// Pins
byte Parameter::leftWheelPin1      = 10;
byte Parameter::leftWheelPin2      = 8;
byte Parameter::leftWheelpinSleep  = 4;
byte Parameter::rightWheelPin1     = 9;
byte Parameter::rightWheelPin2     = 7;
byte Parameter::rightWheelpinSleep = 5;
// Controller
float Parameter::kp = 1;
float Parameter::kd = 0;
float Parameter::ki = 0;
int Parameter::speedMin = 5;
int Parameter::speedMax = 255;

// Encoders Parameters
byte Parameter::rightWheelEncA = 2;
byte Parameter::rightWheelEncB = 11;
byte Parameter::leftWheelEncA  = 3;
byte Parameter::leftWheelEncB  = 13;
Parameter::Mode Parameter::mode = CHANGE_A; 
int Parameter::encDataMin = -32768;
int Parameter::encDataMax = 32767;
