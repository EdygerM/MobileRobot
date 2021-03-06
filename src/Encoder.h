#ifndef ENCODER_H
#define ENCODER_H

#include "Arduino.h"
#include "Constant.h"

// Incremental Encoder with signal A and signal B in quadrature.
// In mode A, the signal A must be on an interrupt pin (Uno -> pin 2 or 3)
// In mode AB, the signal A and B must be on an interrupt pin.

class Encoder {
  private:
    byte pinA, pinB;
    volatile short data;
    Constant::EncoderMode mode;
    unsigned long previousTime;
    volatile float speed;
    float minRawSpeed, maxRawSpeed; 
        
    void init();
    void risingA();
    void changeA();
    void changeB();
    void subB();
    void addB();
    void addData();
    void subData();
    void computeSpeed(bool isForward);
    float getDeltaTime();
 
  public:
    Encoder(byte pinA, byte pinB);
    Encoder(byte pinA, byte pinB, Constant::EncoderMode mode, float minSpeed, float maxSpeed);
    Encoder(byte pinA, byte pinB, Constant::EncoderMode mode, float minSpeed, float maxSpeed, int startData);
    void incrementA();
    void incrementB();
    int getData();
    float getSpeed();
};

#endif
