/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  10/10/2020   *******/
/******* Update :            	*******/
/******* SWC    :     SPI       *******/
/******* Version:     1.0       *******/
/**************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SPI_Interface.h"
#include "SPI_Private.h"
#include "SPI_Config.h"


void SPI_voidInit(void)
{
	#if (SPI_u8_MODE == SPI_u8_MASTER_MODE)
		/* Data Order = MSB First */
		CLR_BIT(SPI_u8_SPCR_REG, 5);
		
		/* Select Master mode */
		SET_BIT(SPI_u8_SPCR_REG, 4);
		
		/* Select Master mode */
		SET_BIT(SPI_u8_SPCR_REG, 4);
		
		/* Clk polarity falling/rising and clk phase Setup/Sample */
		SET_BIT(SPI_u8_SPCR_REG, 3);
		SET_BIT(SPI_u8_SPCR_REG, 2);
	
		/* Select Clk Fosc/64 */
		SET_BIT(SPI_u8_SPCR_REG, 1);
		CLR_BIT(SPI_u8_SPCR_REG, 0);
	
	#elif (SPI_u8_MODE == SPI_u8_SLAVE_MODE)
		/* Data Order = MSB First */
		CLR_BIT(SPI_u8_SPCR_REG, 5);
		
		/* Select Slave mode */
		SET_BIT(SPI_u8_SPCR_REG, 4);
		
		/* Select Slave mode */
		CLR_BIT(SPI_u8_SPCR_REG, 4);
		
		/* Clk polarity falling/rising and clk phase Setup/Sample */
		SET_BIT(SPI_u8_SPCR_REG, 3);
		SET_BIT(SPI_u8_SPCR_REG, 2);
	#else 
		#error "Wrong Choice"
	
	#endif
	/* Enable SPI */
	SET_BIT(SPI_u8_SPCR_REG, 6);
	
}//end SPI_voidInit

//--------------------------------------------------------------------------------------------------

u8   SPI_u8TxRx(u8 Copy_u8DataByte, u8* Copy_pu8RecieveData)
{
	u8 Local_u8ErrorState = STD_TYPES_NOK;
	if (Copy_pu8RecieveData != NULL)
	{
		/* Send DataByte */
		SPI_u8_SPDR_REG = Copy_u8DataByte;
		
		/* Check Falg */
		while (!GET_BIT(SPI_u8_SPSR_REG, 7));
		
		/* Read the input Data */
		*Copy_pu8RecieveData = SPI_u8_SPDR_REG;
		
		Local_u8ErrorState = STD_TYPES_OK;
	}
	return Local_u8ErrorState;	
}// end SPI_u8TxRx
