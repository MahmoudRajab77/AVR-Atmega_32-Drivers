/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  28/8/2020    *******/
/******* SWC    :    KPD        *******/
/******* Version:    1.0        *******/
/**************************************/

/* LIB layer */
#include"STD_TYPES.h"
#include"STD_MATH.h"
#define  F_CPU 	 8000000UL
#include <util/delay.h>

/* MCAL */
#include"DIO_interface.h"

/* HAL */
#include "KPD_interface.h"
#include"KPD_private.h"
#include"KPD_config.h"

static KPD_Au8Keys[4][4]= {
	{'1', '2', '3', '+'}, 
	{'4', '5', '6', '-'},
	{'7', '8', '9', '*'},
	{'0', '=', '%', '/'}
};

//static to not be accessed outside this file 
static u8 KPD_Au8RowsPins[4]={KPD_u8_R1_PIN, KPD_u8_R2_PIN, KPD_u8_R3_PIN, KPD_u8_R4_PIN};
static u8 KPD_Au8ColsPins[4]={KPD_u8_C1_PIN, KPD_u8_C2_PIN, KPD_u8_C3_PIN, KPD_u8_C4_PIN};

//this function returns with 2 things : 1- error state  2- the pushed key( via pointer ) 
/* ROWs output  and COLs input */
u8 KPD_u8GetKey(u8 * Copy_pu8ReturnedKey)
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	u8 Local_u8RowsCounter, Local_u8ColsCounter, Local_u8ReturnedPinValue;
	/* check pointer validation */
	if (Copy_pu8ReturnedKey != NULL)
	{
		for(Local_u8RowsCounter = 0; Local_u8RowsCounter<=3; Local_u8RowsCounter++)
		{
			DIO_u8SetPinValue(KPD_u8_PORT, KPD_Au8RowsPins[Local_u8RowsCounter], DIO_u8_LOW);
			/* Read Cols */
			for(Local_u8ColsCounter = 4; Local_u8ColsCounter <= 7; Local_u8ColsCounter++)
			{
				DIO_u8GetPinValue(KPD_u8_PORT, KPD_Au8ColsPins[Local_u8ColsCounter], &Local_u8ReturnedPinValue);
				/*check switch is pressed */
				if(Local_u8ReturnedPinValue == DIO_u8_LOW)
				{
					/*Debouncing */
					_delay_ms(20);
					while (Local_u8ReturnedPinValue == DIO_u8_LOW)
					{
						DIO_u8GetPinValue(KPD_u8_PORT, KPD_Au8ColsPins[Local_u8ColsCounter], &Local_u8ReturnedPinValue);
					}//end while
					
					*Copy_pu8ReturnedKey = 	KPD_Au8Keys[Local_u8RowsCounter][Local_u8ColsCounter];
					
				}//end if the switch was pressed		
			}//end nested for which read cols	
		}//end for that loops on Rows 
		
	}//end if that check pointer validation
	else 
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}		
	
	return Local_u8ErrorState;
}