/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  17/09/2020    *******/
/******* Update :   9/1/2022	*******/
/******* SWC    :    EXTI       *******/
/******* Version:    1.0        *******/
/**************************************/

/* LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "EXTI_interface.h"
#include "EXTI_private.h"


//--------------------------------------------------------------------------------------------------

/* Global Array of Pointers to ISR functions */
static void (*EXTI_ApfEXTI[3])(void) = {NULL, NULL, NULL};  //static to be non-editable or unseen outside this file  

//----------------------------------------< EXTI Enable Function >-------------------------------------------------

u8 EXTI_u8Enable(u8 Copy_u8EXTIIndex, u8 Copy_u8EdgeType){
	u8  Local_u8ErrorState = STD_TYPES_OK;
	
	switch(Copy_u8EXTIIndex){
		case EXTI_u8_INT0:		// CASE Interrupt 0  
			switch(Copy_u8EdgeType){
					case EXTI_u8_FALLING_EDGE:	     // Falling Edge Mode
						SET_BIT(EXTI_u8_MCUCR_REG, ISC01_BIT);
						CLR_BIT(EXTI_u8_MCUCR_REG, ISC00_BIT);
					break;
					
					case EXTI_u8_RISING_EDGE:	     // Rising Edge Mode 
						SET_BIT(EXTI_u8_MCUCR_REG, ISC00_BIT);
						SET_BIT(EXTI_u8_MCUCR_REG, ISC01_BIT);
					break;
					
					case EXTI_u8_ANY_LOGICAL_CHANGE: // Any Logical Change Mode
						SET_BIT(EXTI_u8_MCUCR_REG, ISC00_BIT);
						CLR_BIT(EXTI_u8_MCUCR_REG, ISC01_BIT);
					break;
					
					case EXTI_u8_LOW_LEVEL: 		 // Low Level Mode
						CLR_BIT(EXTI_u8_MCUCR_REG, ISC00_BIT);
						CLR_BIT(EXTI_u8_MCUCR_REG, ISC01_BIT);
					break;
					
					default:
						Local_u8ErrorState = STD_TYPES_NOK;			
			}// end switch
			
		/*-----------------Enable PIE----------------*/
		SET_BIT(EXTI_u8_GICR_REG, INT0_PIE);
		
		break;	//end CASE Interrupt 0
		
		//---------------------------------------------------------------------------
		case EXTI_u8_INT1:		// CASE Interrupt 1	
			switch(Copy_u8EdgeType){
					case EXTI_u8_FALLING_EDGE:	     // Falling Edge Mode
						SET_BIT(EXTI_u8_MCUCR_REG, ISC11_BIT);
						CLR_BIT(EXTI_u8_MCUCR_REG, ISC10_BIT);
					break;
					
					case EXTI_u8_RISING_EDGE:	     // Rising Edge Mode 
						SET_BIT(EXTI_u8_MCUCR_REG, ISC11_BIT);
						SET_BIT(EXTI_u8_MCUCR_REG, ISC10_BIT);
					break;
					
					case EXTI_u8_ANY_LOGICAL_CHANGE: // Any Logical Change Mode
						SET_BIT(EXTI_u8_MCUCR_REG, ISC10_BIT);
						CLR_BIT(EXTI_u8_MCUCR_REG, ISC11_BIT);
					break;
					
					case EXTI_u8_LOW_LEVEL: 		 // Low Level Mode
						CLR_BIT(EXTI_u8_MCUCR_REG, ISC10_BIT);
						CLR_BIT(EXTI_u8_MCUCR_REG, ISC11_BIT);
					break;
					
					default:
						Local_u8ErrorState = STD_TYPES_NOK;		
			}// end switch
		/*-----------------Enable PIE----------------*/
		SET_BIT(EXTI_u8_GICR_REG, INT1_PIE);
		
		break; //end CASE Interrupt 1
		//-------------------------------------------------------------------------------
		case EXTI_u8_INT2:		// CASE Interrupt 2	
			switch(Copy_u8EdgeType){
					case EXTI_u8_FALLING_EDGE:	     // Falling Edge Mode
						CLR_BIT(EXTI_u8_MCUCR_REG, ISC2_BIT);
					break;
					
					case EXTI_u8_RISING_EDGE:	     // Rising Edge Mode 
						SET_BIT(EXTI_u8_MCUCR_REG, ISC2_BIT);
					break;
					
					default:
						Local_u8ErrorState = STD_TYPES_NOK;			
			}// end switch
		/*-----------------Enable PIE----------------*/
		SET_BIT(EXTI_u8_GICR_REG, INT2_PIE);
		
		break; //end CASE Interrupt 2
		//----------------------------------------------------------------------------
		default: // CASE None of (INT0, INT1, INT2)
			Local_u8ErrorState = STD_TYPES_NOK;
	}// end big switch 
		
	return Local_u8ErrorState;
}// end EXTI_u8Enable Function

//----------------------------------------< EXTI Disable Function >-------------------------------------------------

u8 EXTI_u8Disable(u8 Copy_u8EXTIIndex){
	u8 Local_u8ErrorState = STD_TYPES_OK;
	switch(Copy_u8EXTIIndex){
		case EXTI_u8_INT0:			// CASE Interrupt 0
			CLR_BIT(EXTI_u8_GICR_REG, INT0_PIE);
		break;
		
		case EXTI_u8_INT1:			// CASE Interrupt 1
			CLR_BIT(EXTI_u8_GICR_REG, INT1_PIE);
		break;
		
		case EXTI_u8_INT2:			// CASE Interrupt 2
			CLR_BIT(EXTI_u8_GICR_REG, INT2_PIE);
		break;
		
		default:
			Local_u8ErrorState = STD_TYPES_NOK;
	}// end switch 
	return Local_u8ErrorState;
} // end EXTI_u8Disable Function

//--------------------------------------------< SetCallBack Function >------------------------------------------------

u8 EXTI_u8SetCallBack(void (*Copy_pf)(void), u8 Copy_u8EXTIIndex) 
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if (Copy_u8EXTIIndex <= EXTI_u8_INT2 && Copy_pf != NULL)
	{
		EXTI_ApfEXTI[Copy_u8EXTIIndex] = Copy_pf;
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}	
	return Local_u8ErrorState;	
}// end EXTI_u8SetCallBack Function

//--------------------------------------------< ISR Functions >------------------------------------------------

/* EXTI0 ISR */
void __vector_1(void)		__attribute__((signal));
void __vector_1(void) 
{
	if (EXTI_ApfEXTI[EXTI_u8_INT0] != NULL)
	{
		EXTI_ApfEXTI[EXTI_u8_INT0]();			// Calling function through pointer
	}
}

/* EXTI1 ISR */
void __vector_2(void)		__attribute__((signal));
void __vector_2(void)
{
	if (EXTI_ApfEXTI[EXTI_u8_INT1] != NULL)
	{
		EXTI_ApfEXTI[EXTI_u8_INT1]();
	}	
}

/* EXTI2 ISR */
void __vector_3(void)		__attribute__((signal));
void __vector_3(void)
{
	if (EXTI_ApfEXTI[EXTI_u8_INT2] != NULL)
	{
		EXTI_ApfEXTI[EXTI_u8_INT2]();
	}
}

	

