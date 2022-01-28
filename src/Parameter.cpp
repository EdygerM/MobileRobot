#include "Parameter.h"

// Motors Parameters
// Pins
byte Parameter::leftWheelPin1      = 10;
byte Parameter::leftWheelPin2      = 8;
byte Parameter::leftWheelpinSleep  = 4;
byte Parameter::rightWheelPin1     = 9;
byte Parameter::rightWheelPin2     = 7;
byte Parameter::rightWheelpinSleep = 5;
byte Parameter::motorSpeedMin      = 5;
byte Parameter::motorSpeedMax      = 255;
bool Parameter::leftWheelTuning    = false; 
bool Parameter::rightWheelTuning   = false;
Constant::MotorMode Parameter::motorMode = Constant::PWM_DIRECTION; 

// Controller
float Parameter::kp = 1;
float Parameter::kd = 0;
float Parameter::ki = 0;

// Encoders Parameters
byte Parameter::rightWheelEncA = 2;
byte Parameter::rightWheelEncB = 11;
byte Parameter::leftWheelEncA  = 3;
byte Parameter::leftWheelEncB  = 13;
Constant::EncoderMode Parameter::encoderMode = Constant::CHANGE_A; 