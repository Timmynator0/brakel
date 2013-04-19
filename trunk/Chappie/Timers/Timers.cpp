#include "Timers.h"
Timers Timers1;
Timers Timers3;
Timers Timers4;
Timers Timers5; // preinstatiate

unsigned int Timers::pwmPeriod = 0;
unsigned char Timers::clockSelectBits = 0;

// interrupt service routine that wraps a user defined function supplied by attachInterrupt
ISR(TIMER1_OVF_vect)
{
  Timers1.isrCallback();
}

// interrupt service routine that wraps a user defined function supplied by attachInterrupt
ISR(TIMER3_OVF_vect)
{
  Timers3.isrCallback();
}

// interrupt service routine that wraps a user defined function supplied by attachInterrupt
ISR(TIMER4_OVF_vect)
{
  Timers4.isrCallback();
}

// interrupt service routine that wraps a user defined function supplied by attachInterrupt
ISR(TIMER5_OVF_vect)
{
  Timers5.isrCallback();
}