/* 
 *  Manage speed of a DC motor with PWM. Must be coupled with an incremental encoder
 *  
 *  Compatible with the majority of popular DC Motor drivers for Arduino. 
 *  For examples: DRV8833 (Texas Instrument)
 *                TB9051FTG (Toshiba)
 *                L298N (STMicroelectronics) 
 *                
 *  The driver is chosen depending on the maximum current drawned by the motor
 *  There are two modes : pin1: PWM, pin2: Direction (CW/CCW)
 *                        pin1: PWM CW, pin2: PWM CCW
 *  If the motor driver has no sleep pin, set pinSleep as 0
 *  
 *  For details about encoders parameters, check Encoder.h
 *  For details about the controller parameters, check PID.h
 */ 

#ifndef MOTOR_H
#define MOTOR_H

#include "Encoder.h"
#include "PID.h"
#include "Constant.h"

class Motor {
  private:
    byte pin1, pin2, pinSleep;
    unsigned long previousTime;
    int previousPos;
    byte minPWM, maxPWM;
    PID controller; 
    Constant::MotorMode mode;
    float div;
    float previousSpeed;

    void init();
    float getDeltaTime();
    float getSpeedPWM(float speed);
    void sleepManagement(byte speedCommand, int speedMeasure);
    bool isForward(float speedOutput) ;
    void setMotor(byte speedPWM, bool isForward); 
    
  public:
    Motor(byte pin1, byte pin2, byte pinSleep, Constant::MotorMode mode, PID controller);
    Motor(byte pin1, byte pin2, byte pinSleep, Constant::MotorMode mode, PID controller, byte minPWM, byte maxPWM);  
    void setSpeed(float speedSetpoint, bool speedTuning, float speed, float maxDeltaSpeed);          
};

#endif
