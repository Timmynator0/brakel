/*

*/
#include <Arduino.h>

#define SCREEN_CRITICAL_ERROR 0
#define SCREEN_ERROR 1
#define SCREEN_MESSAGE 2
#define SCREEN_DEBUG 3
#define MAX_INT 32767

struct message{
  char* value;
  String ID;
  int type;
  int number;
};

void LCDSetup();
void LCDUpdate();
bool LCDAddError(message newError);
bool LCDRemoveError(String oldError);
bool LCDAddMessage(message newMessage);
bool LCDRemoveMessage(String oldMessage);
bool LCDAddBrokenNode(char* newNode);
bool LCDRemoveBrokenNode(String oldNode);
void LCDBeep();