#include "Arduino.h"
#include "SDManager.h"
#include <SD.h>
#include <String.h>

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
        
        myFile.print("NodeAddresLow   \t= ");
        myFile.println(xbee->nodeAddrLow);
        
        myFile.print("NodeAddresHigh  \t= ");
        myFile.println(xbee->nodeAddrHigh);
        myFile.println("");
        
        root.close();
        myFile.close();
        
    }else{
        Serial.println("Error opening SD");
    }
    
}

void SDManager::readFromSD(struct my_xbee *xbee){
    
    char character;
    char results[100];
    String description = "";
    String value = "";
    boolean valid = true;
    
    myFile = SD.open("14052013.txt");
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
        } else if(character =='='){
            do {
                character = myFile.read();
            } while(character == ' ');
               
        if (description == "Temperatuur") {
            value = "";
            while(character != '\n') {
                if(isdigit(character)) {
                    value.concat(character);
                } else if(character != '\n') {
                    // Use of invalid values
                    valid = false;
                    xbee->temperature = value.toInt();
                   
                }
                character = myFile.read();
            };
         
            
        }else if (description == "Licht") {
            value = "";
            while(character != '\n') {
                if(isdigit(character)) {
                    value.concat(character);
                } else if(character != '\n') {
                    // Use of invalid values
                    valid = false;
                    xbee->lightIntensity = value.toInt();
                   
                }
                character = myFile.read();
            };
        
            
        }else if (description == "Co2") {
            value = "";
            while(character != '\n') {
                if(isdigit(character)) {
                    value.concat(character);
                } else if(character != '\n') {
                    // Use of invalid values
                    valid = false;
                    xbee->CO2 = value.toInt();
                }
                character = myFile.read();
            };
            
            
        }else if (description == "Humidity") {
            value = "";
            while(character != '\n') {
                if(isdigit(character)) {
                    value.concat(character);
                } else if(character != '\n') {
                    // Use of invalid values
                    valid = false;
                    xbee->humidity = value.toInt();
                    
                }
                character = myFile.read();
            };
       
            
        }else if (description == "NodeAddresLow") {
            value = "";
            while(character != '\n') {
                if(isdigit(character)) {
                    value.concat(character);
                } else if(character != '\n') {
                    // Use of invalid values
                    valid = false;
                    xbee->nodeAddrLow = value.toInt();
                    
                }
                character = myFile.read();
            };
       
            
        }else if (description == "NodeAddresHigh") {
            value = "";
            while(character != '\n') {
                if(isdigit(character)) {
                    value.concat(character);
                } else if(character != '\n') {
                    // Use of invalid values
                    valid = false;
                    xbee->nodeAddrHigh = value.toInt();
               
                }
                character = myFile.read();
            };
            delay(2000);
            
        }
            description = "";
            
       }
        
    }

    Serial.write("DONE READING!");
    root.close();
    myFile.close();

}





//http://jurgen.gaeremyn.be/index.php/arduino/reading-configuration-file-from-an-sd-card.html