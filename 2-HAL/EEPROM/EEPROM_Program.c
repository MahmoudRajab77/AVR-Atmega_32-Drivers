/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  17/10/2020   *******/
/******* Update :            	*******/
/******* SWC    :    EEPROM     *******/
/******* Version:     1.0       *******/
/**************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#define F_CPU	8000000UL
#include <util/delay.h>

#include "TWI_Interface.h"

#include "EEPROM_Interface.h"
#include "EEPROM_Private.h"
#include "EEPROM_Config.h"


void EEPROM_voidInit(void)
{
	TWI_voidMasterInit();
}

//-------------------------------------------------------------------------------------------

u8 EEPROM_u8WriteDataByte(u8 Copy_u8Data, u16 Copy_u16ByteAddrs)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	TWI_ErrorCode Local_enumTWIErrorState = TWI_OK;
	
	/* Send Start Condition */
	Local_enumTWIErrorState = TWI_enumSendStartCondition();
	Local_u8ErrorState = Private_u8ErrorCheck(Local_enumTWIErrorState);	// Check the error State 
	
	/* Send SLA+W */
	Local_enumTWIErrorState = TWI_enumSendSlaveWithWrite((EEPROM_u8_FIXED_ADDRS) | (EEPROM_u8_A2_value<<2) | ((u8)(Copy_u16ByteAddrs>>8)));// Parameter missing (byte of addrs)
	Local_u8ErrorState = Private_u8ErrorCheck(Local_enumTWIErrorState); 
	
	/* Send the rest of the byte addrs */
	Local_enumTWIErrorState = TWI_enumSendData((u8)Copy_u16ByteAddrs);
	Local_u8ErrorState = Private_u8ErrorCheck(Local_enumTWIErrorState);  
	
	/* Send data byte */
	Local_enumTWIErrorState = TWI_enumSendData(Copy_u8Data);
	Local_u8ErrorState = Private_u8ErrorCheck(Local_enumTWIErrorState);  
	
	/* Send Stop Condition */
	TWI_voidSendStopCondition();
	
	/* Delay before the next start condition */
	_delay_ms(5);
	
	return Local_u8ErrorState;
	
}// end EEPROM_u8WriteDataByte

//----------------------------------------------------------------------------------------------------------

u8 EEPROM_u8ReadDataByte(u8* Copy_pu8Data, u16 Copy_u16ByteAddrs)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	TWI_ErrorCode  Local_enumTWIErrorState = TWI_OK;
	
	if (Copy_pu8Data != NULL)
	{
		/* Send Start Condition */
		Local_enumTWIErrorState = TWI_enumSendStartCondition();
		Local_u8ErrorState = Private_u8ErrorCheck(Local_enumTWIErrorState);	// Check the error State 
		
		/* Send SLA+W */
		Local_enumTWIErrorState = TWI_enumSendSlaveWithWrite((EEPROM_u8_FIXED_ADDRS) | (EEPROM_u8_A2_value<<2) | ((u8)(Copy_u16ByteAddrs>>8)));// Parameter missing (byte of addrs)
		Local_u8ErrorState = Private_u8ErrorCheck(Local_enumTWIErrorState); 
		
		/* Send the rest of the byte addrs */
		Local_enumTWIErrorState = TWI_enumSendData((u8)Copy_u16ByteAddrs);
		Local_u8ErrorState = Private_u8ErrorCheck(Local_enumTWIErrorState);
		
		/* Send REstart condition */ 
		Local_enumTWIErrorState = TWI_enumSendReStartCondition();
		Local_u8ErrorState = Private_u8ErrorCheck(Local_enumTWIErrorState);
		
		/* Send SLA+R */
		Local_enumTWIErrorState = TWI_enumSendSlaveWithRead((EEPROM_u8_FIXED_ADDRS) | (EEPROM_u8_A2_value<<2) | ((u8)(Copy_u16ByteAddrs>>8)))
		Local_u8ErrorState = Private_u8ErrorCheck(Local_enumTWIErrorState);
		
		/* Read data */
		Local_enumTWIErrorState = TWI_enumRecieveData(Copy_pu8Data);
		Local_u8ErrorState = Private_u8ErrorCheck(Local_enumTWIErrorState);
		
		/* Send Stop Condition */
		TWI_voidSendStopCondition();
		
		/* Delay before the next start condition */
		_delay_ms(5);
		
	}// end if 
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}		
	
	return Local_u8ErrorState;
	
}// end EEPROM_u8ReadDataByte

//------------------------------------------------------------------------------------------------------------

static u8 Private_u8ErrorCheck(TWI_ErrorCode Copy_enumError)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if (Copy_enumError != TWI_OK )
	{
		Local_u8ErrorState = STD_TYPES_NOK; 
	}	
	return Local_u8ErrorState;
}