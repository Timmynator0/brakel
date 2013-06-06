#ifndef _UTILS_H_
#define _UTILS_H_
#include <avr/pgmspace.h>
#include <arduino.h>

#define MAX_STRING 70

extern char blaBuffer[MAX_STRING];

char* getString(const char* str);

#endif