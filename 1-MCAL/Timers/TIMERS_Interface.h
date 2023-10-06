/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  26/5/2020    *******/
/******* Update :            	*******/
/******* SWC    :    TIMERS     *******/
/******* Version:     1.0       *******/
/**************************************/

#ifndef	TIMERS_INTERFACE_H
#define TIMERS_INTERFACE_H


//---------------< Macros for Timers Modes >-------------------------

#define TIMERS_NORMAL_MODE					0
#define TIMERS_CTC_MODE						1
#define TIMERS_PHASE_CORRECT_MODE			2	
#define TIMERS_FAST_PWM_MODE				3

//----------------< Macros for Non-PWM Output Modes >-----------------

#define TIMERS_NORMAL_OC_DISCNCTD			0
#define TIMERS_TOGGLE_OC_COMP_MATCH			1	
#define TIMERS_SET_OC_COMP_MATCH			2
#define TIMERS_CLEAR_OC_COMP_MATCH			3

//---------------< Macros for Fast-PWM Output Modes >-----------------

#define TIMERS_NORMAL_OC_DISCNCTD			0
#define TIMERS_FAST_PWM_OC_NON_INVRTD		1
#define TIMERS_FAST_PWM_OC_INVRTD			2

//---------------< Macros for Phase-Correct Output Modes >-------------

#define TIMERS_NORMAL_OC_DISCNCTD			0
#define TIMERS_PhCORCT_OC_NON_INVRTD		1
#define TIMERS_PhCORCT_OC_INVRTD			2

//--------------------< Macros for Clk Modes >--------------------------

#define TIMERS_CLK_NO_PRSCLR					0
#define TIMERS_CLK_PRSCLR_8						1
#define TIMERS_CLK_PRSCLR_64					3
#define TIMERS_CLK_PRSCLR_256					5
#define TIMERS_CLK_PRSCLR_1024					6

//----------------< Timer 2 >------------------
#define TIMERS_CLK_PRSCLR_32					2
#define TIMERS_CLK_PRSCLR_128					4	

//----------------< Timer 0&1 >------------------
#define TIMERS_EXT_CLK_Tpin_Fall_EDGE			7
#define TIMERS_EXT_CLK_Tpin_RIS_EDGE			8


//-----------------------< Timer_0 Functions >---------------------------------
u8 TIMERS_u8Timer0Init();

u8 TIMERS_u8Timer0SetMode(u8 Copy_u8TimerMode, u8 Copy_u8OutputMode);

void TIMERS_voidTimer0Disable();

void TIMERS_voidTimer0Enable(u8 Copy_u8ClkMode);

u8 TIMERS_u8Timer0NormalMode(u16 Copy_u16EventTime, u8 Copy_u8ClkMode, void (*Copy_pfEvent)(void));

u8 TIMERS_u8Timer0CTCMode(u16 Copy_u16EventTime, u8 Copy_u8OCRval, u8 Copy_u8ClkMode, void (*Copy_pfEvent)(void));

u8 TIMERS_u8Timer0FastPWM(u8 Copy_u8DutyCycle, u8 Copy_u8ClkMode);

u8 TIMERS_u8Timer0PhaseCorrect(u8 Copy_u8DutyCycle, u8 Copy_u8ClkMode);



#endif