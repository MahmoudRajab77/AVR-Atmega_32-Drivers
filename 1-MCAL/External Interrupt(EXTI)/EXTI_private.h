/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  17/09/2020   *******/
/******* Date   :   9/1/2022    *******/
/******* SWC    :    EXTI       *******/
/******* Version:    1.0        *******/
/**************************************/

#ifndef EXTI_PRIVATE_H
#define EXTI_PRIVATE_H


#define EXTI_u8_MCUCR_REG				      *((volatile u8 *) 0x55) 
#define EXTI_u8_MCUCSR_REG				    *((volatile u8 *) 0x54) 
#define EXTI_u8_GICR_REG	     		    *((volatile u8 *) 0x5B)
#define EXTI_u8_GIFR_REG		    	    *((volatile u8 *) 0x5A)

#define ISC00_BIT						0		// For INT0
#define ISC01_BIT						1	    // For INT0 
#define ISC10_BIT						2		// For INT1
#define ISC11_BIT						3		// For INT1
#define ISC2_BIT						6		// For INT2

#define INT0_PIE						6
#define INT1_PIE						7
#define INT2_PIE						5

#endif 
