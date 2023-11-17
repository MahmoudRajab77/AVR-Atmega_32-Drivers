/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  26/5/2020    *******/
/******* Update :            	*******/
/******* SWC    :     TMR0      *******/
/******* Version:     1.0       *******/
/**************************************/

#ifndef	TMR0_INTERFACE_H
#define TMR0_INTERFACE_H


//---------------< Macros for Timer0 Modes >-------------------------

#define TMR0_NORMAL_MODE					0
#define TMR0_CTC_MODE						1
#define TMR0_PHASE_CORRECT_MODE				2	
#define TMR0_FAST_PWM_MODE					3

//----------------< Macros for Non-PWM Output Modes >-----------------

#define TMR0_NORMAL_OC_DISCNCTD				0
#define TMR0_TOGGLE_OC_COMP_MATCH			1	
#define TMR0_SET_OC_COMP_MATCH				2
#define TMR0_CLEAR_OC_COMP_MATCH			3

//---------------< Macros for Fast-PWM Output Modes >-----------------

#define TMR0_NORMAL_OC_DISCNCTD				0
#define TMR0_FAST_PWM_OC_NON_INVRTD			1
#define TMR0_FAST_PWM_OC_INVRTD				2

//---------------< Macros for Phase-Correct Output Modes >-------------

#define TMR0_NORMAL_OC_DISCNCTD				0
#define TMR0_PhCORCT_OC_NON_INVRTD			1
#define TMR0_PhCORCT_OC_INVRTD				2

//--------------------< Macros for Clk Modes >--------------------------

#define TMR0_CLK_NO_PRSCLR					0
#define TMR0_CLK_PRSCLR_8					1
#define TMR0_CLK_PRSCLR_64					2
#define TMR0_CLK_PRSCLR_256					3
#define TMR0_CLK_PRSCLR_1024				4
#define TMR0_EXT_CLK_T0_Fall_EDGE			5
#define TMR0_EXT_CLK_T0_RIS_EDGE			6


//-----------------------< Timer_0 Functions >---------------------------------
void TMR0_voidInit();

void TMR0_voidSetMode(u8 Copy_u8TimerMode, u8 Copy_u8OutputMode);

void TMR0_voidDisable();

void TMR0_voidEnable(u8 Copy_u8ClkMode);

u8 TMR0_u8NormalMode(u16 Copy_u16EventTime, u8 Copy_u8ClkMode, void (*Copy_pfEvent)(void));

u8 TMR0_u8CTCMode(u16 Copy_u16EventTime, u8 Copy_u8OCRval, u8 Copy_u8ClkMode, void (*Copy_pfEvent)(void));

u8 TMR0_u8FastPWM(u8 Copy_u8DutyCycle, u8 Copy_u8ClkMode);

u8 TMR0_u8PhaseCorrect(u8 Copy_u8DutyCycle, u8 Copy_u8ClkMode);



#endif