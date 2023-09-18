/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  25/8/2020    *******/
/******* SWC    :    DIO        *******/
/******* Version:    1.0        *******/
/**************************************/

/* lib layer */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_interface.h" 
#include "DIO_private.h"
#include "DIO_config.h"

//------------------------------------------< SetPinDirection Function >-----------------------------------------

u8 DIO_u8SetPinDirection(u8 Copy_u8PortId, u8 Copy_u8PinId, u8 Copy_u8PinDirection)
{
	u8 Local_u8ReturnedState = STD_TYPES_OK;
	/* Check 1- Valid Port ID 
			 2- Valid Pin ID 
			 3- Valid Pin Direction */
			 
	if ((Copy_u8PortId <= DIO_u8_PORTD) &&(Copy_u8PinId <= DIO_u8PIN7) && ((Copy_u8PinDirection == DIO_u8_INPUT) || (Copy_u8PinDirection == DIO_u8_OUTPUT)) )
	{
		switch (Copy_u8PortId)
		{
			case DIO_u8_PORTA:
			switch(Copy_u8PinDirection)
			{
				case DIO_u8_OUTPUT:
				SET_BIT(DDRA_u8_REG, Copy_u8PinId);
				break;
				case DIO_u8_INPUT:
				CLR_BIT(DDRA_u8_REG, Copy_u8PinId);
				break;
			}//end switch PORTA
			break;//end of case PORTA
			
			//case PORTB
			case DIO_u8_PORTB:
			switch(Copy_u8PinDirection)
			{
				case DIO_u8_OUTPUT:
				SET_BIT(DDRB_u8_REG, Copy_u8PinId);
				break;
				case DIO_u8_INPUT:
				CLR_BIT(DDRB_u8_REG, Copy_u8PinId);
				break;
			}//end switch PORTB	
			break;//end case PORTB
			
			//case PORTC
			case DIO_u8_PORTC:
			switch(Copy_u8PinDirection)
			{
				case DIO_u8_OUTPUT:
				SET_BIT(DDRC_u8_REG, Copy_u8PinId);
				break;
				case DIO_u8_INPUT:
				CLR_BIT(DDRC_u8_REG, Copy_u8PinId);
				break;
			}//end switch PORTC
			break;//end of case PORTA
			
			//case PORTD
			case DIO_u8_PORTD:
			switch(Copy_u8PinDirection)
			{
				case DIO_u8_OUTPUT:
				SET_BIT(DDRD_u8_REG, Copy_u8PinId);
				break;
				case DIO_u8_INPUT:
				CLR_BIT(DDRD_u8_REG, Copy_u8PinId);
				break;
			}//end switch PORTD
			break;//end of case PORTD
		
		}//end switch 
	}//end if 
	else 
	{
		Local_u8ReturnedState = STD_TYPES_NOK;	
	} 		
    return Local_u8ReturnedState;	
}//end SetPinDirection function 

//------------------------------------------< SetPinValue Function >-----------------------------------------

u8 DIO_u8SetPinValue(u8 Copy_u8PortId, u8 Copy_u8PinId, u8 Copy_u8PinValue)
{
	u8 Local_u8ReturnedState = STD_TYPES_OK;
	if ((Copy_u8PortId <= DIO_u8_PORTD) &&(Copy_u8PinId <= DIO_u8PIN7) && ((Copy_u8PinValue == DIO_u8_HIGH) || (Copy_u8PinValue == DIO_u8_LOW)))
	{
		switch (Copy_u8PortId)
		{
			//case PORTA
			case DIO_u8_PORTA:
				switch (Copy_u8PinValue)
				{
					case DIO_u8_HIGH:
						SET_BIT(PORTA_u8_REG, Copy_u8PinId);
					break;
					
					case DIO_u8_LOW:
						CLR_BIT(PORTA_u8_REG, Copy_u8PinId);
					break;
				}//end switch PORTA
			break;//end of case PORTA

			//case PORTB
			case DIO_u8_PORTB:
				switch (Copy_u8PinValue)
				{
					case DIO_u8_HIGH:
						SET_BIT(PORTB_u8_REG, Copy_u8PinId);
					break;
					
					case DIO_u8_LOW:
						CLR_BIT(PORTB_u8_REG, Copy_u8PinId);
					break;
				}//end switch PORTB
			break;//end of case	PORTB
			
			//case PORTC
			case DIO_u8_PORTC:
				switch (Copy_u8PinValue)
				{
					case DIO_u8_HIGH:
						SET_BIT(PORTC_u8_REG, Copy_u8PinId);
					break;
					
					case DIO_u8_LOW:
						CLR_BIT(PORTC_u8_REG, Copy_u8PinId);
					break;
				}//end switch PORTC
			break;//end of case PORTC
			
			//case PORTD
			case DIO_u8_PORTD:
				switch (Copy_u8PinValue)
				{
					case DIO_u8_HIGH:
						SET_BIT(PORTD_u8_REG, Copy_u8PinId);
					break;
					
					case DIO_u8_LOW:
						CLR_BIT(PORTD_u8_REG, Copy_u8PinId);
					break;
				}//end switch PORTD
			break;//end of case PORTD
			
		}//end switch 
	}//end if 
	else 
	{
		Local_u8ReturnedState = STD_TYPES_NOK;
	}	
	return Local_u8ReturnedState;
}//end SetPinValue function

//------------------------------------------< GetPinValue Function >-----------------------------------------

u8 DIO_u8GetPinValue(u8 Copy_u8PortId, u8 Copy_u8PinId, u8* Copy_pu8ReturnedPinValue)
{
	u8 Local_u8ReturnedState = STD_TYPES_OK;
	if ((Copy_u8PortId <= DIO_u8_PORTD) &&(Copy_u8PinId <= DIO_u8PIN7) && (Copy_pu8ReturnedPinValue != NULL))
	{
	   switch(Copy_u8PortId)
	   {
		   // Case PORTA
		   case DIO_u8_PORTA:
				if (GET_BIT(PINA_u8_REG, Copy_u8PinId) == 0)
				{
					*Copy_pu8ReturnedPinValue = DIO_u8_LOW;
				}
				else if (GET_BIT(PINA_u8_REG, Copy_u8PinId) != 0)
				{
					*Copy_pu8ReturnedPinValue = DIO_u8_HIGH;
				}		
		   break;//end case PORTA
		   
		   // case PORTB
		   case DIO_u8_PORTB:
				if (GET_BIT(PINB_u8_REG, Copy_u8PinId) == 0)
				{
					*Copy_pu8ReturnedPinValue = DIO_u8_LOW;
				}
				else if (GET_BIT(PINB_u8_REG, Copy_u8PinId) != 0)
				{
					*Copy_pu8ReturnedPinValue = DIO_u8_HIGH;
				}
		   break;//end case PORTB
		   
		   //case PORTC
		   case DIO_u8_PORTC:
				if (GET_BIT(PINC_u8_REG, Copy_u8PinId) == 0)
				{
					*Copy_pu8ReturnedPinValue = DIO_u8_LOW;
				}
				else if (GET_BIT(PINC_u8_REG, Copy_u8PinId) != 0)
				{
					*Copy_pu8ReturnedPinValue = DIO_u8_HIGH;
				}
		   break;//end case PORTC
		   
		   //case PORTD
		   case DIO_u8_PORTD:
				if (GET_BIT(PIND_u8_REG, Copy_u8PinId) == 0)
				{
					*Copy_pu8ReturnedPinValue = DIO_u8_LOW;
				}
				else if (GET_BIT(PIND_u8_REG, Copy_u8PinId) != 0)
				{
					*Copy_pu8ReturnedPinValue = DIO_u8_HIGH;
				}
		   break;//end case PORTD
	   }//end switch 
	
	}//end if 
	else 
	{
		Local_u8ReturnedState = STD_TYPES_NOK;
	}
	return Local_u8ReturnedState;
}//end GetPinValue function 

//------------------------------------------< SetPortDirection Function >-----------------------------------------

u8 DIO_u8SetPortDirection(u8 Copy_u8PortId, u8 Copy_u8PortDirection)
{
	u8 Local_u8ReturnedState = STD_TYPES_OK;
	if ((Copy_u8PortId <= DIO_u8_PORTD) && ((Copy_u8PortDirection == DIO_u8_INPUT) || (Copy_u8PortDirection == DIO_u8_OUTPUT)))
	{
		switch (Copy_u8PortId)
		{
			//case PORTA
			case DIO_u8_PORTA:
				switch (Copy_u8PortDirection)
				{
					case DIO_u8_INPUT:
						DDRA_u8_REG = 0x00;
					break;
					
					case DIO_u8_OUTPUT:
						DDRA_u8_REG = 0xFF;
					break;	
				}//end switch for 'PORTA' Direction 				
			break;//end case PORTA
			
			//case PORTB
			case DIO_u8_PORTB:
				switch (Copy_u8PortDirection)
				{
					case DIO_u8_INPUT:
						DDRB_u8_REG = 0x00;
					break;
					
					case DIO_u8_OUTPUT:
						DDRB_u8_REG = 0xFF;
					break;	
				}//end switch for 'PORTB' Direction 				
			break;//end case PORTB
			
			//case PORTC
			case DIO_u8_PORTC:
				switch (Copy_u8PortDirection)
				{
					case DIO_u8_INPUT:
						DDRC_u8_REG = 0x00;
					break;
					
					case DIO_u8_OUTPUT:
						DDRC_u8_REG = 0xFF;
					break;	
				}//end switch for 'PORTC' Direction 				
			break;//end case PORTC
			
			//case PORTD
			case DIO_u8_PORTD:
				switch (Copy_u8PortDirection)
				{
					case DIO_u8_INPUT:
						DDRD_u8_REG = 0x00;
					break;
					
					case DIO_u8_OUTPUT:
						DDRD_u8_REG = 0xFF;
					break;	
				}//end switch for 'PORTD' Direction 				
			break;//end case PORTD
			
		}//end switch for the PORT
	}
	else 
	{
		Local_u8ReturnedState = STD_TYPES_NOK;
	}	
	return Local_u8ReturnedState;
	
}//end SetPortDirection function

//------------------------------------------< SetPortValue Function >-----------------------------------------

u8 DIO_u8SetPortValue(u8 Copy_u8PortId, u8 Copy_u8PortValue)
{
	u8 Local_u8ReturnedState = STD_TYPES_OK;
	switch (Copy_u8PortId)
	{
		case DIO_u8_PORTA:
			PORTA_u8_REG = Copy_u8PortValue;
		break;

		case DIO_u8_PORTB:
			PORTB_u8_REG = Copy_u8PortValue;
		break;
		
		case DIO_u8_PORTC:
			PORTC_u8_REG = Copy_u8PortValue;
		break;
		
		case DIO_u8_PORTD:
			PORTD_u8_REG = Copy_u8PortValue;
		break;
		default:
			Local_u8ReturnedState = STD_TYPES_NOK;
			
	}//end switch for PORT
	return Local_u8ReturnedState;
}//end SetPortValue dunction 

//------------------------------------------< GetPortValue Function >-----------------------------------------

u8 DIO_u8GetPortValue(u8 Copy_u8PortId, u8* Copy_pu8ReturnedPortValue)
{
	u8 Local_u8ReturnedState = STD_TYPES_OK;
	if (Copy_pu8ReturnedPortValue != NULL)
	{
		switch (Copy_u8PortId)
	{
		case DIO_u8_PORTA:
	        *Copy_pu8ReturnedPortValue = PINA_u8_REG;
		break;

		case DIO_u8_PORTB:
			*Copy_pu8ReturnedPortValue = PINB_u8_REG;
		break;
		
		case DIO_u8_PORTC:
			*Copy_pu8ReturnedPortValue = PINC_u8_REG;
		break;
		
		case DIO_u8_PORTD:
			*Copy_pu8ReturnedPortValue = PIND_u8_REG;
		break;
		default:
			Local_u8ReturnedState = STD_TYPES_NOK;
			
	}//end switch for PORT
	}
	else 
	{
		Local_u8ReturnedState = STD_TYPES_NOK;
	}	
	return Local_u8ReturnedState;
}//end GetPortValue function 

//------------------------------------------< DIO_Init Function >-----------------------------------------

u8 DIO_u8Init(void)
{
	DDRA_u8_REG = CONC(DIO_u8_PA7_INITIAL_DIRECTION, DIO_u8_PA6_INITIAL_DIRECTION, DIO_u8_PA5_INITIAL_DIRECTION, 
					   DIO_u8_PA4_INITIAL_DIRECTION, DIO_u8_PA3_INITIAL_DIRECTION, DIO_u8_PA2_INITIAL_DIRECTION, 
					   DIO_u8_PA1_INITIAL_DIRECTION, DIO_u8_PA0_INITIAL_DIRECTION);
	
	DDRB_u8_REG = CONC(DIO_u8_PB7_INITIAL_DIRECTION, DIO_u8_PB6_INITIAL_DIRECTION, DIO_u8_PB5_INITIAL_DIRECTION, 
					   DIO_u8_PB4_INITIAL_DIRECTION, DIO_u8_PB3_INITIAL_DIRECTION, DIO_u8_PB2_INITIAL_DIRECTION, 
					   DIO_u8_PB1_INITIAL_DIRECTION, DIO_u8_PB0_INITIAL_DIRECTION);
	
	DDRC_u8_REG = CONC(DIO_u8_PC7_INITIAL_DIRECTION, DIO_u8_PC6_INITIAL_DIRECTION, DIO_u8_PC5_INITIAL_DIRECTION, 
					   DIO_u8_PC4_INITIAL_DIRECTION, DIO_u8_PC3_INITIAL_DIRECTION, DIO_u8_PC2_INITIAL_DIRECTION, 
					   DIO_u8_PC1_INITIAL_DIRECTION, DIO_u8_PC0_INITIAL_DIRECTION);
					   
	DDRD_u8_REG = CONC(DIO_u8_PD7_INITIAL_DIRECTION, DIO_u8_PD6_INITIAL_DIRECTION, DIO_u8_PD5_INITIAL_DIRECTION, 
					   DIO_u8_PD4_INITIAL_DIRECTION, DIO_u8_PD3_INITIAL_DIRECTION, DIO_u8_PD2_INITIAL_DIRECTION, 
					   DIO_u8_PD1_INITIAL_DIRECTION, DIO_u8_PD0_INITIAL_DIRECTION);
	
	/* Initial values for pins */
	PORTA_u8_REG = CONC(DIO_u8_PA7_INITIAL_VALUE, DIO_u8_PA6_INITIAL_VALUE, DIO_u8_PA5_INITIAL_VALUE, 
					    DIO_u8_PA4_INITIAL_VALUE, DIO_u8_PA3_INITIAL_VALUE, DIO_u8_PA2_INITIAL_VALUE, 
					    DIO_u8_PA1_INITIAL_VALUE, DIO_u8_PA0_INITIAL_VALUE);
	
	PORTB_u8_REG = CONC(DIO_u8_PB7_INITIAL_VALUE, DIO_u8_PB6_INITIAL_VALUE, DIO_u8_PB5_INITIAL_VALUE, 
					    DIO_u8_PB4_INITIAL_VALUE, DIO_u8_PB3_INITIAL_VALUE, DIO_u8_PB2_INITIAL_VALUE, 
					    DIO_u8_PB1_INITIAL_VALUE, DIO_u8_PB0_INITIAL_VALUE);
	
	PORTC_u8_REG = CONC(DIO_u8_PC7_INITIAL_VALUE, DIO_u8_PC6_INITIAL_VALUE, DIO_u8_PC5_INITIAL_VALUE, 
					    DIO_u8_PC4_INITIAL_VALUE, DIO_u8_PC3_INITIAL_VALUE, DIO_u8_PC2_INITIAL_VALUE, 
					    DIO_u8_PC1_INITIAL_VALUE, DIO_u8_PC0_INITIAL_VALUE);
					   
	PORTD_u8_REG = CONC(DIO_u8_PD7_INITIAL_VALUE, DIO_u8_PD6_INITIAL_VALUE, DIO_u8_PD5_INITIAL_VALUE, 
					    DIO_u8_PD4_INITIAL_VALUE, DIO_u8_PD3_INITIAL_VALUE, DIO_u8_PD2_INITIAL_VALUE, 
					    DIO_u8_PD1_INITIAL_VALUE, DIO_u8_PD0_INITIAL_VALUE);
	
}//end DIO_u8Init function 