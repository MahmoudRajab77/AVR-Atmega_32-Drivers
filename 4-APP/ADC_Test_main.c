/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  19/09/2020   *******/
/******* Update :            	*******/
/******* SWC    : ADC_Program_TEST ****/
/******* Version:     1.0       *******/
/**************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#define  F_CPU	8000000UL
#include <util/delay.h>

/* MCAL */
#include "DIO_Interface.h"
#include "ADC_Interface.h"
#include "GI_Interface.h"

/* HAL */
#include "LCD_Interface.h"

void App_voidADCNotificationFunc(u16 Copy_u16DigitalValue);

u16 App_u16DigitalValue = 0xffff;

int main (void){
	u16 Local_u16AnalogValue, Local_u16TempValue;
	DIO_u8Init();
	GI_voidEnable();
	LCD_voidInit();
	ADC_voidInit();
	
	while (1){
		/* Read Analog Signal */
		ADC_u8GetDigitalValueAsynch(ADC_u8_CHANNEL_0, App_voidADCNotificationFunc);
		if (App_u16DigitalValue != 0xffff){ // means that the value is updated by ISR
			
			Local_u16AnalogValue = (u16)(((u32)App_u16DigitalValue * 5000UL) / 1024);
			Local_u16TempValue = Local_u16AnalogValue / 10;
			LCD_u8GoToXY(LCD_u8_LINE_1,0);
			LCD_voidWriteNumber(Local_u16TempValue);
			_delay_ms(1000);
			
			App_u16DigitalValue = 0xffff; // reset back the value for the next loop
		}
		
	}
	return 0;
}

void App_voidADCNotificationFunc(u16 Copy_u16DigitalValue){
	
	App_u16DigitalValue = Copy_u16DigitalValue;
}