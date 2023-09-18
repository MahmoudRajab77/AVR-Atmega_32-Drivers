/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  25/8/2020    *******/
/******* SWC    :    DIO        *******/
/******* Version:    1.0        *******/
/**************************************/
#ifndef DIO_PRIVATE_H
#define DIO_PRIVATE_H

/* Macros for Hardware register definitions */

//-----------< PORT A >-----------------------
#define  PORTA_u8_REG		*((volatile u8*)0x3B)
#define  DDRA_u8_REG 		*((volatile u8*)0x3A)
#define  PINA_u8_REG       	*((volatile u8*)0x39)

//-----------< PORT B >-----------------------
#define  PORTB_u8_REG		*((volatile u8*)0x38)
#define  DDRB_u8_REG		*((volatile u8*)0x37)
#define  PINB_u8_REG		*((volatile u8*)0x36)

//-----------< PORT C >-----------------------
#define  PORTC_u8_REG		*((volatile u8*)0x35)
#define  DDRC_u8_REG		*((volatile u8*)0x34)
#define  PINC_u8_REG		*((volatile u8*)0x33)

//-----------< PORT D >-----------------------
#define  PORTD_u8_REG		*((volatile u8*)0x32)
#define  DDRD_u8_REG		*((volatile u8*)0x31)
#define  PIND_u8_REG		*((volatile u8*)0x30)

//------------------------------------------------------------------

/* Macros for direction of the pins in config file */
#define DIO_u8_INITIAL_INPUT 		0
#define DIO_u8_INITIAL_OUTPUT		1

/* Macros for values of the pins */
#define DIO_u8_INITIAL_INPUT_FLOATIN 		0
#define DIO_u8_INITIAL_INPUT_PUlLUP			1 
#define DIO_u8_INITIAL_OUTPUT_LOW			0
#define	DIO_u8_INITIAL_OUTPUT_HIGH			1

/* Macros for concatination */
#define CONC(b7, b6, b5, b4, b3, b2, b1, b0)			CONC_HELP(b7, b6, b5, b4, b3, b2, b1, b0)
#define CONC_HELP(b7, b6, b5, b4, b3, b2, b1, b0)		0b ## b7 ## b6 ## b5 ## b4 ## b3 ## b2 ## b1 ## b0	


#endif
