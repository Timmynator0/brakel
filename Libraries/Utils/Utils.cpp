#ifndef _UTILS_CPP_
#define _UTILS_CPP_
#include <Utils.h>
char blaBuffer[MAX_STRING];
char* getString(const char* str) {
	strcpy_P(blaBuffer, (char*)str);
	return blaBuffer;
}
#endif