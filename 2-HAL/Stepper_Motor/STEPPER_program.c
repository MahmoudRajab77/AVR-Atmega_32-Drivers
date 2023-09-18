/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  09/09/2020   *******/
/******* SWC    : STEPPER_MOTOR *******/
/******* Version:    1.0        *******/
/**************************************/

/* LIB Layer */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#define  F_CPU 		8000000UL
#include<util/delay.h>

/* MCAL Layer */
#include "DIO_interface.h"

/* HAL Layer */
#include"STEPPER_interface.h"
#include"STEPPER_config.h"

//-------------------------------------------

#define  STEPPER_FULL_ANGEL		360



u8 STEPPER_MOTOR_ROTATE(u8 Copy_u8Angle, u8 Copy_u8Direction){
	
//-------------------------------------<Preparation>---------------------------------------------	
	u8 Local_u8ErrorState = STD_TYPES_OK; //Error Flag 
	
	u16 Local_u16AnglePerFullStep = STEP_STRIDE_ANGLE * 2;
	u32 Local_u32NumberOfStepsFor360 = (u32) STEPPER_FULL_ANGEL / (u32) Local_u16AnglePerFullStep; //2048
	u32 Local_u32NumberOfSteps = (u32) ( ((u32) Copy_u8Angle * (u32) Local_u32NumberOfStepsFor360) / STEPPER_FULL_ANGEL);
		Local_u32NumberOfSteps = Local_u32NumberOfSteps / 4;
	
	u16 Local_u16IndexCounter = 0;	//Counter for loop 

//--------------------------------------<Function work>-----------------------------------------	

	// 1- In CASE of NO Errors
	if ( (Copy_u8Angle <= STEPPER_FULL_ANGEL) && ( (Copy_u8Direction == CCW) || (Copy_u8Direction == CW) ) ){
		
		// 1.1- In CASE the direction is Clockwise 
		if (Copy_u8Direction == CW){
			for (Local_u16IndexCounter ; Local_u16IndexCounter < Local_u32NumberOfSteps ; Local_u16IndexCounter++){
				
				DIO_u8SetPinValue(STEPER_PORT, STEPER_MOTOR_BLUE_COIL, DIO_u8_LOW);
				DIO_u8SetPinValue(STEPER_PORT, STEPER_MOTOR_PINK_COIL, DIO_u8_HIGH);
				DIO_u8SetPinValue(STEPER_PORT, STEPER_MOTOR_YELLOW_COIL, DIO_u8_HIGH);
				DIO_u8SetPinValue(STEPER_PORT, STEPER_MOTOR_ORANGE_COIL, DIO_u8_HIGH);
				_delay_ms(2);
				DIO_u8SetPinValue(STEPER_PORT, STEPER_MOTOR_BLUE_COIL, DIO_u8_HIGH);
				DIO_u8SetPinValue(STEPER_PORT, STEPER_MOTOR_PINK_COIL, DIO_u8_LOW);
				DIO_u8SetPinValue(STEPER_PORT, STEPER_MOTOR_YELLOW_COIL, DIO_u8_HIGH);
				DIO_u8SetPinValue(STEPER_PORT, STEPER_MOTOR_ORANGE_COIL, DIO_u8_HIGH);
				_delay_ms(2);
				DIO_u8SetPinValue(STEPER_PORT, STEPER_MOTOR_BLUE_COIL, DIO_u8_HIGH);
				DIO_u8SetPinValue(STEPER_PORT, STEPER_MOTOR_PINK_COIL, DIO_u8_HIGH);
				DIO_u8SetPinValue(STEPER_PORT, STEPER_MOTOR_YELLOW_COIL, DIO_u8_LOW);
				DIO_u8SetPinValue(STEPER_PORT, STEPER_MOTOR_ORANGE_COIL, DIO_u8_HIGH);
				_delay_ms(2);
				DIO_u8SetPinValue(STEPER_PORT, STEPER_MOTOR_BLUE_COIL, DIO_u8_HIGH);
				DIO_u8SetPinValue(STEPER_PORT, STEPER_MOTOR_PINK_COIL, DIO_u8_HIGH);
				DIO_u8SetPinValue(STEPER_PORT, STEPER_MOTOR_YELLOW_COIL, DIO_u8_HIGH);
				DIO_u8SetPinValue(STEPER_PORT, STEPER_MOTOR_ORANGE_COIL, DIO_u8_LOW);
				_delay_ms(2);
				
			}// end loop 
		}// end Clockwise CASE 
		
		// 1.2- In CASE the direction is Counter Clockwise
		else if (Copy_u8Direction == CCW){
			for(Local_u16IndexCounter ; Local_u16IndexCounter < Local_u32NumberOfSteps ; Local_u16IndexCounter++){
				
				DIO_u8SetPinValue(STEPER_PORT, STEPER_MOTOR_BLUE_COIL, DIO_u8_HIGH);
				DIO_u8SetPinValue(STEPER_PORT, STEPER_MOTOR_PINK_COIL, DIO_u8_HIGH);
				DIO_u8SetPinValue(STEPER_PORT, STEPER_MOTOR_YELLOW_COIL, DIO_u8_HIGH);
				DIO_u8SetPinValue(STEPER_PORT, STEPER_MOTOR_ORANGE_COIL, DIO_u8_LOW);
				_delay_ms(2);
				DIO_u8SetPinValue(STEPER_PORT, STEPER_MOTOR_BLUE_COIL, DIO_u8_HIGH);
				DIO_u8SetPinValue(STEPER_PORT, STEPER_MOTOR_PINK_COIL, DIO_u8_HIGH);
				DIO_u8SetPinValue(STEPER_PORT, STEPER_MOTOR_YELLOW_COIL, DIO_u8_LOW);
				DIO_u8SetPinValue(STEPER_PORT, STEPER_MOTOR_ORANGE_COIL, DIO_u8_HIGH);
				_delay_ms(2);
				DIO_u8SetPinValue(STEPER_PORT, STEPER_MOTOR_BLUE_COIL, DIO_u8_HIGH);
				DIO_u8SetPinValue(STEPER_PORT, STEPER_MOTOR_PINK_COIL, DIO_u8_LOW);
				DIO_u8SetPinValue(STEPER_PORT, STEPER_MOTOR_YELLOW_COIL, DIO_u8_HIGH);
				DIO_u8SetPinValue(STEPER_PORT, STEPER_MOTOR_ORANGE_COIL, DIO_u8_HIGH);
				_delay_ms(2);
				DIO_u8SetPinValue(STEPER_PORT, STEPER_MOTOR_BLUE_COIL, DIO_u8_LOW);
				DIO_u8SetPinValue(STEPER_PORT, STEPER_MOTOR_PINK_COIL, DIO_u8_HIGH);
				DIO_u8SetPinValue(STEPER_PORT, STEPER_MOTOR_YELLOW_COIL, DIO_u8_HIGH);
				DIO_u8SetPinValue(STEPER_PORT, STEPER_MOTOR_ORANGE_COIL, DIO_u8_HIGH);
				_delay_ms(2);
				
			}// end loop 
		}// end Counter Clockwise CASE
	}// end NO Errors CASE

	
	// 2- In CASE of Errors
	else {
		Local_u8ErrorState = STD_TYPES_NOK;
	}// end else (CASE of Errors)
		
	return Local_u8ErrorState;   // return error flag 
	
}// end STEPPER_MOTOR_ROTATE function 
