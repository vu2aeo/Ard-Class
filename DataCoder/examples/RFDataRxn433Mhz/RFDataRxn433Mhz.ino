#include <DataCoder.h>
#include <VirtualWire.h>

const int rx_pin = 11;
const int led_pin = 13;
const int baudRate = 1000;

void setup()
{
  delay(1000);
  Serial.begin(9600);
  pinMode(led_pin,OUTPUT);
  digitalWrite(led_pin,LOW);
  SetupRFDataRxnLink(rx_pin, baudRate);

}

void loop()
{
	
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  
  union RFData inDataSeq;//To store incoming data
  
  float inArray[RF_DATA_ARRAY_SIZE];//To store decoded information
  //RF_DATA_ARRAY_SIZE can be changed if need be inside DataCoder.h
  
  
  if(RFLinkDataAvailable(buf, &buflen))
  {
        digitalWrite(led_pin, HIGH);
        
        for(int i =0; i< buflen; i++)
        {
          inDataSeq.s[i] = buf[i];
        }
        
        Serial.println();
        
        digitalWrite(led_pin, LOW);
      
        DecodeRFData(inArray, inDataSeq);
        
        //Do something with the information that have been received
       
        Serial.print("Incoming Data:");
        
        for (int i=0; i < RF_DATA_ARRAY_SIZE; i++)
          {
            Serial.print(inArray[i]);
            Serial.print(", ");
          }
          Serial.println();
          Serial.print("Bytes Used:");
          Serial.println(RF_DATA_ARRAY_SIZE * 2);
  }
  
}

