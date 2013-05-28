#include "Arduino.h"

#ifndef __SDManager_H__
#define __SDManager_H__

#include <SD.h>
#include <string.h>
#include <Types.h>
#include <SdFat.h>
#include <Buffer.h>
#include <BufferManager.h>

class SDManager{
    
public:
    bool initSD();

    void readFromSD(char *file);
    bool readFromBuffer();
    
    void removeFile(char *file);
    void writeToSD(xbee_data *xbee, bool writeOffline);
    void writeToOffline(xbee_data *xbee);
    
    void setBufferManager(BufferManager *b);
    void storeToBuffer(xbee_data data);
    
    void dataToFile(File file, xbee_data *xbee,bool filePath);
    
    xbee_data data[100];
    xbee_data offlineData[100];
    xbee_data *getData();
    xbee_data *getOFflineData();
    
    xbee_data buffData;
    BufferManager *buff;
    
    int getDataSize();
    int count;

private:
    int daycount;
    int nodeCount;
    int nodeValue;
    int numberofData;
    File myFile,offlineFile;
    
    bool filePathCheck;
    bool offlinePath;
    DateTime t;
};


#endif
