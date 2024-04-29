/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  14/10/2020   *******/
/******* Update :            	*******/
/******* SWC    :     TWI       *******/
/******* Version:     1.0       *******/
/**************************************/

#ifndef TWI_PRIVATE_H
#define TWI_PRIVATE_H

//---------------------< Registers >------------------------

#define TWI_u8_TWDR_REG		*((volatile u8*)0x23)		// data register 
#define TWI_u8_TWAR_REG		*((volatile u8*)0x22)		// Adress Register
#define TWI_u8_TWSR_REG		*((volatile u8*)0x21)		// status Register
#define TWI_u8_TWBR_REG		*((volatile u8*)0x20)		// Bit Rate Register
#define TWI_u8_TWCR_REG		*((volatile u8*)0x56)		// Control Register

//---------------------< Status Codes >----------------------------------------------------

#define START_COND			0x08
#define RE_START_COND		0x10

#define SLA_W_OK			0x18
#define SLA_W_NOK			0x20

#define DATA_SENT_OK		0x28
#define DATA_SENT_NOK		0x30

#define SLA_R_OK			0x40
#define SLA_R_NOK			0x48

#define DATA_RECV_OK		0x50
#define DATA_RECV_NOK		0x58	

#define BUS_LOST			0x38

#endif 
