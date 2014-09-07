#ifndef Speedo_h
#define Speedo_h

#include "Arduino.h"

enum {
  Interrupt0, // Pin 2
  Interrupt1  // Pin 3
} typedef Interrupt;

class Speedo {
  
  public:
    static Speedo sharedSpeedo();
  
    Speedo(Interrupt interrupt);
    void setup(void);
    int readRevsAndReset(void);
    float readMPHAndReset(float diameterInInches);
    
    int speedoRevsCounter;
    int interruptIdx;
    int interruptPin;
};

#endif
