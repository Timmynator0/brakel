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
    void writeToSD(struct xbee_data *xbee);
    void readFromSD(struct xbee_data *xbee, char *file);
    void removeFile(char *file);
    xbee_data data[100];
    xbee_data *getData();
    int getDataSize();
    int count;

private:
    int daycount;
    int nodeCount;
    int nodeValue;
    int numberofData;
    File myFile;
    SdFile root;
    bool filePathCheck;
    DateTime t;
    
};


#endif
