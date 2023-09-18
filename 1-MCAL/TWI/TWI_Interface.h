/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  14/10/2020   *******/
/******* Update :            	*******/
/******* SWC    :     TWI       *******/
/******* Version:     1.0       *******/
/**************************************/

#ifndef TWI_INTERFACE_H
#define TWI_INTERFACE_H


typedef enum 
{
	TWI_OK = 1, 
	TWI_SC_NOK = 2,
	TWI_RSC_NOK = 3,  
	TWI_SLA_W_NOK =4, 
	TWI_SLA_R_NOK = 5,
	TWI_DATA_SENT_NOK =6,
	TWI_DATA_RECV_NOK = 7,
	TWI_BUS_LOST = 8,
	TWI_POINTER_ERROR=9
	
}TWI_ErrorCode;


void TWI_voidMasterInit(void);

TWI_ErrorCode TWI_enumSlaveInit(u8 Copy_u8SlaveAddress);

TWI_ErrorCode TWI_enumSendStartCondition(void);

TWI_ErrorCode TWI_enumSendReStartCondition(void);

TWI_ErrorCode TWI_enumSendSlaveWithWrite(u8 Copy_u8SlaveAddress);

TWI_ErrorCode TWI_enumSendSlaveWithRead(u8 Copy_u8SlaveAddress);

TWI_ErrorCode TWI_enumSendData(u8 Copy_u8Data);

TWI_ErrorCode TWI_enumRecieveData(u8* Copy_pu8RecieveData);

void TWI_voidSendStopCondition(void);


#endif