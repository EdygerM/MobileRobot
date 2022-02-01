// Include the necessary libraries for this file to work
#include "Encoder.h"
#include "Timer.h"

// Define the pins where the signal A and B are connected on the Arduino
// Note that the pinA must be on a pin supporting interrupt. 
// The official page lists which pins are compatible depending on the board used: https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
const byte pinA = 2;
const byte pinB = 3; 

// Create an object encoder
Encoder myEncoder(pinA, pinB);

// Define a timer with an interval of 100 ms
Timer timer(100);

void setup() 
{ 
  // Enable an interrupt on pinA which will call the function InterruptA each time the signal A is rising from LOW to HIGH
  attachInterrupt(digitalPinToInterrupt(pinA), InterruptA, RISING);

  // Intilialize the Serial Port at 57600 baud rate
  Serial.begin(57600);
}

void loop() 
{
  // Print the encoder datas on the Serial Monitor every 100 ms
  if(timer.isTime())
    Serial.println(myEncoder.getData());
}

// Function called everytime the signal A is rising from LOW to HIGH
void InterruptA() 
{
  // Increment or decrement the position by one tick depending on the turning direction
  myEncoder.incrementA();
}

