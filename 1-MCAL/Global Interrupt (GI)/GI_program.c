/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :   17/09/2020  *******/
/******* SWC    :     GI        *******/
/******* Version:    1.0        *******/
/**************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GI_Interface.h"

/* Defination of SREG */
#define  GI_u8_SREG		*((volatile u8 *) 0x5F) //Private

//------------------------------------------------

void GI_voidEnable(void){
	/* Enable global Interrupt */
	SET_BIT(GI_u8_SREG, 7);

}

//----------------------------------------

void GI_voidDisable(void){
	/* Disable global interrupt */
	CLR_BIT(GI_u8_SREG, 7);

}