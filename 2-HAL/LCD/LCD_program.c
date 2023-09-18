/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  18/9/2020    *******/
/******* SWC    :    LCD        *******/
/******* Version:    1.0        *******/
/**************************************/
/* LCD_program.c*/

/* LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#define F_CPU 	8000000UL
#include <util/delay.h>

/* MCAL */
#include "DIO_interface.h"

/* HAL */
#include "LCD_interface.h"
#include "LCD_private.h"
#include "LCD_config.h"


void LCD_voidInit(void)
{
	_delay_ms(35);
	/* function set cmnd  0b00111000 */
	LCD_voidSendCmnd(0b00111000);
	_delay_us(40);
	/* Display on/off control */
	LCD_voidSendCmnd(0b00001111);
	_delay_us(40);
	/* Display clear */
	LCD_voidSendCmnd(0b00000001);
	_delay_ms(2);
	/* Entry mode set */
	LCD_voidSendCmnd(0b00000110);
}

//-----------------------------------------------------------------------------------------------

void LCD_voidSendCmnd(u8 Copy_u8cmnd)
{
	/* Rs = 0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_Rs_PIN, DIO_u8_LOW);
	
	/* Rw = 0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_Rw_PIN, DIO_u8_LOW);
	
	/* send cmnd Byte to the data pins of LCD */
	DIO_u8SetPortValue(LCD_u8_DATA_PORT, Copy_u8cmnd);
	
	/* Pulse of enable pin E = 1 , E = 0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_u8_HIGH);
	_delay_us(1);
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_u8_LOW);
	_delay_us(1);
	
}//end send cmnd function

//------------------------------------------------------------------------------------------------------

void LCD_voidSendChar(u8 Copy_u8Char)
{
	/* Rs = 1 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_Rs_PIN, DIO_u8_HIGH);
	
	/* Rw = 0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_Rw_PIN, DIO_u8_LOW);
	
	/* send char Byte to the data pins of LCD */
	DIO_u8SetPortValue(LCD_u8_DATA_PORT, Copy_u8char);
	
	/* Pulse of enable pin E = 1 , E = 0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_u8_HIGH);
	_delay_us(1);
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_u8_LOW);
	_delay_us(1);
}//end send char function 

//---------------------------------------------------------------------------------------------------------

u8 LCD_voidGoToXY(u8 Copy_u8X, u8 Copy_u8Y)
{
	u8 Local_u8ReturnState = STD_TYPES_OK;
	if ( (Copy_u8X <= 1) && (Copy_u8Y <= 39) )
	{
		switch (Copy_u8X)
		{
			case LCD_u8_LINE0:
				LCD_voidSendCmnd(0x80 + Copy_u8Y);
				break;
			case LCD_u8_LINE1:
				LCD_voidSendCmnd(0xc0 + Copy_u8Y);
				break;
		}
	}//end if 
	else 
    {
		Local_u8ReturnState = STD_TYPES_NOK;
	}//end else 
	
	return Local_u8ReturnState;
}//end GoToXY function

//----------------------------------------------------------------------------------

void LCD_voidSendStr(u8* Copy_pu8Str)
{
	u8 i = 0;
	while(Copy_pu8Str[i] != 0)
	{
		LCD_voidSendChar(Copy_pu8Str[i]);
		i++;
	}//end while	
}//end SendStr function

void LCD_voidClear(void)
{
	LCD_voidSendCmnd(0b00000001);
	_delay_ms(2);
}//end Clear function 

//----------------------------------------------------------------------------------------------------------

void LCD_voidSendSpecialChar(u8 Copy_u8CharAdd, u8 Copy_u8LineNum, u8 Copy_u8Locat, u8* Copy_pu8Pattern)
{
	/* Set the AC --> CGRAM Address */
	switch(Copy_u8CharAdd)
	{
		case 0:
			LCD_voidSendCmnd(0b01000000);
		break;
			
		default:
			LCD_voidSendCmnd(0b01000000 + (Copy_u8CharAdd * 8));
		break;
	}//end switch
	
	/* Draw the wanted pattern */
	u8 i = 0;
	while(i<=7)
	{
		LCD_voidSendChar(Copy_pu8Pattern[i]);
		i++;
	}//end while
	
	/* Display the pattern at DDRAM */
	LCD_voidGoToXY(Copy_u8LineNum, Copy_u8Locat);
	LCD_voidSendChar(Copy_u8CharAdd);

}//end SendSpecialChar function 
