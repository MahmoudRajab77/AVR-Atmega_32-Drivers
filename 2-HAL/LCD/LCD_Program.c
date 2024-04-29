/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  18/9/2020    *******/
/******* SWC    :    LCD        *******/
/******* Version:    1.0        *******/
/**************************************/
/* LCD_program.c*/

/* LIB */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#define F_CPU 	8000000UL
#include <util/delay.h>

/* MCAL */
#include "../../MCAL/DIO/DIO_interface.h"

/* HAL */
#include "LCD_Interface.h"
#include "LCD_Private.h"
#include "LCD_Config.h"


void LCD_voidInit(void)
{
	DIO_u8SetPinDirection(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_OUTPUT);
	DIO_u8SetPinDirection(LCD_u8_CONTROL_PORT,LCD_u8_Rw_PIN,DIO_u8_OUTPUT);
	DIO_u8SetPinDirection(LCD_u8_CONTROL_PORT,LCD_u8_Rs_PIN,DIO_u8_OUTPUT);
	
#if LCD_u8_INIT_MODE == LCD_4BIT_MODE
		
	DIO_u8SetPortDirection(LCD_u8_DATA_PORT, 0b1111);
	
	
	_delay_ms(35);
			
	LCD_voidSendCmnd(0b00100000);
	LCD_voidSendCmnd(0b00100000);
	LCD_voidSendCmnd(0b11000000);
			
	_delay_us(40);
			
	LCD_voidSendCmnd(0b00000000);
	LCD_voidSendCmnd(0b11000000);	// Cursor OFF & Blinking OFF
			
	_delay_us(40);
			
	LCD_voidSendCmnd(0b00000000);
	LCD_voidSendCmnd(0b00010000);
			
	_delay_ms(2);
			
	LCD_voidSendCmnd(0b00000000);
	LCD_voidSendCmnd(0b01100000);
			
		
#elif LCD_u8_INIT_MODE == LCD_8BIT_MODE
		
	DIO_u8SetPortDirection(LCD_u8_DATA_PORT, DIO_PORT_OUTPUT);
	
	_delay_ms(35);
	/* function set cmnd  0b00111000 */
	LCD_voidSendCmnd(0b00111000);
	_delay_us(40);
	/* Display on/off control */
	LCD_voidSendCmnd(0b00001100);
	_delay_us(40);
	/* Display clear */
	LCD_voidSendCmnd(0b00000001);
	_delay_ms(2);
	/* Entry mode set */
	LCD_voidSendCmnd(0b00000110);
	
#else
	#error "Wrong LCD_MODE Configuration parameter"
#endif	
}// end Func

//-----------------------------------------------------------------------------------------------

void LCD_voidSendCmnd(u8 Copy_u8cmnd)
{
	
	/* Rs = 0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_Rs_PIN, DIO_u8_LOW);
		
	/* Rw = 0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_Rw_PIN, DIO_u8_LOW);
		
#if LCD_u8_INIT_MODE == LCD_8BIT_MODE

	/* send cmnd Byte to the data pins of LCD */
	DIO_u8SetPortValue(LCD_u8_DATA_PORT, Copy_u8cmnd); // send the entire byte 

	/* Pulse of enable pin E = 1 , E = 0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_u8_HIGH);
	_delay_us(1);
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_u8_LOW);
	_delay_us(1);

	
	//--------------------------------------------------------------------
#elif LCD_u8_INIT_MODE == LCD_4BIT_MODE
		
	//---------------------< OPERATION 1 >----------------------------

	/* send cmnd Byte to the data pins of LCD */
	DIO_u8SetPortValue(LCD_u8_DATA_PORT, (Copy_u8cmnd & 0xf0)); // send the last 4 bits first

	/* Pulse of enable pin E = 1 , E = 0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_u8_HIGH);
	_delay_us(1);
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_u8_LOW);
	_delay_us(1);

	//---------------------< OPERATION 2 >----------------------------
	
	/* send cmnd Byte to the data pins of LCD */
	DIO_u8SetPortValue(LCD_u8_DATA_PORT, ((Copy_u8cmnd << 4) & 0xf0)); // send the first 4 bits of the byte

	/* Pulse of enable pin E = 1 , E = 0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_u8_HIGH);
	_delay_us(1);
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_u8_LOW);
	_delay_us(1);
	

#else
	#error "Wrong LCD_MODE Configuration parameter"
#endif		
	
}//end send cmnd function

//------------------------------------------------------------------------------------------------------

void LCD_voidSendChar(u8 Copy_u8Char)
{

	/* Rs = 1 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_Rs_PIN, DIO_u8_HIGH);
	
	/* Rw = 0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_Rw_PIN, DIO_u8_LOW);

#if LCD_u8_INIT_MODE ==	LCD_8BIT_MODE

	/* send char Byte to the data pins of LCD */
	DIO_u8SetPortValue(LCD_u8_DATA_PORT, Copy_u8Char);

	/* Pulse of enable pin E = 1 , E = 0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_u8_HIGH);
	_delay_us(1);
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_u8_LOW);
	_delay_us(1);
		

		
#elif LCD_u8_INIT_MODE ==	LCD_4BIT_MODE

	//----------------------< OPERATION 1 >----------------------------
	
	/* send char Byte to the data pins of LCD */
	DIO_u8SetPortValue(LCD_u8_DATA_PORT, (Copy_u8Char & 0xf0));		// send the last 4 bit of the byte first

	/* Pulse of enable pin E = 1 , E = 0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_u8_HIGH);
	_delay_us(1);
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_u8_LOW);
	_delay_us(1);
		
	//----------------------< OPERATION 2 >----------------------------
	
	/* send char Byte to the data pins of LCD */
	DIO_u8SetPortValue(LCD_u8_DATA_PORT, ((Copy_u8Char << 4) & 0xf0));		// send the first 4 bit of the byte

	/* Pulse of enable pin E = 1 , E = 0 */
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_u8_HIGH);
	_delay_us(1);
	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT, LCD_u8_E_PIN, DIO_u8_LOW);
	_delay_us(1);
	
#else 
	#error	"Wrong LCD_MODE Configuration parameter"
#endif

}//end send char function 

//---------------------------------------------------------------------------------------------------------

u8 LCD_u8GoToXY(u8 Copy_u8X, u8 Copy_u8Y)
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
			
			default:
				Local_u8ReturnState = STD_TYPES_NOK;
			break;
		}// end switch
	}//end if 
	else 
    {
		Local_u8ReturnState = STD_TYPES_NOK;
	}//end else 
	
	return Local_u8ReturnState;
}//end GoToXY function

//---------------------------------------------------------------------------------------------------------

u8 LCD_u8SendStr(u8* Copy_pu8Str)
{
	u8 Local_u8ReturnState = STD_TYPES_OK;
	
	u8 Local_u8Index = 0;
	
	if (Copy_pu8Str != NULL)
	{
		for (Local_u8Index = 0 ; Copy_pu8Str[Local_u8Index] != '\0' ; Local_u8Index++)
		{
			LCD_voidSendChar(Copy_pu8Str[Local_u8Index]);
		}	
	}
	else 
	{
		Local_u8ReturnState = STD_TYPES_NOK;
	}
	
	return Local_u8ReturnState;
}//end SendStr function

//---------------------------------------------------------------------------------------------------------

void LCD_voidClear(void)
{
	LCD_voidSendCmnd(0b00000001);
	_delay_ms(2);
	
}//end Clear function 

//----------------------------------------------------------------------------------------------------------

void LCD_voidSendSpecialChar(u8 Copy_u8CGCharNum, u8 Copy_u8LineNum, u8 Copy_u8Locat, u8* Copy_pu8Pattern)
{
	// Variables
	u8 Local_u8CGRAMAddress = 0;


	// Calculating the CGRAM Address
	Local_u8CGRAMAddress = Copy_u8CGCharNum * 8;

	// Set the 6th bit of the Address to HIGH
	SET_BIT(Local_u8CGRAMAddress, 6);

	/* Set the AC --> CGRAM Address */
	LCD_voidSendCmnd(Local_u8CGRAMAddress);

	/* Draw the pattern in CGRAM */
	u8 i = 0;
	while(i<=7)
	{
		LCD_voidSendChar(Copy_pu8Pattern[i]);
		i++;
	}//end while
	
	/* Display the pattern at DDRAM */
	LCD_u8GoToXY(Copy_u8LineNum, Copy_u8Locat);
	LCD_voidSendChar(Copy_u8CGCharNum);

}//end SendSpecialChar function 

//---------------------------------------------------------------------------------------------------------------

void LCD_voidSendNumber(u32 Copy_u32Number)
{
	
    u8 Local_u8Remainder = 0x00;
    u8 Local_u8Counter = 0x00;
    u32 Local_u32Temp = 0;

	while (Copy_u32Number != 0)
    {
        Local_u32Temp = Local_u32Temp * 0x0A;
        Local_u32Temp = Local_u32Temp + Copy_u32Number % 0x0A;
        Copy_u32Number = Copy_u32Number / 0x0A;
        
	}// end while 

	for (Local_u8Counter = 0 ; Local_u32Temp != 0 ; ++Local_u8Counter)
	{
        Local_u8Remainder = Local_u32Temp % 0x0A;
		Local_u32Temp = Local_u32Temp / 0x0A;
		switch (Local_u8Remainder)
        {
			case 0:
				LCD_voidSendChar('0');
			break;
		
			case 1:
				LCD_voidSendChar('1');
			break;
		
			case 2:
				LCD_voidSendChar('2');
			break;
			
			case 3:
				LCD_voidSendChar('3');
			break;
		
			case 4:
				LCD_voidSendChar('4');
			break;
		
			case 5:
				LCD_voidSendChar('5');
			break;
	
			case 6:
				LCD_voidSendChar('6');
			break;
		
			case 7:
				LCD_voidSendChar('7');
			break;
			
			case 8:
				LCD_voidSendChar('8');
			break;
			
			case 9:
				LCD_voidSendChar('9');
			break;

			default:
			break;			
        }// end switch
	
    }// end for
}// end function 

//---------------------------------------------------------------------------------------------------------------

void LCD_voidDisplayShift(u8 Copy_u8ShiftDir)
{
	switch (Copy_u8ShiftDir)
	{
		case LCD_SHIFT_RIGHT:
			
			LCD_voidSendCmnd(0b00011100);	// Shift the entire display to Right
			_delay_us(40);
			
		break;
		
		case LCD_SHIFT_LEFT:
		
			LCD_voidSendCmnd(0b00011000);	// Shift the entire display to Left
			_delay_us(40);
		
		break;
		
		default:
		break;
	}// end switch 
}// end function
