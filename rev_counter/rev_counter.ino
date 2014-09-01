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

int revsCounter = 0;

// Arduino UNO support interrupts only on selected pins
// see: http://arduino.cc/en/Reference/attachInterrupt
#define INT0 0
#define INT1 1
#define INT0_PIN 2
#define INT1_PIN 3

void setup() {
  
  Serial.begin(9600); // DEBUG
  attachInterrupt(INT0, incRevs, FALLING);
  
}

void incRevs() {
  
  int sensorValue = analogRead(INT0_PIN);
  float voltage = sensorValue * (5.0 / 1023.0);
  
  /*
    Sensor keeps voltage on the edge between LOW and HIGH, this couses erratic readings.
    Folowing is used to reduce the problem:
    Count only if voltage drops below major threshold
  */
  if (voltage < 2.0) {
    revsCounter++;
  }
}

void loop() {
  
  // disable interrupts and
  // save the revs value. 
  // Then reset the counter
  noInterrupts();
  float r = revsCounter;
  revsCounter = 0;
  interrupts();
  
  // Do the math...
  float rps = r / 1.0;
  float rpm = rps * 60;
  float rph = rpm * 60;
 
  
  float diameter = 0.000268308; // 17 inches in miles
  float c = 2 * PI * diameter;
  float mph = rph * c;
  Serial.println(mph);
  
  delay(1000);
  
}



