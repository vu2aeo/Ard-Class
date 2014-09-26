#include "qttalker.h"

QtTalker::QtTalker(unsigned long speed)
{
    connSpeed = speed;
}

QtTalker::~QtTalker()
{

}

void QtTalker::Connect()
{
    Serial.begin(connSpeed);
    
    delay(50);
}

void QtTalker::SendDataPacketToQt(float* data)
{
    //Parse the data according to our agreed Arduino<->Qt protocol
    //and send it over the serial line


     //send the start character
     Serial.print('*');

     float total = 0;

     for (int i = 0; i < TX_PKT_SIZE; i++)
     {
       //send the number
       Serial.print(data[i]);

       total+= data[i];

       //send the space character
       Serial.print(',');
     }
     //send the checksum
     Serial.print(total);
     //send the termination characters
     Serial.print(',');
     Serial.print('*');
     Serial.print('&');
}

bool QtTalker::NewDataAvailable()
{
    if(Serial.available())
      {
        //if there is new data on the serial line

        for(int i = 0; i < RX_PKT_SIZE; i++)
        {
          inPkt[i] = Serial.parseFloat();
        }
        
        while (Serial.read() != -1)
        {
          //loop here until serial buffer becomes empty
          
        }

      return true;

    } else return false;

}

void QtTalker::GetIncomingData(float* inData)
{
    for(int i =0; i < RX_PKT_SIZE; i++)
    {
        inData[i] = inPkt[i];
    }
    
}

