/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  18/9/2020    *******/
/******* SWC    :    LCD        *******/
/******* Version:    1.0        *******/
/**************************************/

#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H



#define LCD_u8_LINE0			0
#define LCD_u8_LINE1			1

#define LCD_SHIFT_RIGHT			0
#define LCD_SHIFT_LEFT			1





void LCD_voidInit(void);

void LCD_voidSendCmnd(u8 Copy_u8cmnd);

void LCD_voidSendChar(u8 Copy_u8Char);

/* 
   (Copy_u8CGLocat)options:  - LCD_u8_CGRAM_CHAR1
							 - LCD_u8_CGRAM_CHAR2
							 - LCD_u8_CGRAM_CHAR3	
							 - LCD_u8_CGRAM_CHAR4 
							 - LCD_u8_CGRAM_CHAR5 
							 - LCD_u8_CGRAM_CHAR6 
							 - LCD_u8_CGRAM_CHAR7 
							 - LCD_u8_CGRAM_CHAR8  */ 

void LCD_voidSendSpecialChar(u8 Copy_u8CGLocat, u8 Copy_u8LineNum, u8 Copy_u8Locat, u8* Copy_pu8Pattern)

void LCD_voidSendNumber(u32 Copy_u32Number);

void LCD_voidClear(void);

void LCD_voidDisplayShift(u8 Copy_u8ShiftDir);

u8 LCD_u8GoToXY(u8 Copy_u8X, u8 Copy_u8Y); 

u8 LCD_u8SendStr(u8* Copy_pu8Str); 



#endif 