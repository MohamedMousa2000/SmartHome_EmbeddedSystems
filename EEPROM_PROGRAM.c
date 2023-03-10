/*
 * EEPROM_PROGRAM.c
 *
 * Created: 12/16/2022 10:18:39 PM
 * Author: Mohamed Mousa & Mohamed Ibrahim
 */ 
#define F_CPU 16000000UL
#include <util/delay.h>
/*UTILS*/
#include "ATMEGA32_REG.h"
#include "DATA_TYPES.h"
#include "BIT_MATH.h"
/*MCAL*/
#include "DIO_INTERFACE.h"
#include "TWI_INTERFACE.h"
/*HAL*/
#include "EEPROM_INTERFACE.h"

/**
 * @brief: A function that take the address of the byte, divide it,
 *         Assign it into the frame for the I2C communication
 *         and write the data
 * 
 * @param Byte_Address: The Byte address we want to access in EEPROM
 * @param Data        : The data to be written in the Byte 
 */
void EEPROM_WRITE_BYTE(u16 Byte_Address, u8 Data)
{
    u8 Address = (u8)((EEPROM_FIXED_ADDRESS) | (u8)(Byte_Address >> 8));
    /*Send Start Condition*/
    TWI_SEND_START_CONDITION();
    /*Send Slave address with write operation*/
    TWI_SEND_SLAVE_ADDRESS_WITH_WRITE(Address);
    /*Send Byte Address*/
    TWI_SEND_MASTER_BYTE_DATA((u8)Byte_Address);
    /*Send Data (1-Byte)*/
    TWI_SEND_MASTER_BYTE_DATA(Data);
    /*Send Stop Condition*/
    TWI_SEND_STOP_CONDITION();
    /*Delay*/
    _delay_ms(5);
}

/**
 * @brief: A function that take the address of the byte, divide it,
 *         Assign it into the frame for the I2C communication
 *         and read the data 
 * 
 * @param Byte_Address: The Byte address we want to access in EEPROM  
 * @param Data        : The data to be written in the Byte   
 */ 
void EEPROM_READ_BYTE(u16 Byte_Address, u8* Returned_Data)
{
    u8 Address = (u8)((EEPROM_FIXED_ADDRESS) | (u8)(Byte_Address >> 8));
    /*Send Start Condition*/
    TWI_SEND_START_CONDITION();
    /*Send Slave address with write operation*/
    TWI_SEND_SLAVE_ADDRESS_WITH_WRITE(Address);
    /*Send Byte Address*/
    TWI_SEND_MASTER_BYTE_DATA((u8)Byte_Address);
    /*Send Repeated start*/
    TWI_SEND_REP_START_CONDITION();
    /*Send Slave address with read operation*/
    TWI_SEND_SLAVE_ADDRESS_WITH_READ(Address);
    /*Read Byte*/
    TWI_Read_MASTER_BYTE_DATA(Returned_Data);
    /*Send Stop Condition*/
    TWI_SEND_STOP_CONDITION();
    /*Delay*/
    _delay_ms(5);
}

