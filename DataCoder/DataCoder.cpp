#include "DataCoder.h"

//#include <QDebug>

void SetupRFDataTxnLink(int transmit_pin, int baudRate)
{
  vw_set_tx_pin(transmit_pin);
  vw_setup(baudRate);
}

void SetupRFDataRxnLink(int rx_pin, int baudRate)
{
  vw_set_rx_pin(rx_pin);
  vw_setup(baudRate);
  vw_rx_start();
}

bool RFLinkDataAvailable(uint8_t* buf, uint8_t* buflen)
{
if(vw_get_message(buf,buflen)) return true;
else return false;
}



void EncodeRFData(float* outArray, RFData& outData)
{
    //qDebug() << "Encoded Values..." ;

    for (int i = 0; i < RF_DATA_ARRAY_SIZE ; i++)
    {
        outData.dataBox[i] = (unsigned short)(outArray[i] * 10 * RF_DATA_DECIMAL_PLACES);

        //qDebug() << "Data:" << i << " = " << outData.dataBox[i];
    }

}

void TransmitRFData(RFData outDataSeq, RFData& inDataSeq)
{
    for (int i = 0; i < RF_DATA_ARRAY_SIZE * UNION_EXPANSION_FACTOR; i++)
    {
        inDataSeq.s[i] = outDataSeq.s[i];
    }
}

void TransmitRFData(RFData outDataSeq)
{
    //Call the VirtualWire library using outDataSeq.s[] as argument

    
     if(sizeof(outDataSeq.s) <= 27) //Max allowable packet size in VirtualWire library is 27 bytes
     {
         vw_send((uint8_t*)outDataSeq.s, sizeof(outDataSeq.s));

         vw_wait_tx();

         delay(200);
     }

     
}

void DecodeRFData(float* inArray, RFData inDataSeq)
{
    for (int i = 0; i < RF_DATA_ARRAY_SIZE ; i++)
    {
        inArray[i] = ((float)inDataSeq.dataBox[i]) / (10 * RF_DATA_DECIMAL_PLACES);

        //qDebug() << "Data Decoded:" << i << " = " << inArray[i];
    }

}
