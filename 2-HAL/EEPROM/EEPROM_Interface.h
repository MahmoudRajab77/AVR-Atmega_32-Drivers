/**************************************/
/******* Name   : Mahmoud Rajab *******/
/******* Date   :  17/10/2020   *******/
/******* Update :            	*******/
/******* SWC    :    EEPROM     *******/
/******* Version:     1.0       *******/
/**************************************/

#ifndef EEPROM_INTERFACE_H
#define EEPROM_INTERFACE_H


void EEPROM_voidInit(void);

u8 EEPROM_u8WriteDataByte(u8 Copy_u8Data, u16 Copy_u16ByteAddrs);

u8 EEPROM_u8ReadDataByte(u8* Copy_pu8Data, u16 Copy_u16ByteAddrs);


#endif