/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  09/09/2020   *******/
/******* SWC    : STEPPER_MOTOR *******/
/******* Version:    1.0        *******/
/**************************************/

#ifndef 	STEPPER_CONFIG_H
#define 	STEPPER_CONFIG_H


#define  STEP_STRIDE_ANGLE     0.0878

/* PORT configuration */
#define   STEPPER_PORT		DIO_u8_PORTA

/* PIN configuration for Motor */
#define   STEPPER_MOTOR_BLUE_COIL		DIO_u8PIN0
#define   STEPPER_MOTOR_PINK_COIL		DIO_u8PIN1
#define   STEPPER_MOTOR_YELLOW_COIL		DIO_u8PIN2
#define   STEPPER_MOTOR_ORANGE_COIL		DIO_u8PIN3


#endif 