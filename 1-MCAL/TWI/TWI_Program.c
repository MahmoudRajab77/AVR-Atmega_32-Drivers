/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  14/10/2020   *******/
/******* Update :            	*******/
/******* SWC    :     TWI       *******/
/******* Version:     1.0       *******/
/**************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TWI_Interface.h"
#include "TWI_Private.h"
#include "TWI_Config.h"


void TWI_voidMasterInit(void)
{
	/* Set prescaler value = 1 */
	CLR_BIT(TWI_u8_TWSR_REG, 0);
	CLR_BIT(TWI_u8_TWSR_REG, 1);
	
	/* Set TWBR Value , SLC = 200KHZ */
	TWI_u8_TWBR_REG = 12;
	
	/* Enable ACK */
	SET_BIT(TWI_u8_TWCR_REG, 6);
	
	/* Enable TWI */
	SET_BIT(TWI_u8_TWCR_REG, 2);

}// end TWI_voidMasterInit

//-------------------------------------------------------------------------------

TWI_ErrorCode TWI_enumSlaveInit(u8 Copy_u8SlaveAddress)
{
	// you have to check the slave add if it included in the listed adresses or not
	
	TWI_ErrorCode Local_enumErrorState = TWI_OK;
	
	/* Set slave address in TWAR Reg */
	TWI_u8_TWAR_REG = Copy_u8SlaveAddress << 1;		// shifting to avoid bit 0 (General call recognition bit)
	
	/* Enable ACK */
	SET_BIT(TWI_u8_TWCR_REG, 6);
	
	/* Enable TWI */
	SET_BIT(TWI_u8_TWCR_REG, 2);
	
	return Local_enumErrorState;
	
}// end TWI_enumSlaveInit

//---------------------------------------------------------------------------------

TWI_ErrorCode TWI_enumSendStartCondition(void)
{
	TWI_ErrorCode Local_enumErrorState = TWI_OK;
	
	/* Send Start Condition */
	SET_BIT(TWI_u8_TWCR_REG, 5);
	
	/* Clear Flag to start operation */ 				// the flage is cleared by writing 1
	SET_BIT(TWI_u8_TWCR_REG, 7);
	
	/* Wait for the flag (operation ended)*/
	while (!GET_BIT(TWI_u8_TWCR_REG, 7));
	
	/* Check Status => START CONDITION */
	if ((TWI_u8_TWSR_REG & 0xF8) != START_COND )
	{
		Local_enumErrorState = TWI_SC_NOK;
	}	
	
	return Local_enumErrorState;

}//end TWI_enumSendStartCondition

//-------------------------------------------------------------------------------

TWI_ErrorCode TWI_enumSendReStartCondition(void)
{
	TWI_ErrorCode Local_enumErrorState = TWI_OK;
	
	/* Send Start Condition */
	SET_BIT(TWI_u8_TWCR_REG, 5);
	
	/* Clear Flag to start operation */
	SET_BIT(TWI_u8_TWCR_REG, 7);
	
	/* Wait for the flag (operation ended)*/
	while (!GET_BIT(TWI_u8_TWCR_REG, 7));	
	
	/* Check Status */
	if ((TWI_u8_TWSR_REG & 0xF8) != RE_START_COND )
	{
		Local_enumErrorState = TWI_RSC_NOK;
	}	
	
	return Local_enumErrorState;

}// end TWI_enumSendReStartCondition

//-----------------------------------------------------------------------------------

TWI_ErrorCode TWI_enumSendSlaveWithWrite(u8 Copy_u8SlaveAddress)
{
	TWI_ErrorCode Local_enumErrorState = TWI_OK;
	
	/* Set TWDR = SLA + W */
	TWI_u8_TWDR_REG = Copy_u8SlaveAddress << 1;
	CLR_BIT(TWI_u8_TWDR_REG, 0);
	
	/* Clear Start Condition for future use */
	CLR_BIT(TWI_u8_TWCR_REG, 5);
	
	/* Clear Flag to start operation */
	SET_BIT(TWI_u8_TWCR_REG, 7);
	
	/* Wait for the flag (operation ended)*/
	while (!GET_BIT(TWI_u8_TWCR_REG, 7));
	
	/* Check Status */
	if ((TWI_u8_TWSR_REG & 0xF8) != SLA_W_OK )
	{
		Local_enumErrorState = TWI_SLA_W_NOK;
	}	
	
	return Local_enumErrorState;
	
}//end TWI_enumSendSlaveWithWrite

//---------------------------------------------------------------------------------------------------

TWI_ErrorCode TWI_enumSendSlaveWithRead(u8 Copy_u8SlaveAddress)
{
	TWI_ErrorCode Local_enumErrorState = TWI_OK;
	
	/* Set TWDR = SLA + R */
	TWI_u8_TWDR_REG = Copy_u8SlaveAddress << 1;
	SET_BIT(TWI_u8_TWDR_REG, 0);
	
	/* Clear Start Condition */
	CLR_BIT(TWI_u8_TWCR_REG, 5);
	
	/* Clear Flag to start operation */
	SET_BIT(TWI_u8_TWCR_REG, 7);
	
	/* Wait for the flag (operation ended)*/
	while (!GET_BIT(TWI_u8_TWCR_REG, 7));
	
	/* Check Status */
	if ((TWI_u8_TWSR_REG & 0xF8) != SLA_R_OK )
	{
		Local_enumErrorState = TWI_SLA_R_NOK;
	}	
	
	return Local_enumErrorState;
	
}//end TWI_enumSendSlaveWithRead

//------------------------------------------------------------------------------------------------------

TWI_ErrorCode TWI_enumSendData(u8 Copy_u8Data)
{
	TWI_ErrorCode Local_enumErrorState = TWI_OK;
	
	/* Set TWDR = Data */
	TWI_u8_TWDR_REG = Copy_u8Data;
	
	/* Clear Flag to start operation */
	SET_BIT(TWI_u8_TWCR_REG, 7);
	
	/* Wait for the flag (operation ended)*/
	while (!GET_BIT(TWI_u8_TWCR_REG, 7));
	
	/* Check Status */	
	if ((TWI_u8_TWSR_REG & 0xF8) != DATA_SENT_OK )
	{
		Local_enumErrorState = TWI_DATA_SENT_NOK;
	}	
	
	return Local_enumErrorState;

}// end TWI_enumSendData

//------------------------------------------------------------------------------------------------------

TWI_ErrorCode TWI_enumRecieveData(u8* Copy_pu8RecieveData)
{
	TWI_ErrorCode Local_enumErrorState = TWI_OK;
	
	/* Check the pointer */ 
	if (Copy_pu8RecieveData != NULL)
	{
		/* Clear Flag to start operation */
		SET_BIT(TWI_u8_TWCR_REG, 7);
		
		/* Wait for the flag (operation ended)*/
		while (!GET_BIT(TWI_u8_TWCR_REG, 7));
		
		/* Check Status */
		if ((TWI_u8_TWSR_REG & 0xF8) != DATA_RECV_OK )
		{
			Local_enumErrorState = TWI_DATA_RECV_NOK;
		}	
		else
		{	
			/* Read data */	
			*Copy_pu8RecieveData = TWI_u8_TWDR_REG;
		}
		
	}//end if 	
	else 
	{
		Local_enumErrorState = TWI_POINTER_ERROR;
	}	
	
	return Local_enumErrorState; 
	
}// end TWI_enumRecieveData

//---------------------------------------------------------------------------------------------

void TWI_voidSendStopCondition(void)
{
	/* Send Stop Condition */
	SET_BIT(TWI_u8_TWCR_REG, 4);
	
	/* Clear Flag to start operation */
	SET_BIT(TWI_u8_TWCR_REG, 7);

}// end TWI_voidSendStopCondition