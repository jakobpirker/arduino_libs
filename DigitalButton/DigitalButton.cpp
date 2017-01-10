#include "DigitalButton.h"

DigitalButton::DigitalButton(int pin, int stable_count)
{
  pinMode(pin, INPUT);
  this->last_stable_state_  = digitalRead(pin);
  this->pin_ = pin;
  this->stable_count_ = stable_count;
}

int DigitalButton::getStableState()
{
  int stable = 0;
  int last_state = this->last_stable_state_;
  int cur = digitalRead(this->pin_);
  unsigned long t_start = millis();

  while(!stable)
  { 
    if(cur != last_state)
    {
      t_start = millis();
    }
      
    if((millis() - t_start)  > this->stable_count_)
    {
      stable = 1;
    }
      
    last_state = cur;
    cur = digitalRead(this->pin_);
  }

  this->last_stable_state_ = cur;
  return cur;
}

unsigned long DigitalButton::waitForToggle(unsigned long max_wait)
{
  int stable_previous = this->getStableState();
  unsigned long t_start = millis();
  
  while( stable_previous == last_stable_state_ )
  {
    if(digitalRead(pin_) != stable_previous)
    {
      this->getStableState();
    }
    
    if(max_wait > 0 && (millis() - t_start) > max_wait)
      break;
  }
  
  return (millis() - t_start);
}

unsigned long DigitalButton::detectPulse(unsigned long max_wait, unsigned long max_pulse_length)
{  
  if(this->waitForToggle(max_wait) <= max_wait || max_wait == 0)
  {
    unsigned long t_start = millis();
    if(this->waitForToggle(max_pulse_length) <= max_pulse_length || max_pulse_length == 0 )
    {
      return (millis() - t_start);
    }
    else
    {
      return 0;
    }
  }
  else
  {
    return 0;
  }
}

unsigned long DigitalButton::waitForState(int state, unsigned long max_wait)
{
  if(this->getStableState() != state)
  {
    return this->waitForToggle(max_wait);
  }
  
  return 0;
}