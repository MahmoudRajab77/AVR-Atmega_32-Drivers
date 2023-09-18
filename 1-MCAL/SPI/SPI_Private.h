/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  10/10/2020   *******/
/******* Update :            	*******/
/******* SWC    :     SPI       *******/
/******* Version:     1.0       *******/
/**************************************/

#ifndef SPI_PRIVATE_H
#define SPI_PRIVATE_H

#define SPI_u8_SPDR_REG				*((volatile u8*)0x2F)
#define SPI_u8_SPSR_REG				*((volatile u8*)0x2E)
#define SPI_u8_SPCR_REG				*((volatile u8*)0x2D)

/* SPI MODES */
#define SPI_u8_MASTER_MODE		1
#define SPI_u8_SLAVE_MODE 		2

#endif