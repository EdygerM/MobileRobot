#include "Encoder.h"
#include "Timer.h"

const byte pinA = 2;
const byte pinB = 3; 

// Define the reading mode of the encoder. RISING_A is by default is no mode is defined (cf. EncoderBasic.ino)
// RISING_A --> interrupt RISING on pinA 
// CHANGE_A --> interrupt CHANGE on pinA: 2x more ticks per revolution
// CHANGE_AB --> interrupt CHANGE on pinA & pinB: 4x more ticks per revolution (the value usually given on the encoder datasheet)
Constant::EncoderMode mode = Constant::CHANGE_AB;

Encoder myEncoder(pinA, pinB, mode);
Timer timer(100);

void setup() 
{ 
  // Call the function InterruptA each time the signal A is changing from LOW to HIGH or from HIGH to LOW
  attachInterrupt(digitalPinToInterrupt(pinA), InterruptA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinB), InterruptB, CHANGE);
  Serial.begin(57600);
}

void loop() 
{
  if(timer.isTime())
    Serial.println(myEncoder.getData());
}

void InterruptA() 
{
  myEncoder.incrementA();
}

void InterruptB() 
{
  myEncoder.incrementB();
}

