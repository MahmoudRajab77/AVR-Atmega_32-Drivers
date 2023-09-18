#include "STD_TYPES.h"
#include "BIT_MATH.h"

#define F_CPU 	8000000UL

#include <util/delay.h>

#include "DIO_Interface.h"
#include "SPI_Interface.h"


int main (void)
{
	u8 Local_u8Data;
	DIO_u8Init();
	SPI_u8Init(); // Make sure you have selected the master mode
	
	while (1)
	{
		SPI_u8TxRx('a', &Local_u8Data);
		if (Local_u8Data == 10)
		{
			/* Turn on LED */
			DIO_u8SetPinValue(DIO_u8_PORTA, DIO_u8_PIN0, DIO_u8_HIGH);
		}	
		_delay_ms(200); //initiate comm with slave every 200 ms
	}	
	return 0;
}