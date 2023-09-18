/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  09/10/2020   *******/
/******* Update :            	*******/
/******* SWC    :     USART     *******/
/******* Version:     1.0       *******/
/**************************************/

#ifndef 	UART_INTERFACE_H
#define 	UART_INTERFACE_H


void UART_voidInit(void);

void UART_voidTxData(u8 Copy_u8DataByte);

u8 UART_u8RxData(u8* Copy_pu8RecvDataByte);

u8 UART_u8TxStringSynchWithBlocking(u8* Copy_pu8TxString);

u8 UART_u8RxStringSynchWithBlocking(u8* Copy_pu8RxString);

void UART_voidTxStringAsynch(void (*Copy_pfNotification)(void));

void UART_voidRxStringAsynch(void (*Copy_pfNotification)(void));


#endif