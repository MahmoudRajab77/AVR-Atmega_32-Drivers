/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  18/9/2020    *******/
/******* SWC    :    LCD        *******/
/******* Version:    1.0        *******/
/**************************************/

#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H






//-------------------------< Select Copy_u8LineNum>-----------------------------------

#define LCD_u8_LINE0				0
#define LCD_u8_LINE1				1

//-------------------------< Select Copy_u8Locat >------------------------------------

#define LCD_u8_COLUMN0				0
#define LCD_u8_COLUMN1				1
#define LCD_u8_COLUMN2				2
#define LCD_u8_COLUMN3				3
#define LCD_u8_COLUMN4				4
#define LCD_u8_COLUMN5				5
#define LCD_u8_COLUMN6				6
#define LCD_u8_COLUMN7				7
#define LCD_u8_COLUMN8				8
#define LCD_u8_COLUMN9				9
#define LCD_u8_COLUMN10				10
#define LCD_u8_COLUMN11				11
#define LCD_u8_COLUMN12				12
#define LCD_u8_COLUMN13				13
#define LCD_u8_COLUMN14				14
#define LCD_u8_COLUMN15				15

//------------------------------< Select Copy_u8CGCharNum >----------------------------------------------

#define LCD_u8_CG_CHAR1			0
#define LCD_u8_CG_CHAR2			1
#define LCD_u8_CG_CHAR3			2
#define LCD_u8_CG_CHAR4			3
#define LCD_u8_CG_CHAR5			4
#define LCD_u8_CG_CHAR6			5
#define LCD_u8_CG_CHAR7			6
#define LCD_u8_CG_CHAR8			7

//-----------------------------< Config Init Mode & Shift Direction >-----------------------------------

#define LCD_SHIFT_RIGHT			1
#define LCD_SHIFT_LEFT			2


#define LCD_4BIT_MODE			1		//DB4 = 0 ---> Data sent or recieved through (DB4 ---> DB7)
#define LCD_8BIT_MODE			2		//DB4 = 1 ---> Data sent or recieved through (DB0 ---> DB7)







//------------------------------< Functions Prototypes >----------------------------------

void LCD_voidInit(void);

void LCD_voidSendCmnd(u8 Copy_u8cmnd);

void LCD_voidSendChar(u8 Copy_u8Char);

void LCD_voidSendSpecialChar(u8 Copy_u8CGCharNum, u8 Copy_u8LineNum, u8 Copy_u8Locat, u8* Copy_pu8Pattern);

void LCD_voidSendNumber(u32 Copy_u32Number);

void LCD_voidClear(void);

void LCD_voidDisplayShift(u8 Copy_u8ShiftDir);

u8 LCD_u8GoToXY(u8 Copy_u8X, u8 Copy_u8Y); 

u8 LCD_u8SendStr(u8* Copy_pu8Str); 



#endif 
