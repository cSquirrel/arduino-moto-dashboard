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

Speedo speedo = Speedo::sharedSpeedo();

void setup() {
  
  Serial.begin(9600); // DEBUG

  speedo.setup();
  
}

void loop() {
  
  float mph = speedo.readMPHAndReset(17);
  Serial.println(mph);
  
  delay(1000);
  
}



