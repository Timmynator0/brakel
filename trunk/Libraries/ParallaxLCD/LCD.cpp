/*

 */
#include <LCD.h>

//broken nodes
char* brokenNodes[10];
int numberBrokenNodes = 0;
int currentBrokenNode = 0;

//errors
LCDMessage errors[5];
int numberErrors = 0;
int currentError = 0;

//LCDMessages
LCDMessage LCDMessages[10];
int numberLCDMessages = 0;
int currentLCDMessage = 0;

bool updated = false;
bool initialized = false;
int sinceLastUpdate = MAX_INT;

void LCDSetup() {
  // initialize LCD screen and turn the light on:
  Serial1.begin(9600);
  delay(200);//delay om te wachten met de rest van de init. Anders komt niet alles aan.
//  Serial1.print("alksdjf");
  Serial1.write(0x16);
  Serial1.write(0x80);
  Serial1.write(0x11);
  delay(100);
  //LCDBeep();
  initialized = true;
}

void LCDUpdate()
{
  Serial1.write(0x16);
  if(!initialized || (numberErrors+numberBrokenNodes+numberLCDMessages != 0) || updated || sinceLastUpdate >= 5)
  {
    sinceLastUpdate = 0;
    updated = false;
    
    if(!initialized)
    {LCDSetup();}
    
    Serial1.write(0x0C);
    Serial1.write(0x80);
    if(numberErrors==0)
    {
      Serial1.print("Geen foutmeldingen.");
    }
    else
    {
      Serial1.print(errors[currentError].value);
      currentError++;
      currentError = currentError % numberErrors;
    }
    Serial1.write(0x94);
    if(numberBrokenNodes==0)
    {
      Serial1.print("Node's OK.");
    }
    else
    {
      Serial1.print("Node ");
      Serial1.print(brokenNodes[currentBrokenNode]);
      Serial1.print(" kapot.");
      currentBrokenNode++;
      currentBrokenNode = (currentBrokenNode % numberBrokenNodes) % 10;
      Serial.print("Kapotte node: ");
      Serial.println(brokenNodes[currentBrokenNode]);
      Serial.print("Array Index: ");
      Serial.println(currentBrokenNode);
      //currentBrokenNode = currentBrokenNode ;
    }
    Serial1.write(0xA8);
    if(numberBrokenNodes > 10)
    {
      Serial1.print(numberBrokenNodes);
      Serial1.print(" node's kapot.");
      Serial1.write(0xBC);
    }
    if(numberLCDMessages == 0)
    {
      Serial1.print("Geen berichten.");
    }
    else
    {
      Serial1.print(LCDMessages[currentLCDMessage].value);
      currentLCDMessage++;
      currentLCDMessage = currentLCDMessage % numberLCDMessages;
    }
  }
  sinceLastUpdate++;
}

bool LCDAddError(LCDMessage newError)
{
  if(numberErrors < 5)
  {
    numberErrors++;
    errors[numberErrors-1] = newError;
    return true;
  }
  else
  {
    for(int i = 0; i<5; i++ )
    {
      errors[i] = errors[i+1];
    }
    errors[5] = newError;
    return true;
  }
}

bool LCDRemoveError(String oldError)
{
  bool returnBool = false;
  int teller = 0;
  for(int i = 0; i < numberErrors; i++ )
  {
    errors[teller] = errors[i];
    if(!(oldError.equalsIgnoreCase(errors[i].value)))
    {
      teller++;
    }
    else
    {
      returnBool = true;
      numberErrors--;
    }
  } 
  return returnBool;
}

bool LCDAddMessage(LCDMessage newLCDMessage)
{
  if(numberLCDMessages < 10)
  {
    numberLCDMessages++;
    LCDMessages[numberLCDMessages-1] = newLCDMessage;
    return true;
  }
  else
  {
    for(int i = 0; i<9; i++ )
    {
      LCDMessages[i] = LCDMessages[i+1];
    }
    LCDMessages[9] = newLCDMessage;
    return true;
  }
}

bool LCDRemoveLCDMessage(String oldLCDMessage)
{
  bool returnBool = false;
  int teller = 0;
  for(int i = 0; i < numberLCDMessages; i++ )
  {
    LCDMessages[teller] = LCDMessages[i];
    if(!(oldLCDMessage.equalsIgnoreCase(LCDMessages[i].value)))
    {
      teller++;
    }
    else
    {
      returnBool = true;
      numberLCDMessages--;
    }
  } 
  return returnBool;
}

bool LCDAddBrokenNode(char* newNode)
{
  numberBrokenNodes++;
  if(numberBrokenNodes != 10)
  {
    brokenNodes[numberBrokenNodes-1] = newNode;
  }
  else
  {
    for(int i = 0; i<9; i++ )
    {
      brokenNodes[i] = brokenNodes[i+1];
    }
    brokenNodes[9] = newNode;
  }
  return true;
}

bool LCDRemoveBrokenNode(String oldNode)
{
  bool returnBool = false;
  int teller = 0;
  for(int i = 0; i<numberBrokenNodes; i++)
  {
    brokenNodes[teller] = brokenNodes[i];
    if(!(oldNode.equalsIgnoreCase(brokenNodes[i])))
    {
      teller++;
    }  
    else
    {
      returnBool = true;
      numberBrokenNodes--;
    }  
  }
  return returnBool;
}

void LCDBeep()
{
  Serial1.write(0xD4);
  Serial1.write(0xE4);
  Serial.println("Beeped");
}

void LCDWrite(String message)
{
    Serial1.write(0x0C);
	Serial1.write(message);
}