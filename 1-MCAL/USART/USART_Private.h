/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  09/10/2020   *******/
/******* Update :            	*******/
/******* SWC    :     USART     *******/
/******* Version:     1.0       *******/
/**************************************/

#ifndef 	UART_PRIVATE_H
#define 	UART_PRIVATE_H


#define UART_u8_UCSRC_REG		*((volatile u8*)0x40)
#define UART_u8_UBRRH_REG		*((volatile u8*)0x40)

#deine  UART_u8_UBRRL_REG		*((volatile u8*)0x29)

#define UART_u8_UDR_REG			*((volatile u8*)0x2C)
#deine  UART_u8_UCSRA_REG		*((volatile u8*)0x2B)
#define UART_u8_UCSRB_REG		*((volatile u8*)0x2A)


#endif
