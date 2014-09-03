
#include "Speedo.h"
#include "Arduino.h"

// Arduino UNO support interrupts only on selected pins
// see: http://arduino.cc/en/Reference/attachInterrupt
//#define INT0 0
//#define INT1 1
//#define INT0_PIN 2
//#define INT1_PIN 3

void increaseRevsCount();

Speedo _sharedSpeedo = Speedo(Interrupt0);
int _speedoRevsCounter = 0;

Speedo Speedo::sharedSpeedo() {
  return _sharedSpeedo;
}

Speedo::Speedo(Interrupt interrupt) {
  
  interruptIdx = 0;
  interruptPin = 2;
  switch(interrupt) {
    case Interrupt1:
      interruptIdx = 1;
      interruptPin = 3;
      break;
  }

}

void Speedo::setup(void) {
  
  attachInterrupt(interruptIdx, increaseRevsCount, FALLING);
    
}

int Speedo::readRevsAndReset(void) {
  
  noInterrupts();
  int result = this->speedoRevsCounter;
  this->speedoRevsCounter = 0;
  interrupts();
  
  return result;
  
}

float Speedo::readMPHAndReset(float diameterInInches) {
  
  int revCount = this->readRevsAndReset();
  // Do the math...
  float rps = revCount / 1.0;
  float rpm = rps * 60;
  float rph = rpm * 60;
  
  float diameterMiles = diameterInInches * 0.00001578282;
  float c = 2 * PI * diameterMiles;
  float mph = rph * c;
}

void increaseRevsCount() {
    
    int sensorValue = analogRead(_sharedSpeedo.interruptPin);
    float voltage = sensorValue * (5.0 / 1023.0);
    
    /*
     Sensor keeps voltage on the edge between LOW and HIGH, this couses erratic readings.
     Folowing is used to reduce the problem:
     Count only if voltage drops below major threshold
     */
    if (voltage < 2.0) {
        _sharedSpeedo.speedoRevsCounter++;
    }
}

