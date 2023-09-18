/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  23/05/2020   *******/
/******* Update :            	*******/
/******* SWC    :   STD_TYPES   *******/
/******* Version:     1.0       *******/
/**************************************/


#ifndef _STD_TYPES_H
#define _STD_TYPES_H


/* Unsigned types */
typedef 	unsigned char 			u8;			// 0 ----> 255
typedef 	unsigned short int 		u16;	    // 0 ----> 65536
typedef 	unsigned long int 		u32;		// 0 ----> 4294967296
typedef 	unsigned long long int 	u64;		// 0 ----> 18446744073709551615

/* Signed types */
typedef 	signed char 			s8;			// -128 ----> +127
typedef 	signed short int 		s16;		// -32768 ----> +32767
typedef 	signed long  int 		s32;		// -2147483648 ----> +2147483647
typedef		signed long long int 	s64;		// -9223372037709551618 ----> +9223372037709551617

/* Float types */
typedef float  f32;                 // 4 Byte 
typedef double f64;					// 8 Byte 

#define NULL   ((void *)0)

/* Error status check */
#define STD_TYPES_NOK   0
#define STD_TYPES_OK    1


#endif
