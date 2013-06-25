#ifndef DBClient_h
#define DBClient_h
#include "SPI.h"
#include "Ethernet.h"
#include "BufferManager.h"
#include "String.h"

class DBClient{
public:
void setBufferManager(BufferManager *b);
void setEthernetClient(EthernetClient *client);
void dbClientSend();
void getResponse();
BufferManager *buffermanagerInstance;
SDManager	*sdmanagerInstance;
EthernetClient *client;
bool sendSucces = true;;

private:
void xmlBuildInit();
int xmlBuildSize();
int xmlBuildTransmitBuffer();
void xmlBuildStringItem( const char *str );
void xmlBuildDataItem(int data);
void xmlBuildMessage();

};

#endif