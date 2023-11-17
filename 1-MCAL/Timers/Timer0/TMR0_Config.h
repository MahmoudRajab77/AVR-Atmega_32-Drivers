/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  26/5/2020    *******/
/******* Update :            	*******/
/******* SWC    :     TMR0      *******/
/******* Version:     1.0       *******/
/**************************************/

#ifndef TMR0_CONFIG_H
#define TMR0_CONFIG_H


#define F_u8_CPU		8  // 8 MHZ

//--------------< Timer0 Modes >--------------

/* options : - TMR0_NORMAL_MODE
		     - TMR0_CTC_MODE
		     - TMR0_PHASE_CORRECT_MODE	
		     - TMR0_FAST_PWM_MODE		
*/




//**********************< Choose the Modes for your Timer >***********************

#define TMR0_u8_MODE			TMR0_NORMAL_MODE





//--------------< Output Mode for Non-PWM >--------------

/* options : - TMR0_NORMAL_OC_DISCNCTD
			 - TMR0_TOGGLE_OC_COMP_MATCH
			 - TMR0_SET_OC_COMP_MATCH
			 - TMR0_CLEAR_OC_COMP_MATCH
*/			 

//--------------< Output modes for Fast PWM >--------------

/* options : - TMR0_NORMAL_OC_DISCNCTD
			 - TMR0_FAST_PWM_OC_NON_INVRTD
			 - TMR0_FAST_PWM_OC_INVRTD	
*/

//--------------< Output modes for Phase Correct >--------------

/* options : - TMR0_NORMAL_OC_DISCNCTD
			 - TMR0_PhCORCT_OC_NON_INVRTD
			 - TMR0_PhCORCT_OC_INVRTD
*/			 




//**********************< Choose the Output Mode for your Timer >**********************

#define TMR0_u8_OUTPUT_MODE			TMR0_NORMAL_OC_DISCONNECTED



#endif 