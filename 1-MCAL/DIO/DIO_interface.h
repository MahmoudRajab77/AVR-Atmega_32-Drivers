/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  25/8/2020    *******/
/******* SWC    :    DIO        *******/
/******* Version:    1.0        *******/
/**************************************/
#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

/*Macros for Ports ID */
#define DIO_u8_PORTA        0
#define DIO_u8_PORTB        1
#define DIO_u8_PORTC        2
#define DIO_u8_PORTD        3

/* Macros for PINS ID */
#define DIO_u8PIN0			0
#define DIO_u8PIN1			1
#define DIO_u8PIN2			2
#define DIO_u8PIN3			3	
#define DIO_u8PIN4			4	
#define DIO_u8PIN5			5
#define DIO_u8PIN6			6
#define DIO_u8PIN7			7

/* Macros for PIN Direction */
#define DIO_u8_INPUT		0
#define DIO_u8_OUTPUT		1

/* Macros for pin value */
#define DIO_u8_HIGH			1
#define DIO_u8_LOW			0

/* prototypes of the DIO Driver */

u8 DIO_u8Init(void);
u8 DIO_u8SetPinDirection(u8 Copy_u8PortId, u8 Copy_u8PinId, u8 Copy_u8PinDirection);
u8 DIO_u8SetPinValue(u8 Copy_u8PortId, u8 Copy_u8PinId, u8 Copy_u8PinValue);
u8 DIO_u8GetPinValue(u8 Copy_u8PortId, u8 Copy_u8PinId, u8* Copy_pu8ReturnedPinValue);

// this function is to set the direction for all the port as input or output 
u8 DIO_u8SetPortDirection(u8 Copy_u8PortId, u8 Copy_u8PortDirection);

u8 DIO_u8SetPortValue(u8 Copy_u8PortId, u8 Copy_u8PortValue);
u8 DIO_u8GetPortValue(u8 Copy_u8PortId, u8* Copy_pu8ReturnedPortValue);


#endif 
