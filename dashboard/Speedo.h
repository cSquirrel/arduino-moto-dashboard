#ifndef Speedo_h
#define Speedo_h

#include "Arduino.h"

enum {
  Interrupt0,
  Interrupt1
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
