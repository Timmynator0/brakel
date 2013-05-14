#include "Arduino.h"

#ifndef __SDManager_H__
#define __SDManager_H__

#include <SD.h>
#include <string.h>

typedef struct my_xbee {
    char *day;
    int temperatuur;
    int licht;
    int luchtvochtigheid;
    int co2;
    int nodeNr;
}xbee_data;

class SDManager{
    
public:
    
    void initSD(void);
    void writeToSD(struct my_xbee *xbee);
    void readFromSD(void);
    

private:
    
    int daycount;
    int nodeCount;
    int nodeValue;
    File myFile;
};


#endif
