/*
	Rtc.h - Library for a Realtime Clock.
	Created by Carven Martis, March, 8 ,2013.
*/
#ifndef Rtc_h
#define Rtc_h

#include "Arduino.h"
#include <Wire.h>

#define clockAddress 0x68

class Rtc
{
	
	public:
		Rtc(int pin);
		void init();
    void setTimeDay(int _second,int _minute, int _hour,
                    int _dayOfWeek, int _dayOfMonth, int _month, int _year);
		byte getSecond();
		byte getMinutes();
		byte getHour();
		byte getDayOfMonth();
		byte getMonth();
		byte getYear();
        int getPin();
        void getTimeDate();
        
        byte decToBcd(byte val);
        byte bcdToDec(byte val);
		
	private:
		int _pin;
		byte second,minute,hour,dayOfWeek,dayOfMonth,month,year;
	
};

#endif

