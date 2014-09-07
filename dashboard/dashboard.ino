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

#include <avr/interrupt.h>
#include <avr/eeprom.h>

#define display_dataPin     8
#define display_clockPin    9
#define display_strobePin    10

int odometerValueaAdr = 1;
int odometerValue = 0;

Speedo speedo = Speedo::sharedSpeedo();
TM1638 displayModule(display_dataPin, display_clockPin, display_strobePin);

void setup() {
  
  Serial.begin(9600); // DEBUG
  
  speedo.setup();
}

void loop() {
  
  float mph = speedo.readMPHAndReset(17);
  Serial.println(mph);
  
  byte keys = displayModule.getButtons();
  boolean resetOdo = (keys == 3); // S1 & S2 pressed
  
  while (!eeprom_is_ready()); // Wait for EEPROM to be ready
  cli();
  int odometerValue = eeprom_read_word((uint16_t*)odometerValueaAdr);
  if(resetOdo) {
    odometerValue = 0;
  } else { 
    odometerValue++;
  }
  eeprom_write_word((uint16_t*)odometerValueaAdr, odometerValue);
  sei();

  setSpeedAndOdo( 10, odometerValue);
  
  delay(1000);
  
}

void setSpeedAndOdo(unsigned long speed, unsigned long odometer) {
  
    unsigned long value = odometer*1000+speed;

    byte separator = 0x08;
    displayModule.setDisplayToDecNumber(value,separator);
  
}



