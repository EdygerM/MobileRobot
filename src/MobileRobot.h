#ifndef MOBILEROBOT_H
#define MOBILEROBOT_H

#include "Motor.h"
#include "Encoder.h"

class MobileRobot {
  private:
    PID leftController, rightController;
    Motor leftWheel, rightWheel;
    Encoder leftEncoder, rightEncoder;
    float previousLinearSpeed, previousAngularSpeed;
    float degreeToRad(float angle);
    void initInterrupt();
  public:
    MobileRobot();  
    void leftWheelIncrementA();    
    void rightWheelIncrementA();
    void leftWheelIncrementB();    
    void rightWheelIncrementB();
    void move(float linear_vel,float angular_vel);
    int getDataLeftWheel();
    int getDataRightWheel();
    float setSpeed(float speedCommand, float previousSpeed, float maxDeltaSpeed);
};

#endif
