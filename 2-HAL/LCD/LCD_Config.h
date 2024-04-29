/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  18/9/2020    *******/
/******* SWC    :    LCD        *******/
/******* Version:    1.0        *******/
/**************************************/


#ifndef LCD_CONFIG_H
#define LCD_CONFIG_H
	
	
	
/* Macros for LCD Pins Config */
#define LCD_u8_CONTROL_PORT			DIO_u8_PORTA
#define LCD_u8_Rs_PIN 				DIO_u8_PIN0
#define LCD_u8_Rw_PIN				DIO_u8_PIN1
#define LCD_u8_E_PIN				DIO_u8_PIN2

#define LCD_u8_DATA_PORT			DIO_u8_PORTD			
	
	
/* Select : - LCD_4BIT_MODE
			- LCD_8BIT_MODE */	
#define LCD_u8_INIT_MODE			LCD_8BIT_MODE

/* Select : - LCD_SHIFT_RIGHT
			- LCD_SHIFT_LEFT */
#define LCD_u8_SHIFT_DIR			LCD_SHIFT_RIGHT
	
	
	
#endif
