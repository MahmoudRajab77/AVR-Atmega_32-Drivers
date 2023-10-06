/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  26/5/2020    *******/
/******* Update :            	*******/
/******* SWC    :    TIMERS     *******/
/******* Version:     1.0       *******/
/**************************************/

#ifndef TIMERS_CONFIG_H
#define TIMERS_CONFIG_H


#define F_u32_CPU			8000000UL

//--------------< Timers Modes >--------------

/* options : - TIMERS_NORMAL_MODE
		     - TIMERS_CTC_MODE
		     - TIMERS_PHASE_CORRECT_MODE	
		     - TIMERS_FAST_PWM_MODE		
*/




//**********************< Choose the Modes for your Timers >***********************

#define TIMER0_u8_MODE			TIMERS_NORMAL_MODE





//--------------< Output Mode for Non-PWM >--------------

/* options : - TIMERS_NORMAL_OC_DISCNCTD
			 - TIMERS_TOGGLE_OC_COMP_MATCH
			 - TIMERS_SET_OC_COMP_MATCH
			 - TIMERS_CLEAR_OC_COMP_MATCH
*/			 

//--------------< Output modes for Fast PWM >--------------

/* options : - TIMERS_NORMAL_OC_DISCNCTD
			 - TIMERS_FAST_PWM_OC_NON_INVRTD
			 - TIMERS_FAST_PWM_OC_INVRTD	
*/

//--------------< Output modes for Phase Correct >--------------

/* options : - TIMERS_NORMAL_OC_DISCNCTD
			 - TIMERS_PhCORCT_OC_NON_INVRTD
			 - TIMERS_PhCORCT_OC_INVRTD
*/			 




//**********************< Choose the Output Mode for your Timers >**********************

#define TIMER0_u8_OUTPUT_MODE			NORMAL_OC_DISCONNECTED



#endif 