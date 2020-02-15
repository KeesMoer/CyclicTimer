# CyclicTimer

A minimalistic cyclic timer class for Arduino, to run repeating tasks from `loop()`

## Introduction

Sometimes you need a simple way to time multiple tasks, without
wanting to have a complete scheduler (or not having the space for it, as on
an Arduino Nano). This could be for example a measuring task plus a user
interface task, as I had in my [CO2 sensor](https://www.keesmoerman.nl/airsense.html).

Based on the Arduino main program `loop()` concept, CyclicTimer is a simple
helper to create milli-second resolution timers, which you can decrement
and check for zero, in which case they will auto-reload for the next interval.
Kind of cooperative multi-tasking.

Don't expect millisecond accuracy, as we have no control over how long other
tasks run (it is all 'scheduled' in the main loop, not in an interrupt routine).
However, when reloading it takes into account any time already
lapsed due to possible other tasks, so will catch up to run on average
on the specified interval.

Note: maximum time is 65K miliseconds, so let's say one minute. Useful for
sub-second or few-second intervals.

## Methods

```c++
// cyclicTimer initialiser: creates new timer, but does not yet start it.
cyclicTimer::cyclicTimer()

// Set the period in milliseconds, and (re)start the timer.
void cyclicTimer::setPeriod(uint16_t newPeriodMilliseconds) 

// Restart timer with earlier specified period.
void cyclicTimer::reset(void)

// Decrement and test, and reload timer with compensation for elapsed time.
// Might be true for multiple times sequentially, if much time has elapsed.
bool cyclicTimer::tickAndTest(void) 
```

## Example

Within the main program loop, flash a LED every second (half second on,
half second off):

```
#include <CyclicTimer.h>
cyclicTimer halfSecondTicker;  // Instantiate a new timer

// In init(): tick for half second period
    halfSecondTicker.setPeriod(500);

// In loop(): check (decrement with auto-reload)
    while(halfSecondTicker.tickAndTest()) { toggle_led(); }
    do_other_tasks();
```

You might expect an `if` before the test, but a while is useful if in the mean
time already multiple periods have passed, so the timer can 'catch up'.
I will do a second example with this (see the `examples` directory).


## Authors

* **Kees Moerman** - *Initial work* - [My pages](https://www.keesmoerman.nl)


## License

Still to select, but permissive: feel free to use, no strings attached.
Would be nice to acknowledge me.
