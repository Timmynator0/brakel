#include "Arduino.h"
#include "SDManager.h"
#include <SD.h>
#include <String.h>

#define SDCARD  0

void SDManager::initSD(){
 
    
    Serial.println("Waiting 5 seconds for SD ");
    Serial.print("Initializing SD card...");
    
    pinMode(53, OUTPUT);
    nodeCount = 0;
    delay(5000);
    
    if(!SD.begin(4)){
        Serial.println("initialization failed!");
    }else{
         Serial.println("initialization done.");
    }

}


void SDManager::readFromBuffer(){
    while(!buff.isEmpty(0)){
        bool result = buff.read(&buffData, 0);
        if(result)
            writeToSD(&buffData ,false);
        else
            Serial.println("Failed to read from buffer");
    }

}

void SDManager::writeToSD(xbee_data *xbee, bool writeOffline ){
    
    char *result = "                              ";
    sprintf(result,"%02d%02d%02d.txt",xbee->timeStamp.day(),xbee->timeStamp.month(),xbee->timeStamp.year());
    Serial.println(result);
    
    if(SD.exists(result))
        filePathCheck = true;
    else
        filePathCheck = false;
    
    
    myFile = SD.open(result, FILE_WRITE);
    delay(1000);

    if(myFile){
        Serial.println("Succes opening SD");
        if(!filePathCheck){
            myFile.print("UnixTime;");
            myFile.print("Temperatuur;");
            myFile.print("Licht;");
            myFile.print("Co2;");
            myFile.print("Humidity;");
            myFile.print("NodeAddresLow;");
            myFile.println("NodeAddresHigh;");
        }
 
        myFile.print(xbee->timeStamp.unixtime());
        
        myFile.print(";");
        myFile.print(xbee->temperature);

        myFile.print(";");
        myFile.print(xbee->lightIntensity);
        
        myFile.print(";");
        myFile.print(xbee->CO2);
        
        myFile.print(";");
        myFile.print(xbee->humidity);
        
        myFile.print(";");
        myFile.print(xbee->nodeAddrLow);
        
        myFile.print(";");
        myFile.print(xbee->nodeAddrHigh);
        myFile.println(";");
        root.close();
        myFile.close();
        
    }else{
        Serial.println("Error opening SD");
    }
    delay(1000);
    if (writeOffline) {
        Serial.println("yes make offline file");
        writeToOffline(xbee);
    }else{
        Serial.println("no dont make offline file");
    }
    
}

void SDManager::readFromSD(char *file){
    
    char character;
    char results[100];
    String description = "";
    String value = "";
    numberofData = 0;
    boolean valid = true;
    
    myFile = SD.open(file);
    delay(1000);
    if(myFile){
        Serial.println("Reading from file succes");
    }else{
        Serial.println("Failed to read from file");
    }
    while (myFile.available()) {
        character = myFile.read();
        if(character == '/'){
            while(character != '\n'){
                character = myFile.read();
            };
        } else if(isalnum(character)){
               description.concat(character);
        } else if(character ==';'){
            
        if (description == "UnixTime") {
            value = "";
            while(character != '\n') {
                if(isdigit(character)) {
                    value.concat(character);
                } 
                character = myFile.read();
            };
          
        }
            // check for array
            if (numberofData < 100) {
                
            
                switch (count) {
                    case 1:
                        Serial.println(description);
                        t =DateTime(description.toInt());
                  
                        data[numberofData].timeStamp =t;
                        break;
                    case 2:
                        Serial.println(description);
                        data[numberofData].temperature =description.toInt();
                        break;
                    case 3:
                        Serial.println(description);
                        data[numberofData].lightIntensity =description.toInt();
                        break;
                    case 4:
                        Serial.println(description);
                        data[numberofData].CO2 =description.toInt();
                        break;
                    case 5:
                        Serial.println(description);
                        data[numberofData].humidity =description.toInt();
                        break;
                    case 6:
                        Serial.println(description);
                        data[numberofData].nodeAddrLow =description.toInt();
                        break;
                    case 7:
                        Serial.println(description);
                        data[numberofData].nodeAddrHigh =description.toInt();
                        numberofData++;
                    
                        count= 0;
                        break;
                    
                    default:
                        break;
                }
            }
            
            count++;
            description = "";
       }
        
    }
    Serial.write("DONE READING!");
    root.close();
    myFile.close();
    
    if(file[0] == 'o')
        removeFile(file);
    else
        Serial.println("File Can not be deleted");

}

void SDManager::writeToOffline(xbee_data *xbee){
    if(SD.exists("offline.txt"))
        offlinePath = true;
    else
        offlinePath = false;
    
    offlineFile = SD.open("offline.txt", FILE_WRITE);
    delay(1000);

    if(offlineFile){
        Serial.println("Succes opening offline SD");
        if(!offlinePath){
            offlineFile.print("UnixTime;");
            offlineFile.print("Temperatuur;");
            offlineFile.print("Licht;");
            offlineFile.print("Co2;");
            offlineFile.print("Humidity;");
            offlineFile.print("NodeAddresLow;");
            offlineFile.println("NodeAddresHigh;");
        }

        offlineFile.print(xbee->timeStamp.unixtime());
        
        offlineFile.print(";");
        offlineFile.print(xbee->temperature);
        
        offlineFile.print(";");
        offlineFile.print(xbee->lightIntensity);
        
        offlineFile.print(";");
        offlineFile.print(xbee->CO2);
        
        offlineFile.print(";");
        offlineFile.print(xbee->humidity);
        
        offlineFile.print(";");
        offlineFile.print(xbee->nodeAddrLow);
        
        offlineFile.print(";");
        offlineFile.print(xbee->nodeAddrHigh);
        offlineFile.println(";");

        
    }else
        Serial.println("Error opening offline SD");
    
    root.close();
    offlineFile.close();
}


void SDManager::removeFile(char *file){
    
    if(SD.exists(file)){
        SD.remove(file);
    }
    
}

int SDManager::getDataSize(){
    return numberofData;
}




xbee_data *SDManager::getData(){
    return data;
}


xbee_data *SDManager::getOFflineData(){
    return offlineData;
}



//http://jurgen.gaeremyn.be/index.php/arduino/reading-configuration-file-from-an-sd-card.html