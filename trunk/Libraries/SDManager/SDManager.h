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
    void writeToSD(struct xbee_data *xbee, bool writeOffline);
    void readFromSD(char *file);
    void removeFile(char *file);
    void writeToOffline(struct xbee_data *xbee);
    
    xbee_data data[100];
    xbee_data offlineData[100];
    xbee_data *getData();
    xbee_data *getOFflineData();
    
    int getDataSize();
    int count;

private:
    int daycount;
    int nodeCount;
    int nodeValue;
    int numberofData;
    File myFile,offlineFile;
    SdFile root;
    bool filePathCheck;
    bool offlinePath;
    DateTime t;
    
};


#endif
