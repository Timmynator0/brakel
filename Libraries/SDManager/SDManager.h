#include "Arduino.h"

#ifndef __SDManager_H__
#define __SDManager_H__

#include <SD.h>
#include <string.h>
#include <Types.h>
#include <SdFat.h>

class SDManager{
    
public:
    void initSD(void);
    void writeToSD(struct my_xbee *xbee);
    void readFromSD(struct my_xbee *xbee);
    

private:
    int daycount;
    int nodeCount;
    int nodeValue;
    File myFile;
    SdFile root;
    
};


#endif
