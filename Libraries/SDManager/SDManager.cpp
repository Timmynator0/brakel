#include "Arduino.h"
#include "SDManager.h"
#include <SD.h>



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

    Serial.println(xbee->day);
    
    myFile = SD.open(xbee->day, FILE_WRITE);
    delay(1000);
    if(myFile){
        Serial.println("Succes opening SD");
        myFile.print("Temperatuur  = \t");
        myFile.println(xbee->temperatuur);
        
        myFile.print("Licht = \t");
        myFile.println(0);
        
        myFile.print("Co2 =\t");
        myFile.println(0);
        myFile.close();
//        myFile2 = SD.open(xbee->day, FILE_WRITE);
//        if(myFile2){
//            myFile2.print("Luchtvochtigheid =\t");
//            myFile2.println(0);
//            myFile2.print("Node Nummer = ");
//            myFile2.println(1);
//            myFile2.close();
//        }else{
//            Serial.println("Error opening SD Second!!");
//            myFile2.close();
//        }
        
    }else{
        Serial.println("Error opening SD");
        myFile.close();
    }
    
   
}

void SDManager::readFromSD(){
    
    // re-open the file for reading:
    myFile = SD.open("test.txt");
    if (myFile) {
        Serial.println("test.txt:");
        
        // read from the file until there's nothing else in it:
        while (myFile.available()) {
            //
            
        }
        Serial.write("DONE READING!");
        // close the file:
        myFile.close();
    } else {
        // if the file didn't open, print an error:
        Serial.println("error opening test.txt");
    }
}