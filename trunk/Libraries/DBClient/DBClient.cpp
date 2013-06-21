#include "Arduino.h"
#include "DBclient.h"
#include "SPI.h"
#include "Ethernet.h"
#include "BufferManager.h"
#include "String.h"
#define MAXBUFFERSIZE 2500

const char datapointStart[] PROGMEM= "<XbeeData>";
const char timeStart[] PROGMEM = "<Time>";
const char timeEnd[] PROGMEM = "</Time>";
const char temperatureStart[] PROGMEM ="<Temperature>";
const char temperatureEnd[] PROGMEM = "</Temperature>";
const char CO2Start[] PROGMEM ="<CO2>";
const char CO2End[] PROGMEM = "</CO2>";
const char humidityStart[] PROGMEM ="<Humidity>";
const char humidityEnd[] PROGMEM ="</Humidity>";
const char lightStart[] PROGMEM ="<Light>";
const char lightEnd[] PROGMEM = "</Light>";
const char NodeAdressLowStart[] PROGMEM ="<NodeAdressLow>";
const char NodeAdressLowEnd[] PROGMEM = "</NodeAdressLow>";
const char NodeAdressHighStart[] PROGMEM ="<NodeAdressHigh>";
const char NodeAdressHighEnd[] PROGMEM = "</NodeAdressHigh>";
const char datapointEnd[] PROGMEM ="</XbeeData>";
const char xmlStart[] PROGMEM = "<soap:Envelope xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\"> <soap:Body>    <storedata xmlns=\"localhost/Receive/\">      <XbeeDataPoints>";
const char xmlEnd[] PROGMEM = " </XbeeDataPoints> </storedata> </soap:Body></soap:Envelope>";
char txbuf[MAXBUFFERSIZE] = {'\0'};
int index = 0;
IPAddress server(145,48,6,30); // the IP adress of the ASP Server


void DBClient::setBufferManager(BufferManager *b)
{
    buffermanagerInstance = b;
}

void DBClient::setEthernetClient(EthernetClient *client_)
{
   client = client_; 
}

void DBClient::xmlBuildInit()
{
  index = 0;
  for( int idx = 0; idx < MAXBUFFERSIZE; idx++ )
  {
     
    txbuf[idx] = 0;
  }
}

int DBClient::xmlBuildSize()
{
  int idx = 0;
  while( txbuf[idx] != 0 )
  {
    idx++;
	}
  return idx;
}

int DBClient::xmlBuildTransmitBuffer()
{
  for( int idx = 0; idx < xmlBuildSize(); idx++ )
  {
    client->print(txbuf[idx]);
  }
}

void DBClient::xmlBuildStringItem( const char *str )
{
  for( uint8_t ch; ch = pgm_read_byte(str); str++)
  {
    if( index < MAXBUFFERSIZE )
    {
      txbuf[index++] = ch;
    }
    else
    {
      Serial.print("xmlBuildStringItem err: buffer to small");
    }
  }
}

void DBClient::xmlBuildDataItem(int data)
{  
  // convert data to char[]
  char tmp[8] = {'\0'};
  itoa(data,tmp,10);
    
  // print in buffer
  int idx = 0;
  while(char c = tmp[idx++])
  {
    if( index < MAXBUFFERSIZE )
      txbuf[index++] = c;
    else
      Serial.print("xmlBuildDataItem err: buffer to small");
  }
}

void DBClient::xmlBuildMessage()
{
    int count = 0;
    xbee_data readpoint;
    
    xmlBuildInit();
    
    xmlBuildStringItem( xmlStart );    
    while(!buffermanagerInstance->isEmpty(DATABASE)&& count < 10)
    {
      buffermanagerInstance->read(&readpoint, DATABASE);
      xmlBuildStringItem(datapointStart);
      xmlBuildStringItem(timeStart); xmlBuildDataItem(readpoint.timeStamp.unixtime()); xmlBuildStringItem(timeEnd);      
      xmlBuildStringItem(temperatureStart); xmlBuildDataItem(readpoint.temperature); xmlBuildStringItem(temperatureEnd);
      xmlBuildStringItem(CO2Start); xmlBuildDataItem(readpoint.CO2); xmlBuildStringItem(CO2End);
      xmlBuildStringItem(humidityStart); xmlBuildDataItem(readpoint.humidity); xmlBuildStringItem(humidityEnd);
      xmlBuildStringItem(lightStart); xmlBuildDataItem(readpoint.lightIntensity); xmlBuildStringItem(lightEnd);
      xmlBuildStringItem(NodeAdressLowStart); xmlBuildDataItem(readpoint.nodeAddrLow); xmlBuildStringItem(NodeAdressLowEnd);
      xmlBuildStringItem(NodeAdressHighStart); xmlBuildDataItem(readpoint.nodeAddrHigh); xmlBuildStringItem(NodeAdressHighEnd); 
      xmlBuildStringItem(datapointEnd);
      count++;    
    }
    xmlBuildStringItem( xmlEnd ); 
}

void DBClient::dbClientSend()
{
	if(!buffermanagerInstance->isEmpty(DATABASE))
	{
		if(!client->connected())
		{
			if(!client->connect(server, 80))
			{
				// couldn't make a connection, stopping client and aborting to free cpu time
				Serial.println("connection failed");
				client->stop();
				return;
			}
		}
		Serial.println("Server is Online!") ;
		xmlBuildMessage();
		
		client->print("POST /Receive/WebService.asmx HTTP/1.1 \r\n");
		client->print("User-Agent: curl/7.24.0 (x86_64-apple-darwin12.0) libcurl/7.24.0 OpenSSL/0.9.8r zlib/1.2.5 \r\n");
		client->print("Host: 145.48.6.30 \r\n");
		client->print("Connection:  close \r\n");
		client->print("SOAPAction:localhost/Receive/storedata \r\n");
		client->print("Content-Type:text/xml;charset=utf-8 \r\n");
		client->print("Content-Length: " + (String) xmlBuildSize() + " \r\n");
		client->print("\r\n");
		
		xmlBuildTransmitBuffer();
		
		client->print("\r\n"); 
		client->flush();
	}
	else
	{
		Serial.println("DATABASE: buffer empty");
	}
}

void DBClient::getResponse()
{
	if (!client->connected()) 
	{
		client->stop();
		Serial.println("disconnecting.");
	}
}
