#include "Encoder.h"
#include "Timer.h"

// Define the pins where the signal A and B are connected on the Arduino
// Note that the pinA must be on an interrupt pin. 
// This official page lists which pins are compatible depending on the board used: https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
const byte pinA = 2;
const byte pinB = 3; 

// Define the reading mode of the encoder.
Constant::EncoderMode mode = Constant::RISING_A;

// Create an object encoder
Encoder myEncoder(pinA, pinB, mode);

// Define a timer with an interval of 100 ms
Timer timer(100);

void setup() 
{ 
  attachInterrupt(digitalPinToInterrupt(pinA), InterruptA, RISING);
  Serial.begin(57600);
}

void loop() 
{
  if(timer.isTime())
    Serial.print(myEncoder.getData());
}

void InterruptA() 
{
  myEncoder.incrementA();
}

