/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  18/9/2020    *******/
/******* SWC    :    LCD        *******/
/******* Version:    1.0        *******/
/**************************************/

#ifndef LCD_PRIVATE_H
#define LCD_PRIVATE_H



#define LCD_4BIT_MODE			0		//DB4 = 0 ---> Data sent or recieved through (DB4 ---> DB7)
#define LCD_8BIT_MODE			1		//DB4 = 1 ---> Data sent or recieved through (DB0 ---> DB7)

#define LCD_u8_CGRAM_CHAR1              0b01000000
#define LCD_u8_CGRAM_CHAR2              0b01001000
#define LCD_u8_CGRAM_CHAR3              0b01010000
#define LCD_u8_CGRAM_CHAR4              0b01011000
#define LCD_u8_CGRAM_CHAR5              0b01100000
#define LCD_u8_CGRAM_CHAR6              0b01101000
#define LCD_u8_CGRAM_CHAR7              0b01110000
#define LCD_u8_CGRAM_CHAR8              0b01111000


#endif