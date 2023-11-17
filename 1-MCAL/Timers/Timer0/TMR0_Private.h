/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  26/5/2020    *******/
/******* Update :            	*******/
/******* SWC    :     TMR0      *******/
/******* Version:     1.0       *******/
/**************************************/

#ifndef TMR0_PRIVATE_H
#define TMR0_PRIVATE_H




/* Timers Interrupt Mask Register */
#define TMR0_u8_TIMSK_REG			*((volatile u8*)0x59)


/* Timers Interrupt Flags Register */
#define TMR0_u8_TIFR_REG			*((volatile u8*)0x58)

//-----------------------< Timer_0 Registers >---------------------------------------------

#define TMR0_u8_TCCR0_REG			*((volatile u8*)0x53)	//control register	
#define TMR0_u8_TCNT0_REG			*((volatile u8*)0x52)	//counter register
#define TMR0_u8_OCR0_REG			*((volatile u8*)0x5C)	//output compare register




#endif 