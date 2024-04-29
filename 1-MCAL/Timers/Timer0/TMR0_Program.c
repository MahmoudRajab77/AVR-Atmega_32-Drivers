/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  26/5/2020    *******/
/******* Update :            	*******/
/******* SWC    :     TMR0      *******/
/******* Version:     1.0       *******/
/**************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_Interface.h"
#include "TMR0_Interface.h"
#include "TMR0_Private.h"
#include "TMR0_Config.h"


static u8 TMR0_u8BusyFlag = 0;
static u16 TMR0_u16NumOfCompMatch;
static u16 TMR0_u16NumOfOverFlows;
static void (*TMR0_pfEvent)(void) = NULL;
static u8 TMR0_u8PreloadVal = 0;


//###########################################< Init Func >###########################################

void TMR0_voidInit()
{
	
	/* Set OC0 pin direction to output*/
	DIO_u8SetPinDirection(DIO_u8_PORTB, DIO_u8_PIN3, DIO_u8_OUTPUT);
	
	//*************************< Setting the mode >**************************
	switch (TMR0_u8_MODE)
	{
		//---------------------<Normal>-----------------------
		case TMR0_NORMAL_MODE:
		
			CLR_BIT(TMR0_u8_TCCR0_REG, 6);
			CLR_BIT(TMR0_u8_TCCR0_REG, 3);
			
			/* Set the output mode */
			switch (TMR0_u8_OUTPUT_MODE)
			{
				case TMR0_NORMAL_OC_DISCNCTD:
				
					CLR_BIT(TMR0_u8_TCCR0_REG, 4);
					CLR_BIT(TMR0_u8_TCCR0_REG, 5);
					
				break;
				
				case TMR0_TOGGLE_OC_COMP_MATCH:
				
					SET_BIT(TMR0_u8_TCCR0_REG, 4);
					CLR_BIT(TMR0_u8_TCCR0_REG, 5);
					
				break;
				
				case TMR0_CLEAR_OC_COMP_MATCH:
				
					CLR_BIT(TMR0_u8_TCCR0_REG, 4);
					SET_BIT(TMR0_u8_TCCR0_REG, 5);
					
				break;
				
				case TMR0_SET_OC_COMP_MATCH;
				
					SET_BIT(TMR0_u8_TCCR0_REG, 4);
					SET_BIT(TMR0_u8_TCCR0_REG, 5);
					
				break;
				
				default:	// None of output modes

				break;	
			}//end  output mode switch 
		break;// Normal mode case 	
		
		//---------------------<CTC>-----------------------
		case TMR0_CTC_MODE:
			
			SET_BIT(TMR0_u8_TCCR0_REG, 3);
			CLR_BIT(TMR0_u8_TCCR0_REG, 6);
			
			/* Set the output mode */
			switch (TMR0_u8_OUTPUT_MODE)
			{
				case TMR0_NORMAL_OC_DISCNCTD:
				
					CLR_BIT(TMR0_u8_TCCR0_REG, 4);
					CLR_BIT(TMR0_u8_TCCR0_REG, 5);
					
				break;
				
				case TMR0_TOGGLE_OC_COMP_MATCH:
				
					SET_BIT(TMR0_u8_TCCR0_REG, 4);
					CLR_BIT(TMR0_u8_TCCR0_REG, 5);
					
				break;
				
				case TMR0_CLEAR_OC_COMP_MATCH:
				
					CLR_BIT(TMR0_u8_TCCR0_REG, 4);
					SET_BIT(TMR0_u8_TCCR0_REG, 5);
					
				break;
				
				case TMR0_SET_OC_COMP_MATCH:
				
					SET_BIT(TMR0_u8_TCCR0_REG, 4);
					SET_BIT(TMR0_u8_TCCR0_REG, 5);
					
				break;
				
				default:	// None of output modes
					
				break;	
			}//end  output mode switch
			
		break; // CTC mode case 
		
		//---------------------<Fast PWM>-----------------------
		case TMR0_FAST_PWM_MODE:
		
			SET_BIT(TMR0_u8_TCCR0_REG, 3);
			SET_BIT(TMR0_u8_TCCR0_REG, 6);
			
			/* Set the output mode */
			switch (TMR0_u8_OUTPUT_MODE)
			{
				case TMR0_NORMAL_OC_DISCNCTD:
				
					CLR_BIT(TMR0_u8_TCCR0_REG, 4);
					CLR_BIT(TMR0_u8_TCCR0_REG, 5);
					
				break;
				
				case TMR0_FAST_PWM_OC_NON_INVRTD:
				
					CLR_BIT(TMR0_u8_TCCR0_REG, 4);
					SET_BIT(TMR0_u8_TCCR0_REG, 5);
					
				break;
				
				case TMR0_FAST_PWM_OC_INVRTD:
				
					SET_BIT(TMR0_u8_TCCR0_REG, 4);
					SET_BIT(TMR0_u8_TCCR0_REG, 5);
					
				break;
				
				default:	// None of output modes
					
				break;	
			}//end  output mode switch	
			
		break; // Fast PWM case
		
		//-------------------<Phase Correct>---------------------
		case TMR0_PHASE_CORRECT_MODE:
		
			CLR_BIT(TMR0_u8_TCCR0_REG, 3);
			SET_BIT(TMR0_u8_TCCR0_REG, 6);

			/* Set the output mode */
			switch (TMR0_u8_OUTPUT_MODE)
			{
				case TMR0_NORMAL_OC_DISCNCTD:
				
					CLR_BIT(TMR0_u8_TCCR0_REG, 4);
					CLR_BIT(TMR0_u8_TCCR0_REG, 5);
					
				break;
				
				case TMR0_PhCORCT_OC_NON_INVRTD:
				
					CLR_BIT(TMR0_u8_TCCR0_REG, 4);
					SET_BIT(TMR0_u8_TCCR0_REG, 5);
					
				break;
				
				case TMR0_PhCORCT_OC_INVRTD:
				
					SET_BIT(TMR0_u8_TCCR0_REG, 4);
					SET_BIT(TMR0_u8_TCCR0_REG, 5);
					
				break;
				
				default:	// None of output modes 
					
				break;	
			}//end  output mode switch	
		
		break; // Phase Correct case
		
		default:	//None of Timers Modes 
			
		break;
	}//end switch 
	
}// end Timer_0 Init


//###########################################< Set Mode Func >###########################################

void TMR0_voidSetMode(u8 Copy_u8TimerMode, u8 Copy_u8OutputMode)
{
	
	/* Set OC0 pin direction to output*/
	DIO_u8SetPinDirection(DIO_u8_PORTB, DIO_u8_PIN3, DIO_u8_OUTPUT);
	
	switch (Copy_u8TimerMode)
	{
		//---------------------<Normal>-----------------------
		case TMR0_NORMAL_MODE:
			
			switch (Copy_u8OutputMode)
			{
				case TMR0_NORMAL_OC_DISCNCTD:
					
					/* Stop Timer */
					TMR0_voidDisable();
					
					/* Enable Timer Mode */
					CLR_BIT(TMR0_u8_TCCR0_REG, 6);
					CLR_BIT(TMR0_u8_TCCR0_REG, 3);
			
					/* Enable Output Mode */
					CLR_BIT(TMR0_u8_TCCR0_REG, 4);
					CLR_BIT(TMR0_u8_TCCR0_REG, 5);
			
				break;
				
				case TMR0_TOGGLE_OC_COMP_MATCH:
				
					/* Stop Timer */
					TMR0_voidDisable();
					
					/* Enable Timer Mode */
					CLR_BIT(TMR0_u8_TCCR0_REG, 6);
					CLR_BIT(TMR0_u8_TCCR0_REG, 3);
				
					/* Enable Output Mode */
					SET_BIT(TMR0_u8_TCCR0_REG, 4);
					CLR_BIT(TMR0_u8_TCCR0_REG, 5);
					
				break;
				
				case TMR0_CLEAR_OC_COMP_MATCH:
					
					/* Stop Timer */
					TMR0_voidDisable();
					
					/* Enable Timer Mode */
					CLR_BIT(TMR0_u8_TCCR0_REG, 6);
					CLR_BIT(TMR0_u8_TCCR0_REG, 3);
				
					/* Enable Output Mode */
					CLR_BIT(TMR0_u8_TCCR0_REG, 4);
					SET_BIT(TMR0_u8_TCCR0_REG, 5);
					
				break;
				
				case TMR0_SET_OC_COMP_MATCH:
					
					/* Stop Timer */
					TMR0_voidDisable();
					
					/* Enable Timer Mode */
					CLR_BIT(TMR0_u8_TCCR0_REG, 6);
					CLR_BIT(TMR0_u8_TCCR0_REG, 3);	
				
					/* Enable Output Mode */
					SET_BIT(TMR0_u8_TCCR0_REG, 4);
					SET_BIT(TMR0_u8_TCCR0_REG, 5);
					
				break;
				
				default:	
				break;	
			}//end  output mode switch 
		break;// Normal mode case 	
		
		//---------------------<CTC>-----------------------
		case TMR0_CTC_MODE:
			
			
			
			/* Set the output mode */
			switch (Copy_u8OutputMode)
			{
				case TMR0_NORMAL_OC_DISCNCTD:
					
					/* Stop Timer */
					TMR0_voidDisable();
	
					/* Enable Timer Mode */
					SET_BIT(TMR0_u8_TCCR0_REG, 3);
					CLR_BIT(TMR0_u8_TCCR0_REG, 6);	
				
					/* Enable Output Mode */
					CLR_BIT(TMR0_u8_TCCR0_REG, 4);
					CLR_BIT(TMR0_u8_TCCR0_REG, 5);
					
				break;
				
				case TMR0_TOGGLE_OC_COMP_MATCH:
					
					/* Stop Timer */
					TMR0_voidDisable();
	
					/* Enable Timer Mode */
					SET_BIT(TMR0_u8_TCCR0_REG, 3);
					CLR_BIT(TMR0_u8_TCCR0_REG, 6);
				
					/* Enable Output Mode */
					SET_BIT(TMR0_u8_TCCR0_REG, 4);
					CLR_BIT(TMR0_u8_TCCR0_REG, 5);
					
				break;
				
				case TMR0_CLEAR_OC_COMP_MATCH:
				
					/* Stop Timer */
					TMR0_voidDisable();
	
					/* Enable Timer Mode */
					SET_BIT(TMR0_u8_TCCR0_REG, 3);
					CLR_BIT(TMR0_u8_TCCR0_REG, 6);	
				
					/* Enable Output Mode */
					CLR_BIT(TMR0_u8_TCCR0_REG, 4);
					SET_BIT(TMR0_u8_TCCR0_REG, 5);
					
				break;
				
				case TMR0_SET_OC_COMP_MATCH:
					
					/* Stop Timer */
					TMR0_voidDisable();
	
					/* Enable Timer Mode */
					SET_BIT(TMR0_u8_TCCR0_REG, 3);
					CLR_BIT(TMR0_u8_TCCR0_REG, 6);	
				
					/* Enable Output Mode */
					SET_BIT(TMR0_u8_TCCR0_REG, 4);
					SET_BIT(TMR0_u8_TCCR0_REG, 5);
					
				break;
				
				default:	
				break;	
			}//end  output mode switch
			
		break; // CTC mode case 
		
		//---------------------<Fast PWM>-----------------------
		case TMR0_FAST_PWM_MODE:
		
			
			
			/* Set the output mode */
			switch (Copy_u8OutputMode)
			{
				case TMR0_NORMAL_OC_DISCNCTD:
					
					/* Stop Timer */
					TMR0_voidDisable();
	
					/* Enable Timer Mode */
					SET_BIT(TMR0_u8_TCCR0_REG, 3);
					SET_BIT(TMR0_u8_TCCR0_REG, 6);	
				
					/* Enable Output Mode */
					CLR_BIT(TMR0_u8_TCCR0_REG, 4);
					CLR_BIT(TMR0_u8_TCCR0_REG, 5);
					
				break;
				
				case TMR0_FAST_PWM_OC_NON_INVRTD:
					
					/* Stop Timer */
					TMR0_voidDisable();
	
					/* Enable Timer Mode */
					SET_BIT(TMR0_u8_TCCR0_REG, 3);
					SET_BIT(TMR0_u8_TCCR0_REG, 6);	
				
					/* Enable Output Mode */
					CLR_BIT(TMR0_u8_TCCR0_REG, 4);
					SET_BIT(TMR0_u8_TCCR0_REG, 5);
					
				break;
				
				case TMR0_FAST_PWM_OC_INVRTD:
					
					/* Stop Timer */
					TMR0_voidDisable();
	
					/* Enable Timer Mode */
					SET_BIT(TMR0_u8_TCCR0_REG, 3);
					SET_BIT(TMR0_u8_TCCR0_REG, 6);	
				
					/* Enable Output Mode */
					SET_BIT(TMR0_u8_TCCR0_REG, 4);
					SET_BIT(TMR0_u8_TCCR0_REG, 5);
					
				break;
				
				default:	
				break;	
			}//end  output mode switch	
			
		break; // Fast PWM case
		
		//-------------------<Phase Correct>---------------------
		case TMR0_PHASE_CORRECT_MODE:
		
			

			/* Set the output mode */
			switch (Copy_u8OutputMode)
			{
				case TMR0_NORMAL_OC_DISCNCTD:
					
					/* Stop Timer */
					TMR0_voidDisable();
	
					/* Enable Timer Mode */
					CLR_BIT(TMR0_u8_TCCR0_REG, 3);
					SET_BIT(TMR0_u8_TCCR0_REG, 6);	
				
					/* Enable Output Mode */
					CLR_BIT(TMR0_u8_TCCR0_REG, 4);
					CLR_BIT(TMR0_u8_TCCR0_REG, 5);
	
				break;
				
				case TMR0_PhCORCT_OC_NON_INVRTD:
					
					/* Stop Timer */
					TMR0_voidDisable();
	
					/* Enable Timer Mode */
					CLR_BIT(TMR0_u8_TCCR0_REG, 3);
					SET_BIT(TMR0_u8_TCCR0_REG, 6);	
				
					/* Enable Output Mode */
					CLR_BIT(TMR0_u8_TCCR0_REG, 4);
					SET_BIT(TMR0_u8_TCCR0_REG, 5);
					
				break;
				
				case TMR0_PhCORCT_OC_INVRTD:
					
					/* Stop Timer */
					TMR0_voidDisable();
	
					/* Enable Timer Mode */
					CLR_BIT(TMR0_u8_TCCR0_REG, 3);
					SET_BIT(TMR0_u8_TCCR0_REG, 6);	
				
					/* Enable Output Mode */
					SET_BIT(TMR0_u8_TCCR0_REG, 4);
					SET_BIT(TMR0_u8_TCCR0_REG, 5);
					
				break;
				
				default:	
				break;	
			}//end  output mode switch	
		
		break; // Phase Correct case
		
		default:	
		break;
	}//end switch 

}// end func 


//###########################################< Normal Mode Func >###########################################

u8 TMR0_u8NormalMode(u16 Copy_u16EventTime, u8 Copy_u8ClkMode, void (*Copy_pfEvent)(void))
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	f32 Local_f32TOV;					// Time of overflow
	f32 Local_f32Fractional;			// the fractional points
	f32 Local_f32NumOfOverFlows;
	u8 Local_u8FractionalCounts;		// Number of counts that represents the fractional points
	
	
	if (Copy_pfEvent != NULL && TMR0_u8BusyFlag == 0)
	{	
		/* Set the Busy Flag */
		TMR0_u8BusyFlag = 1;
		
		switch (Copy_u8ClkMode)
		{
			case TMR0_CLK_NO_PRSCLR:
			
				Local_f32TOV = (1.0*256.0)/F_u8_CPU;		// calculating Tov with microsecond
				
				if (Copy_u16EventTime >= Local_f32TOV)
				{	
					/* Calculating the preload val */
					Local_f32NumOfOverFlows = (f32) ((f32)Copy_u16EventTime / Local_f32TOV);
					TMR0_u16NumOfOverFlows = (u16) Local_f32NumOfOverFlows;			// Num of Overflows without fractional 
					Local_f32Fractional = (f32)(Local_f32NumOfOverFlows - (f32)TMR0_u16NumOfOverFlows);
					Local_u8FractionalCounts = (u8)(Local_f32Fractional * 256.0);
				
					if (Local_u8FractionalCounts > 0)
					{
						TMR0_u16NumOfOverFlows += 1; 							//plus one for the fractional counts
						TMR0_u8PreloadVal = 256 - Local_u8FractionalCounts;
						TMR0_u8_TCNT0_REG = TMR0_u8PreloadVal; 				// Assign preload val to the counter register
					}
				
					/* Passing the Add to the global pointer */
					TMR0_pfEvent = Copy_pfEvent;
				
					/* Enable Timer Overflow Interrupt */
					SET_BIT(TMR0_u8_TIMSK_REG,0);
				
					/* Set the Clk to start the Timer */
					TMR0_voidEnable(TMR0_CLK_NO_PRSCLR);
					
				}// end if 	
				else 
				{
					/* Update the Error state */
					Local_u8ErrorState = STD_TYPES_NOK;	
					
					/* Clear the Busy Flag */
					TMR0_u8BusyFlag = 0;
				}	
		
			break;
			//---------------------------------------------------------------------
			case TMR0_CLK_PRSCLR_8:
			
				Local_f32TOV = (8.0*256.0)/F_u8_CPU;		// calculating Tov
				
				if (Copy_u16EventTime >= Local_f32TOV)
				{	
					/* Calculating the preload val */
					Local_f32NumOfOverFlows = (f32)Copy_u16EventTime / Local_f32TOV;
					TMR0_u16NumOfOverFlows = (u16) Local_f32NumOfOverFlows;			// Num of Overflows without fractional
					Local_f32Fractional = (f32)(Local_f32NumOfOverFlows - (f32)TMR0_u16NumOfOverFlows);
					Local_u8FractionalCounts = (u8)(Local_f32Fractional * 256.0);
				
					if (Local_u8FractionalCounts > 0)
					{
						TMR0_u16NumOfOverFlows += 1; 							//plus one for the fractional counts
						TMR0_u8PreloadVal = 256 - Local_u8FractionalCounts;
						TMR0_u8_TCNT0_REG = TMR0_u8PreloadVal; 				// Assign preload val to the counter register
					}
				
					/* Passing the Add to the global pointer */
					TMR0_pfEvent = Copy_pfEvent;
				
					/* Enable Timer Overflow Interrupt */
					SET_BIT(TMR0_u8_TIMSK_REG,0);
			
					/* Set the Clk to start the Timer */
					TMR0_voidEnable(TMR0_CLK_PRSCLR_8);
					
				} // end if 
				else 
				{
					/* Update the Error state */
					Local_u8ErrorState = STD_TYPES_NOK;	
					
					/* Clear the Busy Flag */
					TMR0_u8BusyFlag = 0;
				}	
				
			break;
			//------------------------------------------------------------------------------
			case TMR0_CLK_PRSCLR_64:
			
				Local_f32TOV = (64.0*256.0)/F_u8_CPU;				// calculating Tov
				
				if (Copy_u16EventTime >= Local_f32TOV)
				{	
					/* Calculating the preload val */
					Local_f32NumOfOverFlows = (f32)Copy_u16EventTime / Local_f32TOV;
					TMR0_u16NumOfOverFlows = (u16) Local_f32NumOfOverFlows;			// Num of Overflows without fractional
					Local_f32Fractional = (f32)(Local_f32NumOfOverFlows - (f32)TMR0_u16NumOfOverFlows);
					Local_u8FractionalCounts = (u8)(Local_f32Fractional * 256.0);
				
					if (Local_u8FractionalCounts > 0)
					{
						TMR0_u16NumOfOverFlows += 1; 							//plus one for the fractional counts
						TMR0_u8PreloadVal = 256 - Local_u8FractionalCounts;
						TMR0_u8_TCNT0_REG = TMR0_u8PreloadVal; 				// Assign preload val to the counter register
					}
				
					/* Passing the Add to the global pointer */
					TMR0_pfEvent = Copy_pfEvent;
				
					/* Enable Timer Overflow Interrupt */
					SET_BIT(TMR0_u8_TIMSK_REG,0);
				
					/* Set the Clk to start the Timer */
					TMR0_voidEnable(TMR0_CLK_PRSCLR_64);
					
				}// end if 
				else 
				{
					/* Update the Error state */
					Local_u8ErrorState = STD_TYPES_NOK;	
					
					/* Clear the Busy Flag */
					TMR0_u8BusyFlag = 0;
				}	
		
			break;
			//-----------------------------------------------------------------------------------
			case TMR0_CLK_PRSCLR_256:
			
				Local_f32TOV = (256.0*256.0)/F_u8_CPU;				// calculating Tov
				
				if (Copy_u16EventTime >= Local_f32TOV)
				{	
					/* Calculating the preload val */
					Local_f32NumOfOverFlows = (f32)Copy_u16EventTime / Local_f32TOV;
					TMR0_u16NumOfOverFlows = (u16) Local_f32NumOfOverFlows;			// Num of Overflows without fractional
					Local_f32Fractional = (f32)(Local_f32NumOfOverFlows - (f32)TMR0_u16NumOfOverFlows);
					Local_u8FractionalCounts = (u8)(Local_f32Fractional * 256.0);
				
					if (Local_u8FractionalCounts > 0)
					{
						TMR0_u16NumOfOverFlows += 1; 							//plus one for the fractional counts
						TMR0_u8PreloadVal = 256 - Local_u8FractionalCounts;
						TMR0_u8_TCNT0_REG = TMR0_u8PreloadVal; 				// Assign preload val to the counter register
					}
				
					/* Passing the Add to the global pointer */
					TMR0_pfEvent = Copy_pfEvent;
				
					/* Enable Timer Overflow Interrupt */
					SET_BIT(TMR0_u8_TIMSK_REG,0);
				
					/* Set the Clk to start the Timer */
					TMR0_voidEnable(TMR0_CLK_PRSCLR_256);
				
				}//end if
				else 
				{
					/* Update the Error state */
					Local_u8ErrorState = STD_TYPES_NOK;	
					
					/* Clear the Busy Flag */
					TMR0_u8BusyFlag = 0;
				}
				
			break;
			//----------------------------------------------------------------------------------
			case TMR0_CLK_PRSCLR_1024:
				
				Local_f32TOV = (1024.0*256.0)/F_u8_CPU;			// calculating Tov
				
				if (Copy_u16EventTime >= Local_f32TOV)
				{	
					/* Calculating the preload val */
					Local_f32NumOfOverFlows = (f32)Copy_u16EventTime / Local_f32TOV;
					TMR0_u16NumOfOverFlows = (u16) Local_f32NumOfOverFlows;			// Num of Overflows without fractional
					Local_f32Fractional = (f32)(Local_f32NumOfOverFlows - (f32)TMR0_u16NumOfOverFlows);
					Local_u8FractionalCounts = (u8)(Local_f32Fractional * 256.0);
				
					if (Local_u8FractionalCounts > 0)
					{
						TMR0_u16NumOfOverFlows += 1; 							//plus one for the fractional counts
						TMR0_u8PreloadVal = 256 - Local_u8FractionalCounts;
						TMR0_u8_TCNT0_REG = TMR0_u8PreloadVal; 				// Assign preload val to the counter register
					}
				
					/* Passing the Add to the global pointer */
					TMR0_pfEvent = Copy_pfEvent;
				
					/* Enable Timer Overflow Interrupt */
					SET_BIT(TMR0_u8_TIMSK_REG,0);
				
					/* Set the Clk to start the Timer */
					TMR0_voidEnable(TMR0_CLK_PRSCLR_1024);
				
				}// end if 
				else 
				{
					/* Update the Error state */
					Local_u8ErrorState = STD_TYPES_NOK;	
					
					/* Clear the Busy Flag */
					TMR0_u8BusyFlag = 0;
				}
				
			break;
		
		/*	case TMR0_EXT_CLK_T0_Fall_EDGE:
				
				TMR0_voidEnable(TMR0_EXT_CLK_T0_Fall_EDGE);
		
			break;
		
			case TMR0_EXT_CLK_T0_RIS_EDGE:
				
				TMR0_voidEnable(TMR0_EXT_CLK_T0_RIS_EDGE);
			
			break;
		*/
			default:	// None of Clk modes 
				
				/* Udate the Error state */
				Local_u8ErrorState = STD_TYPES_NOK;
				
				/* Clear the Busy Flag */
				TMR0_u8BusyFlag = 0;
				
			break;		
		}//end switch
	}//end if 	
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}	
	
	return Local_u8ErrorState;
}// end Normal Mode function 


//###########################################< CTC Mode Func >###########################################

u8 TMR0_u8CTCMode(u16 Copy_u16EventTime, u8 Copy_u8OCRval, u8 Copy_u8ClkMode, void (*Copy_pfEvent)(void))
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	u16 Local_u16TOV;
	
	if (Copy_pfEvent != NULL && TMR0_u8BusyFlag ==0)
	{
		/* Set the Busy falg */
		TMR0_u8BusyFlag = 1;
		
		switch (Copy_u8ClkMode)
		{
			case TMR0_CLK_NO_PRSCLR:
				
				Local_u16TOV = (1*Copy_u8OCRval)/F_u8_CPU;	 		// TOV in microsecond
				TMR0_u16NumOfCompMatch = Copy_u16EventTime / Local_u16TOV;
				
				/* Assign OCR value to the Rgister */
				TMR0_u8_OCR0_REG = Copy_u8OCRval;
				
				/* Passing Address to the global pointer */
				TMR0_pfEvent = Copy_pfEvent;
				
				/* Enable Timer Compare Match Interrupt */
				SET_BIT(TMR0_u8_TIMSK_REG,1);
				
				/* Set the CLK to start the timer */
				TMR0_voidEnable(TMR0_CLK_NO_PRSCLR);
				
			break;
			//---------------------------------------------------------------
			case TMR0_CLK_PRSCLR_8:
			
				Local_u16TOV = (8*Copy_u8OCRval)/F_u8_CPU;	 		// TOV in microsecond
				TMR0_u16NumOfCompMatch = Copy_u16EventTime / Local_u16TOV;
				
				/* Assign OCR value to the Rgister */
				TMR0_u8_OCR0_REG = Copy_u8OCRval;
				
				/* Passing Address to the global pointer */
				TMR0_pfEvent = Copy_pfEvent;
				
				/* Enable Timer Compare Match Interrupt */
				SET_BIT(TMR0_u8_TIMSK_REG,1);
				
				/* Set the CLK to start the timer */
				TMR0_voidEnable(TMR0_CLK_PRSCLR_8);
				
			break;
			//---------------------------------------------------------------
			case TMR0_CLK_PRSCLR_64:
				
				Local_u16TOV = (64*Copy_u8OCRval)/F_u8_CPU;	 		// TOV in microsecond
				TMR0_u16NumOfCompMatch = Copy_u16EventTime / Local_u16TOV;
				
				/* Assign OCR value to the Rgister */
				TMR0_u8_OCR0_REG = Copy_u8OCRval;
				
				/* Passing Address to the global pointer */
				TMR0_pfEvent = Copy_pfEvent;
				
				/* Enable Timer Compare Match Interrupt */
				SET_BIT(TMR0_u8_TIMSK_REG,1);
				
				/* Set the CLK to start the timer */
				TMR0_voidEnable(TMR0_CLK_PRSCLR_64);
				
			break;
			//---------------------------------------------------------------
			case TMR0_CLK_PRSCLR_256:
			
				Local_u16TOV = (256*Copy_u8OCRval)/F_u8_CPU;	 		// TOV in microsecond
				TMR0_u16NumOfCompMatch = Copy_u16EventTime / Local_u16TOV;
				
				/* Assign OCR value to the Rgister */
				TMR0_u8_OCR0_REG = Copy_u8OCRval;
				
				/* Passing Address to the global pointer */
				TMR0_pfEvent = Copy_pfEvent;
				
				/* Enable Timer Compare Match Interrupt */
				SET_BIT(TMR0_u8_TIMSK_REG,1);
				
				/* Set the CLK to start the timer */
				TMR0_voidEnable(TMR0_CLK_PRSCLR_256);
				
			break;
			//---------------------------------------------------------------
			case TMR0_CLK_PRSCLR_1024:
			
				Local_u16TOV = (1024*Copy_u8OCRval)/F_u8_CPU;	 		// TOV in microsecond
				TMR0_u16NumOfCompMatch = Copy_u16EventTime / Local_u16TOV;
				
				/* Assign OCR value to the Rgister */
				TMR0_u8_OCR0_REG = Copy_u8OCRval;
				
				/* Passing Address to the global pointer */
				TMR0_pfEvent = Copy_pfEvent;
				
				/* Enable Timer Compare Match Interrupt */
				SET_BIT(TMR0_u8_TIMSK_REG,1);
				
				/* Set the CLK to start the timer */
				TMR0_voidEnable(TMR0_CLK_PRSCLR_1024);
				
			break;
			//---------------------------------------------------------------
		/*	case TMR0_EXT_CLK_T0_Fall_EDGE:
				
				TMR0_voidEnable(TMR0_EXT_CLK_T0_Fall_EDGE);
			
			break;
			//---------------------------------------------------------------
			case TMR0_EXT_CLK_T0_RIS_EDGE:
				
				TMR0_voidEnable(TMR0_EXT_CLK_T0_RIS_EDGE);
				
			break;
		*/
			default:	// None of CLK modes 
				
				/* Update the Error state */
				Local_u8ErrorState = STD_TYPES_NOK;
				
				/* Clear the Busy Flag */
				TMR0_u8BusyFlag = 0;
			
			break;
			
		}// end switch
	}// end if 
	else 
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}	
	
	return Local_u8ErrorState
}// end CTC Mode function


//###########################################< Disable Func >###########################################

void TMR0_voidDisable()
{
	/* Stop CLK */
	CLR_BIT(TMR0_u8_TCCR0_REG, 0);
	CLR_BIT(TMR0_u8_TCCR0_REG, 1);
	CLR_BIT(TMR0_u8_TCCR0_REG, 2);
	
	/* Clearing Registers */
	TMR0_u8_TCNT0_REG = 0x00;
	TMR0_u8_OCR0_REG = 0x00;
	
	/* Disable Interrupts */
	CLR_BIT(TMR0_u8_TIMSK_REG,0);
	CLR_BIT(TMR0_u8_TIMSK_REG,1);

	/* Clearing Busy Flag */
	TMR0_u8BusyFlag = 0;
}


//###########################################< Enable Func >###########################################

void TMR0_voidEnable(u8 Copy_u8ClkMode)
{
	switch (Copy_u8ClkMode)
	{
		case TMR0_CLK_NO_PRSCLR:
		
			SET_BIT(TMR0_u8_TCCR0_REG, 0);
			CLR_BIT(TMR0_u8_TCCR0_REG, 1);
			CLR_BIT(TMR0_u8_TCCR0_REG, 2);
		
		break;
		//--------------------------
		case TMR0_CLK_PRSCLR_8:
		
			CLR_BIT(TMR0_u8_TCCR0_REG, 0);
			SET_BIT(TMR0_u8_TCCR0_REG, 1);
			CLR_BIT(TMR0_u8_TCCR0_REG, 2);
		
		break;
		//--------------------------
		case TMR0_CLK_PRSCLR_64:
		
			SET_BIT(TMR0_u8_TCCR0_REG, 0);
			SET_BIT(TMR0_u8_TCCR0_REG, 1);
			CLR_BIT(TMR0_u8_TCCR0_REG, 2);
		
		break;
		//--------------------------
		case TMR0_CLK_PRSCLR_256:
		
			CLR_BIT(TMR0_u8_TCCR0_REG, 0);
			CLR_BIT(TMR0_u8_TCCR0_REG, 1);
			SET_BIT(TMR0_u8_TCCR0_REG, 2);
		
		break;
		//--------------------------
		case TMR0_CLK_PRSCLR_1024:
		
			SET_BIT(TMR0_u8_TCCR0_REG, 0);
			CLR_BIT(TMR0_u8_TCCR0_REG, 1);
			SET_BIT(TMR0_u8_TCCR0_REG, 2);
		
		break;
		//--------------------------
		case TMR0_EXT_CLK_T0_Fall_EDGE:
		
			CLR_BIT(TMR0_u8_TCCR0_REG, 0);
			SET_BIT(TMR0_u8_TCCR0_REG, 1);
			SET_BIT(TMR0_u8_TCCR0_REG, 2);
		
		break;
		//--------------------------
		case TMR0_EXT_CLK_T0_RIS_EDGE:
		
			SET_BIT(TMR0_u8_TCCR0_REG, 0);
			SET_BIT(TMR0_u8_TCCR0_REG, 1);
			SET_BIT(TMR0_u8_TCCR0_REG, 2);
		
		break;
		//--------------------------
		default:
		
			/* Do Nothing */
		
		break;
		
	}//end switch 
	
}// end Timer0 Enable Function 


//###########################################< Fast PWM >###########################################

u8 TMR0_u8FastPWM(u8 Copy_u8DutyCycle, u8 Copy_u8ClkMode)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	
	/* Check Busy Flag */
	if (TMR0_u8BusyFlag == 0)
	{	
		f32 Local_f32TonValue = 0.0;
		u8 Local_u8TonValue = 0;
		f32 Local_f32Fraction = 0.0;
		//---------------------------------
		
		/* Set Busy Flag */
		TMR0_u8BusyFlag = 1;
		
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
		if ((GET_BIT(TMR0_u8_TCCR0_REG, 4)==0) && (GET_BIT(TMR0_u8_TCCR0_REG, 5)==1))		// Non-Inverted Mode
		{	
		
			TMR0_u8_OCR0_REG = Local_u8TonValue - 1 ;			// OCR = Num of Ton Counts
			
			/* Set Prescaler to start timer */
			TMR0_voidEnable(Copy_u8ClkMode);

		}	
		//-----------------------------------------------
		else if ((GET_BIT(TMR0_u8_TCCR0_REG, 4)==1) && (GET_BIT(TMR0_u8_TCCR0_REG, 5)==1))		// Inverted Mode
		{
			
			TMR0_u8_OCR0_REG = 256 - (Local_u8TonValue - 1);	// OCR = Num of Toff Counts
			
			/* Set Prescaler to start timer */
			TMR0_voidEnable(Copy_u8ClkMode);
		
		}
		//-----------------------------------------------
		else 
		{
			Local_u8ErrorState = STD_TYPES_NOK;
			TMR0_u8BusyFlag = 0;
		}	
	}// end if 
	
	else // Busy Flag = 1
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}	
	
	return Local_u8ErrorState;
	
}// end Fast PWM Function 


//###########################################< Phase Correct >###########################################

u8 TMR0_u8PhaseCorrect(u8 Copy_u8DutyCycle, u8 Copy_u8ClkMode)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	
	/* Check Busy Flag */
	if (TMR0_u8BusyFlag == 0)
	{	
		f32 Local_f32TonValue = 0.0;
		u8 Local_u8TonValue = 0;
		f32 Local_f32Fraction = 0.0;
		//-----------------------------
		
		/* Set Busy Flag */
		TMR0_u8BusyFlag = 1;
		
		/* Calculation */
		Local_f32TonValue = (510.0 * (f32)Copy_u8DutyCycle)/100.0;
		Local_u8TonValue = (u8) Local_f32TonValue;
		Local_f32Fraction = Local_f32TonValue - Local_u8TonValue;
				
		if (Local_f32Fraction >= 0.445)
		{
			Local_u8TonValue +=	1;
		}
		
		
		/* Set OC0 pin direction */
		DIO_u8SetPinDirection(DIO_u8_PORTB, DIO_u8_PIN3, DIO_u8_OUTPUT);
		
		
		/* Check the output mode */
		if ((GET_BIT(TMR0_u8_TCCR0_REG, 4)==0) && (GET_BIT(TMR0_u8_TCCR0_REG, 5)==1))		// Non-Inverted Mode
		{	
			
			TMR0_u8_OCR0_REG = Local_u8TonValue /2 ;					// OCR = Num of Ton Counts /2 
			
			/* Set Prescaler to start timer */
			TMR0_voidEnable(Copy_u8ClkMode);

		}	
		//-----------------------------------------------
		else if ((GET_BIT(TMR0_u8_TCCR0_REG, 4)==1) && (GET_BIT(TMR0_u8_TCCR0_REG, 5)==1))		// Inverted Mode
		{		
			
			TMR0_u8_OCR0_REG = (510 - Local_u8TonValue ) / 2;			// OCR = Num of Toff Counts /2
			
			/* Set Prescaler to start timer */
			TMR0_voidEnable(Copy_u8ClkMode);
		
		}
		//-----------------------------------------------
		else 
		{
			Local_u8ErrorState = STD_TYPES_NOK;
			TMR0_u8BusyFlag = 0;
		}
	}// end if

	else // Busy Flag = 1
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}	
	return Local_u8ErrorState;
}//end Phase Correct Function 


//###########################################< ISR_Normal Mode >###########################################

void __vector_11(void) __attribute__((signal));

void __vector_11(void)
{
	static u16 Local_u16CounterOVF = 0;
	
	Local_u16CounterOVF++;
	
	if (Local_u16CounterOVF == TMR0_u16NumOfOverFlows)
	{
		
		// Reset the Preload value 
		TMR0_u8_TCNT0_REG = TMR0_u8PreloadVal;
		
		// Resetting the counter 
		Local_u16CounterOVF = 0;
		
		// Excuting the required event
		TMR0_pfEvent();			 
		
	}	
}// end Normal mode ISR


//###########################################< ISR_CTC Mode >###########################################

void __vector_10(void) __attribute__((signal));

void __vector_10(void)
{
	static u16 Local_u16CounterCTC = 0;
	
	Local_u16CounterCTC++;
	
	if (Local_u16CounterCTC == TMR0_u16NumOfCompMatch)
	{
		// Resetting the counter 
		Local_u16CounterCTC = 0;
		
	    // Excuting the required event
		TMR0_pfEvent();	
	}	
	
}//end CTC Mode ISR




