#include "Encoder.h"
#include <util/atomic.h> // ATOMIC_BLOCK macro https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/

Encoder::Encoder(byte pinA, byte pinB) : 
  data(0),
  mode(Constant::RISING_A),
  previousTime(micros()),
  speed(0)
{
  this->pinA = pinA;
  this->pinB = pinB;
  init();
}

Encoder::Encoder(byte pinA, byte pinB, Constant::EncoderMode mode) : 
  data(0)
{
  this->pinA = pinA;
  this->pinB = pinB;
  this->mode = mode;
  init();
}

// Initialize the 2 pins which are reading the quadrature signals A & B.
void Encoder::init() 
{
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
}

// Increment the raw data depending on the reading mode
void Encoder::incrementA() 
{
  if(mode == Constant::RISING_A)
    risingA();
  else if(mode == Constant::CHANGE_A || mode == Constant::CHANGE_AB)
    changeA();
}

// Increment the raw data when signal B interrupt is called
void Encoder::incrementB() 
{
  if(mode == Constant::CHANGE_AB)
    changeB();
}

void Encoder::computeSpeed(bool isForward)
{
  speed = 1/getDeltaTime();
  
  if(!isForward)
    speed *= -1;
}

// Compute time variation between now and the last call
float Encoder::getDeltaTime() 
{
  unsigned long currentTime = micros();
  unsigned long deltaTime = currentTime - previousTime; 
  previousTime = currentTime;
  
  return (float)deltaTime*Constant::toMicro;
}

void Encoder::risingA() 
{
  subB();
}

void Encoder::changeA() 
{
  if(digitalRead(pinA) > 0)
    subB();
  else
    addB();
}

void Encoder::changeB() 
{
  if(digitalRead(pinA) > 0)
    addB();
  else
    subB();
}

void Encoder::subB() 
{
  if(digitalRead(pinB) > 0)
    subData();
  else
    addData();
}


void Encoder::addB() 
{
  if(digitalRead(pinB) > 0)
    addData();
  else
    subData();
}


void Encoder::addData() 
{
  if (data >= Constant::intMax)
    data = Constant::intMin;
  else
    data++;
  computeSpeed(true);
}

void Encoder::subData() 
{
  if (data <= Constant::intMin)
    data = Constant::intMax;
  else
    data--;
  computeSpeed(false);
}

int Encoder::getData() 
{
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    return data;
  }
}

float Encoder::getSpeed()
{
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    return speed;
  }
}
