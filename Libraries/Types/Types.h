#ifndef __TYPES_H__
#define __TYPES_H__


typedef struct{
    DateTime  timeStamp;
    int temperature;
    int lightIntensity;
    int humidity;
    int CO2;
    uint_8 nodeAddrLow;
	uint_8 nodeAddrHigh;
}xbee_data;
