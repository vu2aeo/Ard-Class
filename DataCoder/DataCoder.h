//This code was written by vu2aeo and is free to distribute or modify
//I am not responsible for any damage caused due to this code
//If you distribute this code, you must do it for free
#include "VirtualWire.h"
#ifndef DATACODER_H
#define DATACODER_H

#define RF_DATA_ARRAY_SIZE 4 //The number of elements to be held in the array

#define RF_DATA_DECIMAL_PLACES 1//The number of decimal places that will be encoded

#define UNION_EXPANSION_FACTOR 2//The number of bytes occupied by each element of the encoded RFData packet. This data is 
							//stored in dataBox[]. See below.

//If you change the literals above make sure that RF_DATA_ARRAY_SIZE * UNION_EXPANSION_FACTOR is less than or equal to 27
//This is the max packet size VirtualWare can handle

/* The value of RF_DATA_DECIMAL_PLACES affects data handling as follows:-

	Value		Min Value Handled			Max Value Handled
	0			0						+32767
	1			-3276.7					+3276.7
	2			-327.67					+327.67
	3			-32.767					+32.767
	
	and so on.......

*/

union RFData
{
    int dataBox[RF_DATA_ARRAY_SIZE];//2 bytes each. In Arduino environment, int is 2 bytes. Change this to unsigned int if you want to transmit only positive numbers. The Max value limits of data handled in the table above will then double in size.

    char s[RF_DATA_ARRAY_SIZE * UNION_EXPANSION_FACTOR];//each char is 1 byte so we need 2 chars for
                                                        //each dataBox[] element (which are currently int)
                                                        //if you change the dataBox[] elements to day floats, then 
                                                        //UNION_EXPANSION_FACTOR must be = 4
};

void EncodeRFData(float* outArray, RFData& outData);

void TransmitRFData(RFData outDataSeq, RFData& inDataSeq);//Dummy function for debugging purposes

void TransmitRFData(RFData outDataSeq);

void DecodeRFData(float* inArray, RFData inDataSeq);

void SetupRFDataTxnLink(int transmit_pin, int baudRate);

void SetupRFDataRxnLink(int rx_pin, int baudRate);

bool RFLinkDataAvailable(uint8_t* buf, uint8_t* buflen);

void SetupRFDataRxnLink(int receive_pin, int baudRate);

#endif // DATACODER_H
