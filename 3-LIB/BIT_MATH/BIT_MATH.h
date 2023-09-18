/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  23/05/2020   *******/
/******* Update :            	*******/
/******* SWC    :    BIT_MATH   *******/
/******* Version:     1.0       *******/
/**************************************/


#ifndef _BIT_MATH_H
#define _BIT_MATH_H

#define SET_BIT(VAR,BITNO) (VAR) |=  (1 << (BITNO))
#define CLR_BIT(VAR,BITNO) (VAR) &= ~(1 << (BITNO))
#define TOG_BIT(VAR,BITNO) (VAR) ^=  (1 << (BITNO))
#define GET_BIT(VAR,BITNO) (((VAR) >> (BITNO)) & 0x01)


#endif