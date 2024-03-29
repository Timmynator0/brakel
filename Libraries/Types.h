#ifndef __TYPES_H__
#define __TYPES_H__

#include "Arduino.h"
#include <RTClib.h>

typedef struct xbee_data{
    DateTime timeStamp;
    int temperature;
    int lightIntensity;
    int humidity;
    int CO2;
    int nodeAddrLow;
	int nodeAddrHigh;
};



#endif