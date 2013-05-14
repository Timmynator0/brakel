#ifndef Timers_h_
#define Timers_h_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "config/known_16bit_timers.h"

#define TIMER_RESOLUTION 65536UL  // Timers are 16 bit

// Placing nearly all the code in this .h file allows the functions to be
// inlined by the compiler.  In the very common case with constant values
// the compiler will perform all calculations and simply write constants
// to the hardware registers (for example, setPeriod).

class Timers
{
	public:
	void initialize(int milliseconden, int timer) __attribute__((always_inline))
	{
	  //initialize the timers
	  noInterrupts(); // first disable all interupts
	  if(timer == 1)
	  {
		  TCCR1A = 0;
		  TCCR1B = 0;
		  TCNT1 = 0;
	  }
	  else if(timer ==3)
	  {
		  TCCR3A = 0;
		  TCCR3B = 0;
		  TCNT3 = 0;	
	  }
	  else if(timer == 4)
      {
		  TCCR4A = 0;
		  TCCR4B = 0;
		  TCNT4 = 0;
	  }
	  else if (timer == 5)
	  {
		  TCCR5A = 0;
		  TCCR5B = 0;
		  TCNT5 = 0;
	  }
	  interrupts();
	  setInterval(milliseconden,timer);
	}


	void setInterval(int milliseconde , int timer) __attribute__((always_inline))
	{
	  const unsigned long cycles = (F_CPU / 2000000) * milliseconde*1000;
	  clockSelectBits = _BV(CS12);
	  	if (cycles < TIMER_RESOLUTION) {
		clockSelectBits = _BV(CS30);
		pwmPeriod = cycles;
	} else
	if (cycles < TIMER_RESOLUTION * 8) {
		clockSelectBits = _BV(CS31);
		pwmPeriod = cycles / 8;
	} else
	if (cycles < TIMER_RESOLUTION * 64) {
		clockSelectBits = _BV(CS31) | _BV(CS30);
		pwmPeriod = cycles / 64;
	} else
	if (cycles < TIMER_RESOLUTION * 256) {
		clockSelectBits = _BV(CS32);
		pwmPeriod = cycles / 256;
	} else
	if (cycles < TIMER_RESOLUTION * 1024) {
		clockSelectBits = _BV(CS32) | _BV(CS30);
		pwmPeriod = cycles / 1024;
	} else {
		clockSelectBits = _BV(CS32) | _BV(CS30);
		pwmPeriod = TIMER_RESOLUTION - 1;
	}
	  if(timer == 1)
	  {
		ICR1 = pwmPeriod;
		TCCR1B = _BV(WGM13) | clockSelectBits;
	  }
	  else if( timer == 3)
	  {
		ICR3 = pwmPeriod;
		TCCR3B = _BV(WGM13) | clockSelectBits;
	  }
	  else if (timer == 4)
	  {
		ICR4 = pwmPeriod;
		TCCR4B = _BV(WGM13) | clockSelectBits;
	  }
	  else if (timer == 5)
	  {
		ICR5 = pwmPeriod;
		TCCR5B = _BV(WGM13) | clockSelectBits;
	  }
	}

	//****************************
	//  Interrupt Functions
	//****************************

	void attachInterruptTimer1(void (*isr)()) __attribute__((always_inline))
	{
	  isrCallback = isr;
	  TIMSK1 = _BV(TOIE1);
	}

	void attachInterruptTimer3(void (*isr)()) __attribute__((always_inline))
	{
	  isrCallback = isr;
	  TIMSK3 = _BV(TOIE3);
	}
	void attachInterruptTimer4(void (*isr)()) __attribute__((always_inline))
	{
	  isrCallback = isr;
	  TIMSK4 = _BV(TOIE4);
	}
	void attachInterruptTimer5(void (*isr)()) __attribute__((always_inline))
	{
	  isrCallback = isr;
	  TIMSK5 = _BV(TOIE5);
	}
	void(*isrCallback)();

	protected:
	//properties
	static unsigned int pwmPeriod;
	static unsigned char clockSelectBits;
};

extern Timers Timers1;
extern Timers Timers3;
extern Timers Timers4;
extern Timers Timers5;

#endif

