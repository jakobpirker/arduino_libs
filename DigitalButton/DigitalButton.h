/*
  Helps handling of digital button inputs (especially bouncing)
*/

#ifndef DigitalButton_h
#define DigitalButton_h

#include "Arduino.h"

class DigitalButton
{
  public:
    // @pin_      number of digital output-pin
    // @stable_count  milli-seconds to detect a stable state
    DigitalButton(int pin, int stable_count);
  
    // reads a stable state (input-state constant for STABLE_COUNT milli-seconds)
    int getStableState();
    
    // last verified stable state (from getStableState())
    int getLastStableState() { return last_stable_state_; }
    
    // waits till the input changes it state
    // @max_wait    max time [ms] that should be waited
    //              0 indicates to wait as long as necessary
    // @return      ms that have been waited
    unsigned long waitForToggle(unsigned long max_wait);
    
    // waits until a pulse appears
    // @max_wait          max time [ms] that should be waited for a pulse
    // @max_pulse_length  max pulse length [ms] to wait
    //              For both: 0 indicates to wait as long as necessary
    // @return      pulse length [ms], 0 if max_wait or max_pulse_length have
    //              been exceeded
    unsigned long detectPulse(unsigned long max_wait, unsigned long max_pulse_length);
    
    // waits for a certain state at the input
    // @state     desired input state (LOW or HIGH)
    // @max_wait  max time [ms] that should be waited for the state
    //            0 indicates to wait as long as necessary
    // @return    ms that have been waited
    unsigned long waitForState(int state, unsigned long max_wait);
    
    int getPin() { return pin_; }
    int getState() { return digitalRead(pin_); }

  private:
    int pin_;
    int last_stable_state_;
    int stable_count_;
};

#endif

