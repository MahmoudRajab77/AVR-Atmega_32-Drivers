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


// this is a function to make initialization for the hardware in LCD
/* we have 2 options : 1- 8 bit initialization Mode(if DB4 = 1 ---> Data sent or recieved through (DB0 ---> DB7) )
					   2- 4 bit initialization Mode(if DB4 = 0 ---> Data sent or recieved through (DB4 ---> DB7) ) */					   	
void LCD_voidInit(void);

// function to send cmnd 
void LCD_voidSendCmnd(u8 Copy_u8cmnd);

void LCD_voidSendChar(u8 Copy_u8Char);

u8 LCD_voidGoToXY(u8 Copy_u8X, u8 Copy_u8Y); 

void LCD_voidSendStr(u8* Copy_pu8Str); 

void LCD_voidClear(void);

/* The variable CharAdd refers to the address of the first byte in the required char to draw in
	- Char 0 = 0
	- Char 1 = 8
	- Char 2 = 16
	- Char 3 = 24
	- Char 4 = 32
    and so on untill Char 7 */
void LCD_voidSendSpecialChar(u8 Copy_u8CharAdd, u8 Copy_u8LineNum, u8 Copy_u8Locat, u8* Copy_pu8Pattern);

#endif 