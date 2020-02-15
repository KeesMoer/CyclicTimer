/*
  CyclicBlink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014 by Scott Fitzgerald
  modified 15 Feb 2020 by Kees Moerman (rewrite with cyclicTimer) 
 */
 
#include <CyclicTimer.h>
cyclicTimer oneSecondTimer;         // Instantiate new timer

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);     // initialize digital pin 13 as an output.
  oneSecondTimer.setPeriod(1000);   // tick for one second period
}

// the loop function runs over and over again forever
void loop() {
  if(oneSecondTimer.tickAndTest())  // check (decrement with auto-reload)
  { digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); }
  
  // Do other things here, if needed
  delay(10);                        // wait for 10 ms to emulate other tasks

}
