#include "Arduino.h"
#include "SDManager.h"

#define SDCARD  0
#define semicolon   ";"
#define megaPin 53
#define sdPin   4


bool SDManager::initSD(){
    
    pinMode(megaPin, OUTPUT);
    delay(100);
    return SD.begin(sdPin);
}
bool SDManager::readFromBuffer()
{
	//if(initSD())
	//{
        bool result = buff->read(&buffData, SDCARD);
        if(result){
            writeToSD(&buffData ,false);
        }else
            return false;
		return true;
	//}
	//else return false;
}

void SDManager::writeToSD(xbee_data *xbee, bool writeOffline ){
    
    
    char fileName[20];
    if(xbee->timeStamp.year() != 2165){
       
        sprintf(fileName,"%02d%02d%02d.txt",xbee->timeStamp.day(),xbee->timeStamp.month(),xbee->timeStamp.year());
    }else{
        sprintf(fileName,"nontp.txt");
    }
    if(SD.exists(fileName))
        filePathCheck = true;
    else
        filePathCheck = false;
    myFile = SD.open(fileName, FILE_WRITE);

    Serial.println(fileName);
    if(myFile){
        Serial.println("Succes opening SD");
        dataToFile(myFile, xbee, filePathCheck);
        
    }else{
        if(initSD()){
            myFile = SD.open(fileName, FILE_WRITE);
            if(myFile){
                dataToFile(myFile, xbee, filePathCheck);
				myFile.flush();
                myFile.close();
            }
        }
    }
    if (writeOffline)
        writeToOffline(xbee);
}

void SDManager::dataToFile(File file, xbee_data *xbee, bool filePath){
   Serial.println("koekjes1"); 
   if(!filePath){
	Serial.println("koekjes2");
        file.print("UnixTime;");
        file.print("Temperatuur;");
        file.print("Licht;");
        file.print("Co2;");
        file.print("Humidity;");
        file.print("NodeAddresLow;");
        file.println("NodeAddresHigh;");
    }
    
    file.print(xbee->timeStamp.unixtime());
    
    file.print(semicolon);
    file.print(xbee->temperature);
    
    file.print(semicolon);
    file.print(xbee->lightIntensity);
    
    file.print(semicolon);
    file.print(xbee->CO2);
    
    file.print(semicolon);
    file.print(xbee->humidity);
    
    file.print(semicolon);
    file.print(xbee->nodeAddrLow);
    
    file.print(semicolon);
    file.print(xbee->nodeAddrHigh);
    file.println(semicolon);
	file.flush();
    file.close();
}

/*
void SDManager::storeToBuffer(xbee_data data){
    buff->store(data);
    
}

/*void SDManager::setNTP(NTP *ntp_){
    ntp = ntp_;
	DateTime t = ntp->GetDateTime();
    char result[10];
    sprintf(result,"%02d-%02d-%04d", t.day(), t.month(), t.year());
    Serial.println(result);
}*/

/*
void SDManager::readFromSD(char *file){
    
    char character;
    char results[100];
    String description = "";
    String value = "";
    numberofData = 0;
    boolean valid = true;
    
    myFile = SD.open(file);
    if(myFile){
       // Serial.println("Reading from file succes");
    }else{
       // Serial.println("Failed to read from file");
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
    myFile.close();
    
    if(file[0] == 'o')
        removeFile(file);
    else
        Serial.println("File Can not be deleted");

}*/

void SDManager::writeToOffline(xbee_data *xbee){
    if(SD.exists("offline.txt"))
        offlinePath = true;
    else
        offlinePath = false;
    
    offlineFile = SD.open("offline.txt", FILE_WRITE);
    if(offlineFile){
        Serial.println("Succes opening offline SD");
        dataToFile(offlineFile,xbee,offlinePath);
    }else
        Serial.println("Error opening offline SD");
    
    offlineFile.close();
}


void SDManager::removeFile(char *file){
    
    if(SD.exists(file)){
        SD.remove(file);
    }
    
}


/*
int SDManager::getDataSize(){
    return numberofData;
}

xbee_data *SDManager::getData(){
    return data;
}


xbee_data *SDManager::getOFflineData(){
    return offlineData;
}
*/
void SDManager::setBufferManager(BufferManager *b)
{
    buff = b;
}


//http://jurgen.gaeremyn.be/index.php/arduino/reading-configuration-file-from-an-sd-card.htmlon-file-from-an-sd-card.html