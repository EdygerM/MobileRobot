#ifndef ENCODER_H
#define ENCODER_H

#include "Arduino.h"
#include "Parameter.h"

// Incremental Encoder with signal A and signal B in quadrature.
// In mode A, the signal A must be on an interrupt pin (Uno -> pin 2 or 3)
// In mode AB, the signal A and B must be on an interrupt pin.

class Encoder {
  private:
    byte pinA, pinB;
    volatile int data;
    Constant::Mode mode;
        
    void init();
    void risingA();
    void changeA();
    void changeB();
    void subB();
    void addB();
    void addData();
    void subData();
 
  public:
    Encoder(byte pinA, byte pinB);
    Encoder(byte pinA, byte pinB, Constant::Mode mode);
    void incrementA();
    void incrementB();
    int getData();
};

#endif
