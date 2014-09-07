/*

  Hall-effect sensor based rev counter

  Goals: 
    - Use hall-effect sensor (UGN3503)
    - detect input changes using interrupts
    - count changes per second ( RPS - revolutions per second )
    - scale up RPS to RPM ( revolutions per minute ) or RPH ( revolutions per hour )
    - do math to derive MPH ( miles per hour ) based on wheel diameter and RPH
    
  Options:
    - use more than one magnet to provide more accurate readings. this imporves low RPM readings.
    
*/

#include "Speedo.h"
#include "Display.h"
#include <TM1638.h>

Speedo speedo = Speedo::sharedSpeedo();
TM1638 displayModule(8, 9, 10);

void setup() {
  
  Serial.begin(9600); // DEBUG

  speedo.setup();
}

void loop() {
  
  float mph = speedo.readMPHAndReset(17);
  Serial.println(mph);
  
  setSpeedAndOdo( 10, 11);
  
  delay(1000);
  
}

void setSpeedAndOdo(unsigned long speed, unsigned long odometer) {
  
    unsigned long value = odometer*1000+speed;

    byte separator = 0x08;
    displayModule.setDisplayToDecNumber(value,separator);
  
}



