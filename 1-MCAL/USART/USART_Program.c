/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  09/10/2020   *******/
/******* Update :            	*******/
/******* SWC    :     USART     *******/
/******* Version:     1.0       *******/
/**************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_Interface.h"
#include "UART_Private.h"
#include "UART_Config.h"


void UART_voidInit(void)
{
	u8 Local_u8UCSRCtempReg = 0x80; //initial value (bit 7 = 1)
	
	/* Select Baud Rate = 9600*/	
	u16 Local_u16UBRRvalue = 51;
	
	UART_u8_UBRRL_REG = (u8)Local_u16UBRRvalue;
	UART_u8_UBRRH_REG = (u8)(Local_u16UBRRvalue >> 8);
	
	/* Enabel RX,TX */
	SET_BIT(UART_u8_UCSRB_REG, 4);
	SET_BIT(UART_u8_UCSRB_REG, 3);
	
	/* Select character size = 8 bits */
	CLR_BIT(UART_u8_UCSRB_REG, 2);
	SET_BIT(Local_u8UCSRCtempReg, 2);
	SET_BIT(Local_u8UCSRCtempReg, 1);
	
	/* Asynch mode */
	CLR_BIT(Local_u8UCSRCtempReg, 6);
	
	/* Disable parity bit */
	CLR_BIT(Local_u8UCSRCtempReg, 5);
	CLR_BIT(Local_u8UCSRCtempReg, 4);
	
	/* Stop bit = 2 */
	SET_BIT(Local_u8UCSRCtempReg, 3)
	
	/* Update UCSRC REG */
	UART_u8_UCSRC_REG = Local_u8UCSRCtempReg;
	
}//end UART_voidInit

//-------------------------------------------------------------

void UART_voidTxData(u8 Copy_u8DataByte)
{
	/* Check if the TX buffer is empty */
	while (!GET_BIT(UART_u8_UCSRA_REG, 5)); // if busy ,remain in loop
    /* Store data to transmit */
	UART_u8_UDR_REG = Copy_u8DataByte; 		// if empty , get the data to transmit

}// end UART_voidTxData

//---------------------------------------------------------------------------

u8 UART_u8RxData(u8* Copy_pu8RecvDataByte)
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;
	
	if (Copy_pu8RecvDataByte != NULL)
	{
		/* Check the RX flag */
		while (!GET_BIT(UART_u8_UCSRA_REG, 7));
		/* Read the data */
		*Copy_pu8RecvDataByte = UART_u8_UDR_REG;
		
		Local_u8ErrorState = STD_TYPES_OK;
	
	}// end if 
	
	return Local_u8ErrorState;
	
}// end UART_u8RxData

//--------------------------------------------------------------------------------

/*u8 UART_u8TxStringSynchWithBlocking(u8* Copy_pu8TxString)
{
	

}// end UART_u8TxStringSynchWithBlocking
*/
//-----------------------------------------------------------------------------------------



