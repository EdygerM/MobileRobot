#include "Encoder.h"
#include <util/atomic.h> // For the ATOMIC_BLOCK macro

Encoder::Encoder(byte pinA, byte pinB) : 
  mode(Parameter::RISING_A), 
  data(0)
{
  this->pinA = pinA;
  this->pinB = pinB;
  init();
}

Encoder::Encoder(byte pinA, byte pinB, Parameter::Mode mode) : 
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

// Increment the raw data when signal A interrupt is called
// Depending on the mode, 
void Encoder::incrementA() 
{
  switch(mode){
    case Parameter::RISING_A:
      risingA();
      break;
    case Parameter::CHANGE_A:
    case Parameter::CHANGE_AB:
      changeA();
      break;
    default:
      break;
  }
}

// Increment the raw data when signal B interrupt is called
void Encoder::incrementB() 
{
  if(mode == Parameter::CHANGE_AB)
    changeB();
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
  if (data >= Parameter::encDataMax)
    data = Parameter::encDataMin;
  else
    data++;
}

void Encoder::subData() 
{
  if (data <= Parameter::encDataMin)
    data = Parameter::encDataMax;
  else
    data--;
}

int Encoder::getData() 
{
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    return data;
  }
}
