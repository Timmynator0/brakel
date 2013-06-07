#ifndef DBClient_h
#define DBClient_h
#include <SPI.h>
#include <Ethernet.h>
#include <BufferManager.h>
#include <String.h>

class DBClient{
public:
void setBufferManager(BufferManager *b);
void setEthernetClient(EthernetClient *client);
void setRTC(RTC_DS1307 *RTC);
void dbClientSend();
BufferManager *buffermanagerInstance;
EthernetClient *client;
RTC_DS1307 *rtc;

private:
void xmlBuildInit();
int xmlBuildSize();
int xmlBuildTransmitBuffer();
void xmlBuildStringItem( const char *str );
void xmlBuildDataItem(int data);
void xmlBuildMessage();

};

#endif