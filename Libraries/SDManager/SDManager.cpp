#include "Arduino.h"
#include "SDManager.h"
#include <SD.h>
#include <String.h>

void SDManager::initSD(){
 
    
    Serial.println("Waiting 5 seconds for SD ");
    Serial.print("Initializing SD card...");
    
    pinMode(10, OUTPUT);
    nodeCount = 0;
    delay(5000);
    
    if(!SD.begin(4)){
        Serial.println("initialization failed!");
    }else{
         Serial.println("initialization done.");
    }

}

void SDManager::writeToSD(struct my_xbee *xbee ){
    
    char *result = "                              ";
    sprintf(result,"%02d%02d%02d.txt",xbee->timeStamp.day(),xbee->timeStamp.month(),xbee->timeStamp.year());
    Serial.println(result);
    
    myFile = SD.open(result, FILE_WRITE);
    delay(1000);
    if(myFile){
        Serial.println("Succes opening SD");
        myFile.print("Temperatuur   \t\t= ");
        myFile.println(xbee->temperature);

        myFile.print("Licht  \t\t\t= ");
        myFile.println(xbee->lightIntensity);
        
        myFile.print("Co2  \t\t\t= ");
        myFile.println(xbee->CO2);
        
        myFile.print("Humidity  \t\t= ");
        myFile.println(xbee->humidity);
        
        myFile.print("Node Addres Low  \t= ");
        myFile.println(xbee->nodeAddrLow);
        
        myFile.print("Node Addres High  \t= ");
        myFile.println(xbee->nodeAddrHigh);
        myFile.println("");
        
        myFile.close();
        
    }else{
        Serial.println("Error opening SD");
       
    }
    
}

void SDManager::readFromSD(){
    
    // re-open the file for reading:
    myFile = SD.open("14052013.txt");
    if (myFile) {
        Serial.println("14052013.txt");
        
        // read from the file until there's nothing else in it:
        while (myFile.available()) {
            Serial.write(myFile.read());
            
        }
        Serial.write("DONE READING!");
        // close the file:
        myFile.close();
    } else {
        // if the file didn't open, print an error:
        Serial.println("error opening 14052013.txt");
    }
}