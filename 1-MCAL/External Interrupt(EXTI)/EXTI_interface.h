/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  17/09/2020   *******/
/******* Update :   9/1/2022    *******/
/******* SWC    :    EXTI       *******/
/******* Version:    1.0        *******/
/**************************************/

#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H


/* Macros for EXTI Index */
#define EXTI_u8_INT0		0
#define EXTI_u8_INT1		1
#define EXTI_u8_INT2		2

//---------------------------------------------

/* Macros for Edge Types */
#define EXTI_u8_FALLING_EDGE				0
#define EXTI_u8_RISING_EDGE				1
#define EXTI_u8_ANY_LOGICAL_CHANGE			2
#define EXTI_u8_LOW_LEVEL				3

//-------------------------------------
/*
	EXTIIndex ----------> - EXTI0 
			      - EXTI1 
			      - EXTI2
						 
	EdgeType -----------> - Rising Edge 
			      - Falling Edge 
			      - Low Level 
			      - Any Logical Change
*/

u8 EXTI_u8Enable(u8 Copy_u8EXTIIndex, u8 Copy_u8EdgeType);

u8 EXTI_u8Disable(u8 Copy_u8EXTIIndex);

u8 EXTI_u8SetCallBack(void (*Copy_pf)(void), u8 Copy_u8EXTIIndex);

#endif
