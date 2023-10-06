/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  26/5/2020   *******/
/******* Update :            	*******/
/******* SWC    :    TIMERS     *******/
/******* Version:     1.0       *******/
/**************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_Interface.h"
#include "TIMERS_Interface.h"
#include "TIMERS_Private.h"
#include "TIMERS_Config.h"


static u8 TIMERS_u8Timer0BusyFlag = 0;
static u16 TIMERS_u16NumOfCompMatch;
static u16 TIMERS_u16NumOfOverFlows;
static void (*TIMERS_pfTimer0Event)(void) = NULL;


//###########################################< Timer_0 Init Func >###########################################

u8 TIMERS_u8Timer0Init()
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	
	//*************************< Setting the mode >**************************
	switch (TIMER0_u8_MODE)
	{
		//---------------------<Normal>-----------------------
		case TIMERS_NORMAL_MODE:
		
			CLR_BIT(TIMERS_u8_TCCR0_REG, 6);
			CLR_BIT(TIMERS_u8_TCCR0_REG, 3);
			
			/* Set the output mode */
			switch (TIMER0_u8_OUTPUT_MODE)
			{
				case TIMERS_NORMAL_OC_DISCNCTD:
				
					CLR_BIT(TIMERS_u8_TCCR0_REG, 4);
					CLR_BIT(TIMERS_u8_TCCR0_REG, 5);
					
				break;
				
				case TIMERS_TOGGLE_OC_COMP_MATCH:
				
					SET_BIT(TIMERS_u8_TCCR0_REG, 4);
					CLR_BIT(TIMERS_u8_TCCR0_REG, 5);
					
				break;
				
				case TIMERS_CLEAR_OC_COMP_MATCH:
				
					CLR_BIT(TIMERS_u8_TCCR0_REG, 4);
					SET_BIT(TIMERS_u8_TCCR0_REG, 5);
					
				break;
				
				case TIMERS_SET_OC_COMP_MATCH;
				
					SET_BIT(TIMERS_u8_TCCR0_REG, 4);
					SET_BIT(TIMERS_u8_TCCR0_REG, 5);
					
				break;
				
				default:	// None of output modes
					Local_u8ErrorState = STD_TYPES_NOK;
				break;	
			}//end  output mode switch 
		break;// Normal mode case 	
		
		//---------------------<CTC>-----------------------
		case TIMERS_CTC_MODE:
			
			SET_BIT(TIMERS_u8_TCCR0_REG, 3);
			CLR_BIT(TIMERS_u8_TCCR0_REG, 6);
			
			/* Set the output mode */
			switch (TIMER0_u8_OUTPUT_MODE)
			{
				case TIMERS_NORMAL_OC_DISCNCTD:
				
					CLR_BIT(TIMERS_u8_TCCR0_REG, 4);
					CLR_BIT(TIMERS_u8_TCCR0_REG, 5);
					
				break;
				
				case TIMERS_TOGGLE_OC_COMP_MATCH:
				
					SET_BIT(TIMERS_u8_TCCR0_REG, 4);
					CLR_BIT(TIMERS_u8_TCCR0_REG, 5);
					
				break;
				
				case TIMERS_CLEAR_OC_COMP_MATCH:
				
					CLR_BIT(TIMERS_u8_TCCR0_REG, 4);
					SET_BIT(TIMERS_u8_TCCR0_REG, 5);
					
				break;
				
				case TIMERS_SET_OC_COMP_MATCH;
				
					SET_BIT(TIMERS_u8_TCCR0_REG, 4);
					SET_BIT(TIMERS_u8_TCCR0_REG, 5);
					
				break;
				
				default:	// None of output modes
					Local_u8ErrorState = STD_TYPES_NOK;
				break;	
			}//end  output mode switch
			
		break; // CTC mode case 
		
		//---------------------<Fast PWM>-----------------------
		case TIMERS_FAST_PWM_MODE:
		
			SET_BIT(TIMERS_u8_TCCR0_REG, 3);
			SET_BIT(TIMERS_u8_TCCR0_REG, 6);
			
			/* Set the output mode */
			switch (TIMER0_u8_OUTPUT_MODE)
			{
				case TIMERS_NORMAL_OC_DISCNCTD:
				
					CLR_BIT(TIMERS_u8_TCCR0_REG, 4);
					CLR_BIT(TIMERS_u8_TCCR0_REG, 5);
					
				break;
				
				case TIMERS_FAST_PWM_OC_NON_INVRTD:
				
					CLR_BIT(TIMERS_u8_TCCR0_REG, 4);
					SET_BIT(TIMERS_u8_TCCR0_REG, 5);
					
				break;
				
				case TIMERS_FAST_PWM_OC_INVRTD:
				
					SET_BIT(TIMERS_u8_TCCR0_REG, 4);
					SET_BIT(TIMERS_u8_TCCR0_REG, 5);
					
				break;
				
				default:	// None of output modes
					Local_u8ErrorState = STD_TYPES_NOK;
				break;	
			}//end  output mode switch	
			
		break; // Fast PWM case
		
		//-------------------<Phase Correct>---------------------
		case TIMERS_PHASE_CORRECT_MODE:
		
			CLR_BIT(TIMERS_u8_TCCR0_REG, 3);
			SET_BIT(TIMERS_u8_TCCR0_REG, 6);

			/* Set the output mode */
			switch (TIMER0_u8_OUTPUT_MODE)
			{
				case TIMERS_NORMAL_OC_DISCNCTD:
				
					CLR_BIT(TIMERS_u8_TCCR0_REG, 4);
					CLR_BIT(TIMERS_u8_TCCR0_REG, 5);
					
				break;
				
				case TIMERS_PhCORCT_OC_NON_INVRTD:
				
					CLR_BIT(TIMERS_u8_TCCR0_REG, 4);
					SET_BIT(TIMERS_u8_TCCR0_REG, 5);
					
				break;
				
				case TIMERS_PhCORCT_OC_INVRTD:
				
					SET_BIT(TIMERS_u8_TCCR0_REG, 4);
					SET_BIT(TIMERS_u8_TCCR0_REG, 5);
					
				break;
				
				default:	// None of output modes 
					Local_u8ErrorState = STD_TYPES_NOK;
				break;	
			}//end  output mode switch	
		
		break; // Phase Correct case
		
		default:	//None of Timers Modes 
			Local_u8ErrorState = STD_TYPES_NOK;
		break;
	}//end switch 

	return Local_u8ErrorState;
}// end Timer_0 Init


//###########################################< Timer_0 Set Mode Func >###########################################

u8 TIMERS_u8Timer0SetMode(u8 Copy_u8TimerMode, u8 Copy_u8OutputMode)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	
	switch (Copy_u8TimerMode)
	{
		//---------------------<Normal>-----------------------
		case TIMERS_NORMAL_MODE:
			
			switch (Copy_u8OutputMode)
			{
				case TIMERS_NORMAL_OC_DISCNCTD:
					
					/* Stop Timer */
					TIMERS_voidTimer0Disable();
					
					/* Enable Timer Mode */
					CLR_BIT(TIMERS_u8_TCCR0_REG, 6);
					CLR_BIT(TIMERS_u8_TCCR0_REG, 3);
			
					/* Enable Output Mode */
					CLR_BIT(TIMERS_u8_TCCR0_REG, 4);
					CLR_BIT(TIMERS_u8_TCCR0_REG, 5);
			
				break;
				
				case TIMERS_TOGGLE_OC_COMP_MATCH:
				
					/* Stop Timer */
					TIMERS_voidTimer0Disable();
					
					/* Enable Timer Mode */
					CLR_BIT(TIMERS_u8_TCCR0_REG, 6);
					CLR_BIT(TIMERS_u8_TCCR0_REG, 3);
				
					/* Enable Output Mode */
					SET_BIT(TIMERS_u8_TCCR0_REG, 4);
					CLR_BIT(TIMERS_u8_TCCR0_REG, 5);
					
				break;
				
				case TIMERS_CLEAR_OC_COMP_MATCH:
					
					/* Stop Timer */
					TIMERS_voidTimer0Disable();
					
					/* Enable Timer Mode */
					CLR_BIT(TIMERS_u8_TCCR0_REG, 6);
					CLR_BIT(TIMERS_u8_TCCR0_REG, 3);
				
					/* Enable Output Mode */
					CLR_BIT(TIMERS_u8_TCCR0_REG, 4);
					SET_BIT(TIMERS_u8_TCCR0_REG, 5);
					
				break;
				
				case TIMERS_SET_OC_COMP_MATCH;
					
					/* Stop Timer */
					TIMERS_voidTimer0Disable();
					
					/* Enable Timer Mode */
					CLR_BIT(TIMERS_u8_TCCR0_REG, 6);
					CLR_BIT(TIMERS_u8_TCCR0_REG, 3);	
				
					/* Enable Output Mode */
					SET_BIT(TIMERS_u8_TCCR0_REG, 4);
					SET_BIT(TIMERS_u8_TCCR0_REG, 5);
					
				break;
				
				default:	// None of output modes
					Local_u8ErrorState = STD_TYPES_NOK;
				break;	
			}//end  output mode switch 
		break;// Normal mode case 	
		
		//---------------------<CTC>-----------------------
		case TIMERS_CTC_MODE:
			
			
			
			/* Set the output mode */
			switch (Copy_u8OutputMode)
			{
				case TIMERS_NORMAL_OC_DISCNCTD:
					
					/* Stop Timer */
					TIMERS_voidTimer0Disable();
	
					/* Enable Timer Mode */
					SET_BIT(TIMERS_u8_TCCR0_REG, 3);
					CLR_BIT(TIMERS_u8_TCCR0_REG, 6);	
				
					/* Enable Output Mode */
					CLR_BIT(TIMERS_u8_TCCR0_REG, 4);
					CLR_BIT(TIMERS_u8_TCCR0_REG, 5);
					
				break;
				
				case TIMERS_TOGGLE_OC_COMP_MATCH:
					
					/* Stop Timer */
					TIMERS_voidTimer0Disable();
	
					/* Enable Timer Mode */
					SET_BIT(TIMERS_u8_TCCR0_REG, 3);
					CLR_BIT(TIMERS_u8_TCCR0_REG, 6);
				
					/* Enable Output Mode */
					SET_BIT(TIMERS_u8_TCCR0_REG, 4);
					CLR_BIT(TIMERS_u8_TCCR0_REG, 5);
					
				break;
				
				case TIMERS_CLEAR_OC_COMP_MATCH:
				
					/* Stop Timer */
					TIMERS_voidTimer0Disable();
	
					/* Enable Timer Mode */
					SET_BIT(TIMERS_u8_TCCR0_REG, 3);
					CLR_BIT(TIMERS_u8_TCCR0_REG, 6);	
				
					/* Enable Output Mode */
					CLR_BIT(TIMERS_u8_TCCR0_REG, 4);
					SET_BIT(TIMERS_u8_TCCR0_REG, 5);
					
				break;
				
				case TIMERS_SET_OC_COMP_MATCH;
					
					/* Stop Timer */
					TIMERS_voidTimer0Disable();
	
					/* Enable Timer Mode */
					SET_BIT(TIMERS_u8_TCCR0_REG, 3);
					CLR_BIT(TIMERS_u8_TCCR0_REG, 6);	
				
					/* Enable Output Mode */
					SET_BIT(TIMERS_u8_TCCR0_REG, 4);
					SET_BIT(TIMERS_u8_TCCR0_REG, 5);
					
				break;
				
				default:	// None of output modes
					Local_u8ErrorState = STD_TYPES_NOK;
				break;	
			}//end  output mode switch
			
		break; // CTC mode case 
		
		//---------------------<Fast PWM>-----------------------
		case TIMERS_FAST_PWM_MODE:
		
			
			
			/* Set the output mode */
			switch (Copy_u8OutputMode)
			{
				case TIMERS_NORMAL_OC_DISCNCTD:
					
					/* Stop Timer */
					TIMERS_voidTimer0Disable();
	
					/* Enable Timer Mode */
					SET_BIT(TIMERS_u8_TCCR0_REG, 3);
					SET_BIT(TIMERS_u8_TCCR0_REG, 6);	
				
					/* Enable Output Mode */
					CLR_BIT(TIMERS_u8_TCCR0_REG, 4);
					CLR_BIT(TIMERS_u8_TCCR0_REG, 5);
					
				break;
				
				case TIMERS_FAST_PWM_OC_NON_INVRTD:
					
					/* Stop Timer */
					TIMERS_voidTimer0Disable();
	
					/* Enable Timer Mode */
					SET_BIT(TIMERS_u8_TCCR0_REG, 3);
					SET_BIT(TIMERS_u8_TCCR0_REG, 6);	
				
					/* Enable Output Mode */
					CLR_BIT(TIMERS_u8_TCCR0_REG, 4);
					SET_BIT(TIMERS_u8_TCCR0_REG, 5);
					
				break;
				
				case TIMERS_FAST_PWM_OC_INVRTD:
					
					/* Stop Timer */
					TIMERS_voidTimer0Disable();
	
					/* Enable Timer Mode */
					SET_BIT(TIMERS_u8_TCCR0_REG, 3);
					SET_BIT(TIMERS_u8_TCCR0_REG, 6);	
				
					/* Enable Output Mode */
					SET_BIT(TIMERS_u8_TCCR0_REG, 4);
					SET_BIT(TIMERS_u8_TCCR0_REG, 5);
					
				break;
				
				default:	// None of output modes
					Local_u8ErrorState = STD_TYPES_NOK;
				break;	
			}//end  output mode switch	
			
		break; // Fast PWM case
		
		//-------------------<Phase Correct>---------------------
		case TIMERS_PHASE_CORRECT_MODE:
		
			

			/* Set the output mode */
			switch (Copy_u8OutputMode)
			{
				case TIMERS_NORMAL_OC_DISCNCTD:
					
					/* Stop Timer */
					TIMERS_voidTimer0Disable();
	
					/* Enable Timer Mode */
					CLR_BIT(TIMERS_u8_TCCR0_REG, 3);
					SET_BIT(TIMERS_u8_TCCR0_REG, 6);	
				
					/* Enable Output Mode */
					CLR_BIT(TIMERS_u8_TCCR0_REG, 4);
					CLR_BIT(TIMERS_u8_TCCR0_REG, 5);
	
				break;
				
				case TIMERS_PhCORCT_OC_NON_INVRTD:
					
					/* Stop Timer */
					TIMERS_voidTimer0Disable();
	
					/* Enable Timer Mode */
					CLR_BIT(TIMERS_u8_TCCR0_REG, 3);
					SET_BIT(TIMERS_u8_TCCR0_REG, 6);	
				
					/* Enable Output Mode */
					CLR_BIT(TIMERS_u8_TCCR0_REG, 4);
					SET_BIT(TIMERS_u8_TCCR0_REG, 5);
					
				break;
				
				case TIMERS_PhCORCT_OC_INVRTD:
					
					/* Stop Timer */
					TIMERS_voidTimer0Disable();
	
					/* Enable Timer Mode */
					CLR_BIT(TIMERS_u8_TCCR0_REG, 3);
					SET_BIT(TIMERS_u8_TCCR0_REG, 6);	
				
					/* Enable Output Mode */
					SET_BIT(TIMERS_u8_TCCR0_REG, 4);
					SET_BIT(TIMERS_u8_TCCR0_REG, 5);
					
				break;
				
				default:	// None of output modes 
					Local_u8ErrorState = STD_TYPES_NOK;
				break;	
			}//end  output mode switch	
		
		break; // Phase Correct case
		
		default:	//None of Timers Modes 
			Local_u8ErrorState = STD_TYPES_NOK;
		break;
	}//end switch 

	return Local_u8ErrorState;
}


//###########################################< Timer_0 Normal Mode Func >###########################################

u8 TIMERS_u8Timer0NormalMode(u16 Copy_u16EventTime, u8 Copy_u8ClkMode, void (*Copy_pfEvent)(void))
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	f32 Local_f32TOV;					// Time of overflow
	f32 Local_f32Fractional;			// the fractional points
	f32 Local_f32NumOfOverFlows;
	u8 Local_u8FractionalCounts;		// Number of counts that represents the fractional points
	u8 Local_u8PreloadVal = 0;
	
	if (Copy_pfEvent != NULL && TIMERS_u8Timer0BusyFlag == 0)
	{	
		/* Set the Busy Flag */
		TIMERS_u8Timer0BusyFlag = 1;
		
		switch (Copy_u8ClkMode)
		{
			case TIMERS_CLK_NO_PRSCLR:
			
				Local_f32TOV = ((1.0*256.0)/F_u32_CPU)*1000000.0;		// calculating Tov with microsecond
				
				if (Copy_u16EventTime >= Local_f32TOV)
				{	
					/* Calculating the preload val */
					Local_f32NumOfOverFlows = (f32) ((f32)Copy_u16EventTime / Local_f32TOV);
					TIMERS_u16NumOfOverFlows = (u16) Local_f32NumOfOverFlows;			// Num of Overflows without fractional 
					Local_f32Fractional = (f32)(Local_f32NumOfOverFlows - (f32)TIMERS_u16NumOfOverFlows);
					Local_u8FractionalCounts = (u8)(Local_f32Fractional * 256.0);
				
					if (Local_u8FractionalCounts > 0)
					{
						TIMERS_u16NumOfOverFlows += 1; 							//plus one for the fractional counts
						Local_u8PreloadVal = 256 - Local_u8FractionalCounts;
						TIMERS_u8_TCNT0_REG = Local_u8PreloadVal; 				// Assign preload val to the counter register
					}
				
					/* Passing the Add to the global pointer */
					TIMERS_pfTimer0Event = Copy_pfEvent;
					
					/* Set OC0 pin direction */
					DIO_u8SetPinDirection(DIO_u8_PORTB, DIO_u8_PIN3, DIO_u8_OUTPUT);
				
					/* Enable Timer Overflow Interrupt */
					SET_BIT(TIMERS_u8_TIMSK_REG,0);
				
					/* Set the Clk to start the Timer */
					TIMERS_voidTimer0Enable(TIMERS_CLK_NO_PRSCLR);
					
				}// end if 	
				else 
				{
					/* Update the Error state */
					Local_u8ErrorState = STD_TYPES_NOK;	
					
					/* Clear the Busy Flag */
					TIMERS_u8Timer0BusyFlag = 0;
				}	
		
			break;
			//---------------------------------------------------------------------
			case TIMERS_CLK_PRSCLR_8:
			
				Local_f32TOV = ((8.0*256.0)/F_u32_CPU)*1000000.0;		// calculating Tov
				
				if (Copy_u16EventTime >= Local_f32TOV)
				{	
					/* Calculating the preload val */
					Local_f32NumOfOverFlows = (f32)Copy_u16EventTime / Local_f32TOV;
					TIMERS_u16NumOfOverFlows = (u16) Local_f32NumOfOverFlows;			// Num of Overflows without fractional
					Local_f32Fractional = (f32)(Local_f32NumOfOverFlows - (f32)TIMERS_u16NumOfOverFlows);
					Local_u8FractionalCounts = (u8)(Local_f32Fractional * 256.0);
				
					if (Local_u8FractionalCounts > 0)
					{
						TIMERS_u16NumOfOverFlows += 1; 							//plus one for the fractional counts
						Local_u8PreloadVal = 256 - Local_u8FractionalCounts;
						TIMERS_u8_TCNT0_REG = Local_u8PreloadVal; 				// Assign preload val to the counter register
					}
				
					/* Passing the Add to the global pointer */
					TIMERS_pfTimer0Event = Copy_pfEvent;
				
					/* Set OC0 pin direction */
					DIO_u8SetPinDirection(DIO_u8_PORTB, DIO_u8_PIN3, DIO_u8_OUTPUT);
				
					/* Enable Timer Overflow Interrupt */
					SET_BIT(TIMERS_u8_TIMSK_REG,0);
			
					/* Set the Clk to start the Timer */
					TIMERS_voidTimer0Enable(TIMERS_CLK_PRSCLR_8);
					
				} // end if 
				else 
				{
					/* Update the Error state */
					Local_u8ErrorState = STD_TYPES_NOK;	
					
					/* Clear the Busy Flag */
					TIMERS_u8Timer0BusyFlag = 0;
				}	
				
			break;
			//------------------------------------------------------------------------------
			case TIMERS_CLK_PRSCLR_64:
			
				Local_f32TOV = ((64.0*256.0)/F_u32_CPU)*1000000.0;				// calculating Tov
				
				if (Copy_u16EventTime >= Local_f32TOV)
				{	
					/* Calculating the preload val */
					Local_f32NumOfOverFlows = (f32)Copy_u16EventTime / Local_f32TOV;
					TIMERS_u16NumOfOverFlows = (u16) Local_f32NumOfOverFlows;			// Num of Overflows without fractional
					Local_f32Fractional = (f32)(Local_f32NumOfOverFlows - (f32)TIMERS_u16NumOfOverFlows);
					Local_u8FractionalCounts = (u8)(Local_f32Fractional * 256.0);
				
					if (Local_u8FractionalCounts > 0)
					{
						TIMERS_u16NumOfOverFlows += 1; 							//plus one for the fractional counts
						Local_u8PreloadVal = 256 - Local_u8FractionalCounts;
						TIMERS_u8_TCNT0_REG = Local_u8PreloadVal; 				// Assign preload val to the counter register
					}
				
					/* Passing the Add to the global pointer */
					TIMERS_pfTimer0Event = Copy_pfEvent;
					
					/* Set OC0 pin direction */
					DIO_u8SetPinDirection(DIO_u8_PORTB, DIO_u8_PIN3, DIO_u8_OUTPUT);
				
					/* Enable Timer Overflow Interrupt */
					SET_BIT(TIMERS_u8_TIMSK_REG,0);
				
					/* Set the Clk to start the Timer */
					TIMERS_voidTimer0Enable(TIMERS_CLK_PRSCLR_64);
					
				}// end if 
				else 
				{
					/* Update the Error state */
					Local_u8ErrorState = STD_TYPES_NOK;	
					
					/* Clear the Busy Flag */
					TIMERS_u8Timer0BusyFlag = 0;
				}	
		
			break;
			//-----------------------------------------------------------------------------------
			case TIMERS_CLK_PRSCLR_256:
			
				Local_f32TOV = ((256.0*256.0)/F_u32_CPU)*1000000.0;				// calculating Tov
				
				if (Copy_u16EventTime >= Local_f32TOV)
				{	
					/* Calculating the preload val */
					Local_f32NumOfOverFlows = (f32)Copy_u16EventTime / Local_f32TOV;
					TIMERS_u16NumOfOverFlows = (u16) Local_f32NumOfOverFlows;			// Num of Overflows without fractional
					Local_f32Fractional = (f32)(Local_f32NumOfOverFlows - (f32)TIMERS_u16NumOfOverFlows);
					Local_u8FractionalCounts = (u8)(Local_f32Fractional * 256.0);
				
					if (Local_u8FractionalCounts > 0)
					{
						TIMERS_u16NumOfOverFlows += 1; 							//plus one for the fractional counts
						Local_u8PreloadVal = 256 - Local_u8FractionalCounts;
						TIMERS_u8_TCNT0_REG = Local_u8PreloadVal; 				// Assign preload val to the counter register
					}
				
					/* Passing the Add to the global pointer */
					TIMERS_pfTimer0Event = Copy_pfEvent;
					
					/* Set OC0 pin direction */
					DIO_u8SetPinDirection(DIO_u8_PORTB, DIO_u8_PIN3, DIO_u8_OUTPUT);
				
					/* Enable Timer Overflow Interrupt */
					SET_BIT(TIMERS_u8_TIMSK_REG,0);
				
					/* Set the Clk to start the Timer */
					TIMERS_voidTimer0Enable(TIMERS_CLK_PRSCLR_256);
				
				}//end if
				else 
				{
					/* Update the Error state */
					Local_u8ErrorState = STD_TYPES_NOK;	
					
					/* Clear the Busy Flag */
					TIMERS_u8Timer0BusyFlag = 0;
				}
				
			break;
			//----------------------------------------------------------------------------------
			case TIMERS_CLK_PRSCLR_1024:
				
				Local_f32TOV = ((1024.0*256.0)/F_u32_CPU)*1000000.0;			// calculating Tov
				
				if (Copy_u16EventTime >= Local_f32TOV)
				{	
					/* Calculating the preload val */
					Local_f32NumOfOverFlows = (f32)Copy_u16EventTime / Local_f32TOV;
					TIMERS_u16NumOfOverFlows = (u16) Local_f32NumOfOverFlows;			// Num of Overflows without fractional
					Local_f32Fractional = (f32)(Local_f32NumOfOverFlows - (f32)TIMERS_u16NumOfOverFlows);
					Local_u8FractionalCounts = (u8)(Local_f32Fractional * 256.0);
				
					if (Local_u8FractionalCounts > 0)
					{
						TIMERS_u16NumOfOverFlows += 1; 							//plus one for the fractional counts
						Local_u8PreloadVal = 256 - Local_u8FractionalCounts;
						TIMERS_u8_TCNT0_REG = Local_u8PreloadVal; 				// Assign preload val to the counter register
					}
				
					/* Passing the Add to the global pointer */
					TIMERS_pfTimer0Event = Copy_pfEvent;
					
					/* Set OC0 pin direction */
					DIO_u8SetPinDirection(DIO_u8_PORTB, DIO_u8_PIN3, DIO_u8_OUTPUT);
				
					/* Enable Timer Overflow Interrupt */
					SET_BIT(TIMERS_u8_TIMSK_REG,0);
				
					/* Set the Clk to start the Timer */
					TIMERS_voidTimer0Enable(TIMERS_CLK_PRSCLR_1024);
				
				}// end if 
				else 
				{
					/* Update the Error state */
					Local_u8ErrorState = STD_TYPES_NOK;	
					
					/* Clear the Busy Flag */
					TIMERS_u8Timer0BusyFlag = 0;
				}
				
			break;
		
		/*	case TIMERS_EXT_CLK_Tpin_Fall_EDGE:
				
				TIMERS_voidTimer0Enable(TIMERS_EXT_CLK_Tpin_Fall_EDGE);
		
			break;
		
			case TIMERS_EXT_CLK_Tpin_RIS_EDGE:
				
				TIMERS_voidTimer0Enable(TIMERS_EXT_CLK_Tpin_RIS_EDGE);
			
			break;
		*/
			default:	// None of Clk modes 
				
				/* Udate the Error state */
				Local_u8ErrorState = STD_TYPES_NOK;
				
				/* Clear the Busy Flag */
				TIMERS_u8Timer0BusyFlag = 0;
				
			break;		
		}//end switch
	}//end if 	
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}	
	
	return Local_u8ErrorState;
}// end Normal Mode function 


//###########################################< Timer_0 CTC Mode Func >###########################################

u8 TIMERS_u8Timer0CTCMode(u16 Copy_u16EventTime, u8 Copy_u8OCRval, u8 Copy_u8ClkMode, void (*Copy_pfEvent)(void))
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	u16 Local_u16TOV;
	
	if (Copy_pfEvent != NULL && TIMERS_u8Timer0BusyFlag ==0)
	{
		/* Set the Busy falg */
		TIMERS_u8Timer0BusyFlag = 1;
		
		switch (Copy_u8ClkMode)
		{
			case TIMERS_CLK_NO_PRSCLR:
				
				Local_u16TOV = ((1*Copy_u8OCRval)/F_u32_CPU)*1000000;	 		// TOV in microsecond
				TIMERS_u16NumOfCompMatch = Copy_u16EventTime / Local_u16TOV;
				
				/* Assign OCR value to the Rgister */
				TIMERS_u8_OCR0_REG = Copy_u8OCRval;
				
				/* Passing Address to the global pointer */
				TIMERS_pfTimer0Event = Copy_pfEvent;
				
				/* Enable Timer Compare Match Interrupt */
				SET_BIT(TIMERS_u8_TIMSK_REG,1);
				
				/* Set the CLK to start the timer */
				TIMERS_voidTimer0Enable(TIMERS_CLK_NO_PRSCLR);
				
			break;
			//---------------------------------------------------------------
			case TIMERS_CLK_PRSCLR_8:
			
				Local_u16TOV = ((8*Copy_u8OCRval)/F_u32_CPU)*1000000;	 		// TOV in microsecond
				TIMERS_u16NumOfCompMatch = Copy_u16EventTime / Local_u16TOV;
				
				/* Assign OCR value to the Rgister */
				TIMERS_u8_OCR0_REG = Copy_u8OCRval;
				
				/* Passing Address to the global pointer */
				TIMERS_pfTimer0Event = Copy_pfEvent;
				
				/* Enable Timer Compare Match Interrupt */
				SET_BIT(TIMERS_u8_TIMSK_REG,1);
				
				/* Set the CLK to start the timer */
				TIMERS_voidTimer0Enable(TIMERS_CLK_PRSCLR_8);
				
			break;
			//---------------------------------------------------------------
			case TIMERS_CLK_PRSCLR_64:
				
				Local_u16TOV = ((64*Copy_u8OCRval)/F_u32_CPU)*1000000;	 		// TOV in microsecond
				TIMERS_u16NumOfCompMatch = Copy_u16EventTime / Local_u16TOV;
				
				/* Assign OCR value to the Rgister */
				TIMERS_u8_OCR0_REG = Copy_u8OCRval;
				
				/* Passing Address to the global pointer */
				TIMERS_pfTimer0Event = Copy_pfEvent;
				
				/* Enable Timer Compare Match Interrupt */
				SET_BIT(TIMERS_u8_TIMSK_REG,1);
				
				/* Set the CLK to start the timer */
				TIMERS_voidTimer0Enable(TIMERS_CLK_PRSCLR_64);
				
			break;
			//---------------------------------------------------------------
			case TIMERS_CLK_PRSCLR_256:
			
				Local_u16TOV = ((256*Copy_u8OCRval)/F_u32_CPU)*1000000;	 		// TOV in microsecond
				TIMERS_u16NumOfCompMatch = Copy_u16EventTime / Local_u16TOV;
				
				/* Assign OCR value to the Rgister */
				TIMERS_u8_OCR0_REG = Copy_u8OCRval;
				
				/* Passing Address to the global pointer */
				TIMERS_pfTimer0Event = Copy_pfEvent;
				
				/* Enable Timer Compare Match Interrupt */
				SET_BIT(TIMERS_u8_TIMSK_REG,1);
				
				/* Set the CLK to start the timer */
				TIMERS_voidTimer0Enable(TIMERS_CLK_PRSCLR_256);
				
			break;
			//---------------------------------------------------------------
			case TIMERS_CLK_PRSCLR_1024:
			
				Local_u16TOV = ((1024*Copy_u8OCRval)/F_u32_CPU)*1000000;	 		// TOV in microsecond
				TIMERS_u16NumOfCompMatch = Copy_u16EventTime / Local_u16TOV;
				
				/* Assign OCR value to the Rgister */
				TIMERS_u8_OCR0_REG = Copy_u8OCRval;
				
				/* Passing Address to the global pointer */
				TIMERS_pfTimer0Event = Copy_pfEvent;
				
				/* Enable Timer Compare Match Interrupt */
				SET_BIT(TIMERS_u8_TIMSK_REG,1);
				
				/* Set the CLK to start the timer */
				TIMERS_voidTimer0Enable(TIMERS_CLK_PRSCLR_1024);
				
			break;
			//---------------------------------------------------------------
		/*	case TIMERS_EXT_CLK_Tpin_Fall_EDGE:
				
				TIMERS_voidTimer0Enable(TIMERS_EXT_CLK_Tpin_Fall_EDGE);
			
			break;
			//---------------------------------------------------------------
			case TIMERS_EXT_CLK_Tpin_RIS_EDGE:
				
				TIMERS_voidTimer0Enable(TIMERS_EXT_CLK_Tpin_RIS_EDGE);
				
			break;
		*/
			default:	// None of CLK modes 
				
				/* Update the Error state */
				Local_u8ErrorState = STD_TYPES_NOK;
				
				/* Clear the Busy Flag */
				TIMERS_u8Timer0BusyFlag = 0;
			
			break;
			
		}// end switch
	}// end if 
	else 
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}	
	
	return Local_u8ErrorState
}// end CTC Mode function


//###########################################< Timer_0 Disable Func >###########################################

void TIMERS_voidTimer0Disable()
{
	/* Stop CLK */
	CLR_BIT(TIMERS_u8_TCCR0_REG, 0);
	CLR_BIT(TIMERS_u8_TCCR0_REG, 1);
	CLR_BIT(TIMERS_u8_TCCR0_REG, 2);
	
	/* Clearing Registers */
	TIMERS_u8_TCNT0_REG = 0x00;
	TIMERS_u8_OCR0_REG = 0x00;
	
	/* Disable Interrupts */
	CLR_BIT(TIMERS_u8_TIMSK_REG,0);
	CLR_BIT(TIMERS_u8_TIMSK_REG,1);

	/* Clearing Busy Flag */
	TIMERS_u8Timer0BusyFlag = 0;
}


//###########################################< Timer_0 Enable Func >###########################################

void TIMERS_voidTimer0Enable(u8 Copy_u8ClkMode)
{
	switch (Copy_u8ClkMode)
	{
		case TIMERS_CLK_NO_PRSCLR:
		
			SET_BIT(TIMERS_u8_TCCR0_REG, 0);
			CLR_BIT(TIMERS_u8_TCCR0_REG, 1);
			CLR_BIT(TIMERS_u8_TCCR0_REG, 2);
		
		break;
		//--------------------------
		case TIMERS_CLK_PRSCLR_8:
		
			CLR_BIT(TIMERS_u8_TCCR0_REG, 0);
			SET_BIT(TIMERS_u8_TCCR0_REG, 1);
			CLR_BIT(TIMERS_u8_TCCR0_REG, 2);
		
		break;
		//--------------------------
		case TIMERS_CLK_PRSCLR_64:
		
			SET_BIT(TIMERS_u8_TCCR0_REG, 0);
			SET_BIT(TIMERS_u8_TCCR0_REG, 1);
			CLR_BIT(TIMERS_u8_TCCR0_REG, 2);
		
		break;
		//--------------------------
		case TIMERS_CLK_PRSCLR_256:
		
			CLR_BIT(TIMERS_u8_TCCR0_REG, 0);
			CLR_BIT(TIMERS_u8_TCCR0_REG, 1);
			SET_BIT(TIMERS_u8_TCCR0_REG, 2);
		
		break;
		//--------------------------
		case TIMERS_CLK_PRSCLR_1024:
		
			SET_BIT(TIMERS_u8_TCCR0_REG, 0);
			CLR_BIT(TIMERS_u8_TCCR0_REG, 1);
			SET_BIT(TIMERS_u8_TCCR0_REG, 2);
		
		break;
		//--------------------------
		case TIMERS_EXT_CLK_Tpin_Fall_EDGE:
		
			CLR_BIT(TIMERS_u8_TCCR0_REG, 0);
			SET_BIT(TIMERS_u8_TCCR0_REG, 1);
			SET_BIT(TIMERS_u8_TCCR0_REG, 2);
		
		break;
		//--------------------------
		case TIMERS_EXT_CLK_Tpin_RIS_EDGE:
		
			SET_BIT(TIMERS_u8_TCCR0_REG, 0);
			SET_BIT(TIMERS_u8_TCCR0_REG, 1);
			SET_BIT(TIMERS_u8_TCCR0_REG, 2);
		
		break;
		//--------------------------
		default:
		
			/* Do Nothing */
		
		break;
		
	}//end switch 
	
}// end Timer0 Enable Function 


//###########################################< Timer_0 Fast PWM >###########################################

u8 TIMERS_u8Timer0FastPWM(u8 Copy_u8DutyCycle, u8 Copy_u8ClkMode)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	
	/* Check Busy Flag */
	if (TIMERS_u8Timer0BusyFlag == 0)
	{	
		f32 Local_f32TonValue = 0.0;
		u8 Local_u8TonValue = 0;
		f32 Local_f32Fraction = 0.0;
		//---------------------------------
		
		/* Set Busy Flag */
		TIMERS_u8Timer0BusyFlag = 1;
		
		/* Calculation */
		Local_f32TonValue = (256.0 * (f32)Copy_u8DutyCycle)/100.0;
		Local_u8TonValue = (u8) Local_f32TonValue;
		Local_f32Fraction = local_f32TonValue - Local_u8TonValue;
	
		if (Local_f32Fraction >= 0.445)
		{
			Local_u8TonValue +=	1;
		}	


		/* Set OC0 pin direction */
		DIO_u8SetPinDirection(DIO_u8_PORTB, DIO_u8_PIN3, DIO_u8_OUTPUT);
		

		/* Check the output mode */
		if ((GET_BIT(TIMERS_u8_TCCR0_REG, 4)==0) && (GET_BIT(TIMERS_u8_TCCR0_REG, 5)==1))		// Non-Inverted Mode
		{	
		
			TIMERS_u8_OCR0_REG = Local_u8TonValue - 1 ;			// OCR = Num of Ton Counts
			
			/* Set Prescaler to start timer */
			TIMERS_voidTimer0Enable(Copy_u8ClkMode);

		}	
		//-----------------------------------------------
		else if ((GET_BIT(TIMERS_u8_TCCR0_REG, 4)==1) && (GET_BIT(TIMERS_u8_TCCR0_REG, 5)==1))		// Inverted Mode
		{
			
			TIMERS_u8_OCR0_REG = 256 - (Local_u8TonValue - 1);	// OCR = Num of Toff Counts
			
			/* Set Prescaler to start timer */
			TIMERS_voidTimer0Enable(Copy_u8ClkMode);
		
		}
		//-----------------------------------------------
		else 
		{
			Local_u8ErrorState = STD_TYPES_NOK;
			TIMERS_u8Timer0BusyFlag = 0;
		}	
	}// end if 
	
	else // Busy Flag = 1
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}	
	
	return Local_u8ErrorState;
	
}// end Fast PWM Function 


//###########################################< Timer_0 Phase Correct >###########################################

u8 TIMERS_u8Timer0PhaseCorrect(u8 Copy_u8DutyCycle, u8 Copy_u8ClkMode)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	
	/* Check Busy Flag */
	if (TIMERS_u8Timer0BusyFlag == 0)
	{	
		f32 Local_f32TonValue = 0.0;
		u8 Local_u8TonValue = 0;
		f32 Local_f32Fraction = 0.0;
		//-----------------------------
		
		/* Set Busy Flag */
		TIMERS_u8Timer0BusyFlag = 1;
		
		/* Calculation */
		Local_f32TonValue = (510.0 * (f32)Copy_u8DutyCycle)/100.0;
		Local_u8TonValue = (u8) Local_f32TonValue;
		Local_f32Fraction = local_f32TonValue - Local_u8TonValue;
				
		if (Local_f32Fraction >= 0.445)
		{
			Local_u8TonValue +=	1;
		}
		
		
		/* Set OC0 pin direction */
		DIO_u8SetPinDirection(DIO_u8_PORTB, DIO_u8_PIN3, DIO_u8_OUTPUT);
		
		
		/* Check the output mode */
		if ((GET_BIT(TIMERS_u8_TCCR0_REG, 4)==0) && (GET_BIT(TIMERS_u8_TCCR0_REG, 5)==1))		// Non-Inverted Mode
		{	
			
			TIMERS_u8_OCR0_REG = Local_u8TonValue /2 ;					// OCR = Num of Ton Counts /2 
			
			/* Set Prescaler to start timer */
			TIMERS_voidTimer0Enable(Copy_u8ClkMode);

		}	
		//-----------------------------------------------
		else if ((GET_BIT(TIMERS_u8_TCCR0_REG, 4)==1) && (GET_BIT(TIMERS_u8_TCCR0_REG, 5)==1))		// Inverted Mode
		{		
			
			TIMERS_u8_OCR0_REG = (510 - Local_u8TonValue ) / 2;			// OCR = Num of Toff Counts /2
			
			/* Set Prescaler to start timer */
			TIMERS_voidTimer0Enable(Copy_u8ClkMode);
		
		}
		//-----------------------------------------------
		else 
		{
			Local_u8ErrorState = STD_TYPES_NOK;
			TIMERS_u8Timer0BusyFlag = 0;
		}
	}// end if

	else // Busy Flag = 1
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}	
	return Local_u8ErrorState;
}//end Phase Correct Function 


//###########################################< Timer_0 ISR_Normal Mode >###########################################

Void __vector_11(Void) __attribute__((signal));

Void __vector_11(Void)
{
	static u16 Local_u16CounterOVF = 0;
	
	Local_u16CounterOVF++;
	
	if (Local_u16CounterOVF == TIMERS_u16NumOfOverFlows)
	{
		// Resetting the counter 
		Local_u16CounterOVF = 0;
		
		// Excuting the required event
		TIMERS_pfTimer0Event();			 
		
		// Stop the timer 
		TIMERS_voidTimer0Disable();
		
	}	
}// end Normal mode ISR


//###########################################< Timer_0 ISR_CTC Mode >###########################################

Void __vector_10(Void) __attribute__((signal));

Void __vector_10(Void)
{
	static u16 Local_u16CounterCTC = 0;
	
	Local_u16CounterCTC++;
	
	if (Local_u16CounterCTC == TIMERS_u16NumOfCompMatch)
	{
		// Resetting the counter 
		Local_u16CounterCTC = 0;
		
	    // Excuting the required event
		TIMERS_pfTimer0Event();
	
		// Stop the timer
		TIMERS_voidTimer0Disable();
		
	}	
	
}//end CTC Mode ISR




