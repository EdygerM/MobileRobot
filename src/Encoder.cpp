#include "Encoder.h"
#include <util/atomic.h> // ATOMIC_BLOCK macro https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/

Encoder::Encoder(byte pinA, byte pinB) : 
  data(0),
  minRawSpeed(0),
  maxRawSpeed(Constant::floatMax),
  mode(Constant::RISING_A)
{
  this->pinA = pinA;
  this->pinB = pinB;
  init();
}

Encoder::Encoder(byte pinA, byte pinB, Constant::EncoderMode mode, float minSpeed, float maxSpeed) : 
  data(0)
{
  this->pinA = pinA;
  this->pinB = pinB;
  this->mode = mode;
  this->minRawSpeed = minSpeed;
  this->maxRawSpeed = maxSpeed;
  init();
}

Encoder::Encoder(byte pinA, byte pinB, Constant::EncoderMode mode, float minSpeed, float maxSpeed, int startData) : 
  data(startData)
{
  this->pinA = pinA;
  this->pinB = pinB;
  this->mode = mode;
  this->minRawSpeed = minSpeed;
  this->maxRawSpeed = maxSpeed;
  init();
}

// Initialize the 2 pins which are reading the quadrature signals A & B.
// Initialize the timer
void Encoder::init() 
{
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
  previousTime = micros();
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

  if(speed >= maxRawSpeed || speed < minRawSpeed)
    speed = 0;
  
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
  if (data >= Constant::shortMax)
    data = Constant::shortMin;
  else
    data++;
  computeSpeed(true);
}

void Encoder::subData() 
{
  if (data <= Constant::shortMin)
    data = Constant::shortMax;
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
