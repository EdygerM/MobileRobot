/* 
 *  Robot.h
 *  
 *  Created: 26.01.22
 *  By: Edy Mariano
 *  
 *  Modified: 26.01.22 
 *  By: Edy Mariano
 *  
 */ 

#ifndef MOBILEROBOT_H
#define MOBILEROBOT_H

#include "Motor.h"
#include "Parameter.h"

class MobileRobot {
  private:
    Motor leftWheel, rightWheel;
    float degreeToRad(float angle) ;
  public:
    MobileRobot();  
    void leftWheelIncrementA();    
    void rightWheelIncrementA();
    void leftWheelIncrementB();    
    void rightWheelIncrementB();
    void move(float linear_vel,float angular_vel);
    int getDataLeftWheel();
    int getDataRightWheel();
};

#endif
