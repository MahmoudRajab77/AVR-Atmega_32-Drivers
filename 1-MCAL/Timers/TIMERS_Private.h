/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  26/5/2020    *******/
/******* Update :            	*******/
/******* SWC    :    TIMERS     *******/
/******* Version:     1.0       *******/
/**************************************/

#ifndef TIMERS_PRIVATE_H
#define TIMERS_PRIVATE_H


//-----------------------< Timers Common Registers >--------------------------------------

/* Timers Interrupt Mask Register */
#define TIMERS_u8_TIMSK_REG			*((volatile u8*)0x59)


/* Timers Interrupt Flags Register */
#define TIMERS_u8_TIFR_REG			*((volatile u8*)0x58)

//-----------------------< Timer_0 Registers >---------------------------------------------

#define TIMERS_u8_TCCR0_REG			*((volatile u8*)0x53)	//control register	
#define TIMERS_u8_TCNT0_REG			*((volatile u8*)0x52)	//counter register
#define TIMERS_u8_OCR0_REG			*((volatile u8*)0x5C)	//output compare register

//-----------------------< Timer_1 Registers >----------------------------------------------

#define TIMERS_u8_TCCR1A_REG		*((volatile u8*)0x4F) 	//control register A 
#define TIMERS_u8_TCCR1B_REG		*((volatile u8*)0x4E) 	//control register B 

//--------------

#define TIMERS_u8_TCNT1H_REG		*((volatile u8*)0x4D) 	//counter register HIGH BYTE
#define TIMERS_u8_TCNT1L_REG		*((volatile u8*)0x4C)	//counter register LOW BYTE

#define TIMERS_u16_TCNT1_REG		*((volatile u16*)0x4C)  //full counter register 

//--------------

#define TIMERS_u8_OCR1AH_REG		*((volatile u8*)0x4B)	//output compare register A HIGH BYTE
#define TIMERS_u8_OCR1AL_REG		*((volatile u8*)0x4A)	//output compare register A LOW BYTE

#define TIMERS_u16_OCR1A_REG		*((volatile u16*)0x4A)	//full output compare register A 

//-------------

#define TIMERS_u8_OCR1BH_REG		*((volatile u8*)0x49)	//output compare register B HIGH BYTE
#define TIMERS_u8_OCR1BL_REG		*((volatile u8*)0x48)	//output compare register B LOW BYTE

#define TIMERS_u16_OCR1B_REG		*((volatile u16*)0x48)	//full output compare register B 

//-------------

#define TIMERS_u8_ICR1H_REG         *((volatile u8*)0x47) 	//input capture register HIGH BYTE
#define TIMERS_u8_ICR1L_REG         *((volatile u8*)0x46)	//input capture register LOW BYTE	

#define TIMERS_u16_ICR1_REG         *((volatile u16*)0x46)	// full input capture register 	



#endif 