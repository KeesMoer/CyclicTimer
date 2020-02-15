/*
 *    CyclicTimer.cpp - A simple class for periodic events from loop()
 *    Copyright (c) 2019 Kees Moerman
 * 
 *    Permission is hereby granted, free of charge, to any person
 *    obtaining a copy of this software and associated documentation
 *    files (the "Software"), to deal in the Software without
 *    restriction, including without limitation the rights to use,
 *    copy, modify, merge, publish, distribute, sublicense, and/or sell
 *    copies of the Software, and to permit persons to whom the
 *    Software is furnished to do so, subject to the following
 *    conditions:
 * 
 *    This permission notice shall be included in all copies or 
 *    substantial portions of the Software.
 * 
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *    OTHER DEALINGS IN THE SOFTWARE.
 */


#include <Arduino.h>
#include "CyclicTimer.h"

cyclicTimer::cyclicTimer() {            // Constructor: initialise at zero
    period = lastTick = 0;
}

void cyclicTimer::setPeriod(uint16_t newPeriod) {
    period = newPeriod;                 // or this->period ?? Mainly style
    lastTick = millis();
}

void cyclicTimer::reset(void) {
    lastTick = millis();                // start from scratch
}

bool cyclicTimer::tickAndTest(void) {   // is next period passed?
    unsigned long now = millis();
    if(lastTick+period < lastTick) {    // we have a wrap-around...
      if(now >= lastTick) return false; // wait till millis() also wraps  
    }
    if(period && (now > lastTick+period)) {
      lastTick += period;               // set value for next period
      return true;
    }
    return false;
}

// End of Class

