/*
  CyclicBlinkPrint
  Shows multiple 'tasks' running with CyclicTimer

  Two timers implemented with CyclicTimer, one running at 10 Hz incrementing
  a counter, the 2nd one running at 1 Hz printing the counter value.
  
  Also, in the main program, a variable delay represeting some random
  main task neeing a random amount of time (0..500 ms), after which it 
  will return to the main loop, giving time to the timer tasks.
    
  As you can see, the 10 Hz task is still executed 10 times a second on
  average, although of course with *significant* jitter in the timing,
  as the main task only returneds and gives time for other tasks like
  tenthSecondTimer after up to 500 ms. However, no missed executions!

  Normally, you would make sure to break up your main task such that it
  will not take that long before returning to loop() ...

  Created 16 Feb 2020 by Kees Moerman as example for CyclicTimer

 */
 
#include <CyclicTimer.h>
cyclicTimer oneSecondTimer;         // Instantiate new timer 1
cyclicTimer tenthSecondTimer;       // Instantiate new timer 2


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize digital pin 13 as an output
  randomSeed(analogRead(0));        // Initialise random number generator
  
  Serial.begin(115200);             // Initialize serial port at 15200 Baud
  delay(1000);                      // Give user time to switch on serial monitor
  Serial.println("CyclicBlinkPrint Setting up...");
  
  oneSecondTimer.setPeriod(1000);   // Tick for one second period
  tenthSecondTimer.setPeriod(100);  // Tick for 1/10th second period
}

void loop() {                       // 'main()', runs over and over again forever
  static int myCounter = 0;
  
  while(tenthSecondTimer.tickAndTest())
  {                                 // while(): to catch up with missed ticks
    myCounter++;                    // Just increment, 10 times a second
  }
  
  while(oneSecondTimer.tickAndTest())
  { 
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // Blink
    Serial.println(myCounter);      // Print current counter value
  }
  
  // Do other things here, if needed: wait random time to emulate other tasks
  // Note: this can be up to 5 times the period of tenthSecondTimer
  delay(random(500));               // Emulated 'main task'
}
