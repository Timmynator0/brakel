#include "Arduino.h"
#include "Rtc.h"
#include "Wire.h"

Rtc::Rtc(int pin){
	_pin = pin;
	Serial.begin(9600);
	
}
void Rtc::init(){
	Wire.begin();
	
}
void Rtc::setTimeDay(int _second,int _minute, int _hour
                     ,int _dayOfWeek, int _dayOfMonth, int _month, int _year){
    Wire.beginTransmission(clockAddress);
    Wire.write(byte(0x00));
    Wire.write(decToBcd(_second));
    Wire.write(decToBcd(_minute));
    Wire.write(decToBcd(_hour));
    
    Wire.write(decToBcd(_dayOfWeek));
    Wire.write(decToBcd(_dayOfMonth));
    Wire.write(decToBcd(_month));
    Wire.write(decToBcd(_year));
    
    
    Wire.endTransmission();
}

void Rtc::getTimeDate(){
    Wire.beginTransmission(clockAddress);
    Wire.write(byte(0x00));
    Wire.endTransmission();
    Wire.requestFrom(clockAddress,7);
    
    second = bcdToDec(Wire.read() & 0x7f);
    minute = bcdToDec(Wire.read());
    hour = bcdToDec(Wire.read() & 0x3f);
    
    dayOfWeek = bcdToDec(Wire.read());
    dayOfMonth = bcdToDec(Wire.read());
    month = bcdToDec(Wire.read());
    year = bcdToDec(Wire.read());
    
    
}

byte Rtc::decToBcd(byte val){
    return ((val/10*16) + (val%10));
}

byte Rtc::bcdToDec(byte val){
    return ((val/16*10) + (val%16));
    
}

byte Rtc::getSecond(){
	return second;
}

int Rtc::getPin(){
    return _pin;
    
}

byte Rtc::getMinutes(){
	return minute;
}
byte Rtc::getHour(){
	return hour;
}

byte Rtc::getDayOfMonth(){
	return dayOfMonth;
}

byte Rtc::getMonth(){
	return month;
}

byte Rtc::getYear(){
	return year;
}





