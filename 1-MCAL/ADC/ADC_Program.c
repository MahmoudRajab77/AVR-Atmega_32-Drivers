/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  19/09/2020   *******/
/******* Update :            	*******/
/******* SWC    :     ADC       *******/
/******* Version:     1.0       *******/
/**************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_Interface.h"
#include "ADC_Private.h"
#include "ADC_Config.h"

/* Global pointer to function */
static void (*ADC_pfNotification)(u16) = NULL; 

static u8 ADC_u8BusyFlag = 0;    // this flag indicates if the conversion cycle ended or not 

void ADC_voidInit(void)
{
	/* 1- select Vref = AVCC */
	CLR_BIT(ADC_u8_ADMUX_REG,7);
	SET_BIT(ADC_u8_ADMUX_REG,6);
	
	/* 2- Right Adjust */ 
	CLR_BIT(ADC_u8_ADMUX_REG,5); // this bit is already initialed by 0 but we clear it so that we don't forget
	
	/* 3- Disable Auto Trigger */
	CLR_BIT(ADC_u8_ADCSRA_REG,5); // this bit is already initialed by 0 but we clear it so that we don't forget
	
	/* 4- CLK/64 */  // because 8MHZ / 64 = 125KHZ and this value is between our available range (50KHZ --> 200KHZ)
	SET_BIT(ADC_u8_ADCSRA_REG,2);
	SET_BIT(ADC_u8_ADCSRA_REG,1);
	CLR_BIT(ADC_u8_ADCSRA_REG,0);
	
	/* 5- Enable ADC Peripheral */
	SET_BIT(ADC_u8_ADCSRA_REG,7);

}// end ADC_voidInit 

//-----------------------------------------------------------------------------------

u8 ADC_u8GetDigitalValueSynchNonBlocking(u8 Copy_u8ChannelNB, u16* Copy_pu16DigitalValue)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	u32 Local_u32TimeOutCounter;
	if ((Copy_u8ChannelNB < 32) && (Copy_pu16DigitalValue != NULL))
	{
		/* Clear Mux 4-->0 bits */
		ADC_u8_ADMUX_REG &= 0b11100000;
		
		/* Select Channel */
		ADC_u8_ADMUX_REG |= Copy_u8ChannelNB;
		
		/* Start Conversion */
		SET_BIT(ADC_u8_ADCSRA_REG,6);
		
		/* Wait untill flag = 1 */
		while ((GET_BIT(ADC_u8_ADCSRA_REG,4) == 0)&&(Local_u32TimeOutCounter < ADC_u32_TIME_OUT_MAX_VALUE)){   // this bit is set to 1 automatically when the conversion finish
		//while (!GET_BIT(ADC_u8_ADCSRA_REG,4));   //same as above with different way
		
			Local_u32TimeOutCounter++;	
		}
		if (Local_u32TimeOutCounter >= ADC_u32_TIME_OUT_MAX_VALUE){
			Local_u8ErrorState = STD_TYPES_NOK;
		}
		else{
			/* Read Digital Value */
			*Copy_pu16DigitalValue = ADC_u16_ADC_REG;
			/* Clearing flag */
			SET_BIT(ADC_u8_ADCSRA_REG,4); // This flag is cleared by setting it to 1
		}
	}// end if 
	else 
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	} 	

	return Local_u8ErrorState;

}// end ADC_u8GetDigitalValueSynchNonBlocking

//----------------------------------------------------------------------------------------

u8 	 ADC_u8GetDigitalValueAsynch(u8 Copy_u8ChannelNB, void (*Copy_pfNotification)(u16))  
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if ((Copy_u8ChannelNB < 32)&&(Copy_pfNotification != NULL) && (ADC_u8BusyFlag == 0)){
		
		/* set the flag to busy case */
		ADC_u8BusyFlag = 1;
		
		/* Update the global Pointer to a function with the Notification function */
		ADC_pfNotification = Copy_pfNotification;
		
		/* Enable ADC Interrupt PIE */
		SET_BIT(ADC_u8_ADCSRA_REG,3);
		
		/* Clear Mux 4-->0 bits */
		ADC_u8_ADMUX_REG &= 0b11100000;
		
		/* Select Channel */
		ADC_u8_ADMUX_REG |= Copy_u8ChannelNB;
		
		/* Start Conversion */
		SET_BIT(ADC_u8_ADCSRA_REG,6);
	}
	else {
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	
	return Local_u8ErrorState;
	
}// end ADC_u8GetdigitalValueAsynch

//-----------------------------------------------------------------------------------------

/* Prototype of ADC ISR */

void __vector_16(void)   __attribute__((signal));


void __vector_16(void){
	
	if (ADC_pfNotification != NULL){
		/* Clear PIE */
		CLR_BIT(ADC_u8_ADCSRA_REG,3);
		
		/* Passing the value to Notification function */
		ADC_pfNotification(ADC_u16_ADC_REG); 
		
		/* Clearing the BusyFlag */
		ADC_u8BusyFlag = 0;
		
		/* the ((ADC_u8_ADCSRA_REG bit 4)) flag will be cleared automatically 
		once it starts to excute the ISR as mentioned in Datasheet */
	
	}//end if 
}
