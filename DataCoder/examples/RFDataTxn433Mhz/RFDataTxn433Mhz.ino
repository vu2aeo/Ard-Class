#include <DataCoder.h>
#include <VirtualWire.h>

const int transmit_pin = 12;
const int led_pin = 13;
const int baudRate = 1000;

void setup()
{
  pinMode(led_pin,OUTPUT);
  
  SetupRFDataTxnLink(transmit_pin, baudRate);

}

void loop()
{
  float outArray[RF_DATA_ARRAY_SIZE];//the number fo elements that 
  //will be transmitted. I use four elements. 
  //RF_DATA_ARRAY_SIZE can be changed if need be inside DataCoder.h
  
  outArray[0] = 203.4;
  outArray[1] = -167.8;
  outArray[2] = -998.5;
  outArray[3] = 10.3;
  
  union RFData outDataSeq;
 
  EncodeRFData(outArray, outDataSeq); 
  
  TransmitRFData(outDataSeq);  
  
  digitalWrite(led_pin, HIGH);
  
  delay(100);
  
  digitalWrite(led_pin,LOW);
  
  delay(500);
  
}


