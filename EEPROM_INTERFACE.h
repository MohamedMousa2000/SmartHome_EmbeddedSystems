/*
 * EEPROM_INTERFACE.h
 *
 * Created: 12/16/2022 10:18:58 PM
 * Author: Mohamed Mousa & Mohamed Ibrahim
 */ 


#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

#define EEPROM_FIXED_ADDRESS 0x50

/**
 * @brief: A function that take the address of the byte, divide it,
 *         Assign it into the frame for the I2C communication
 *         and write the data
 * 
 * @param Byte_Address: The Byte address we want to access in EEPROM
 * @param Data        : The data to be written in the Byte 
 */
void EEPROM_WRITE_BYTE(u16 Byte_Address, u8 Data);

/**
 * @brief: A function that take the address of the byte, divide it,
 *         Assign it into the frame for the I2C communication
 *         and read the data 
 * 
 * @param Byte_Address: The Byte address we want to access in EEPROM  
 * @param Data        : The data to be written in the Byte   
 */ 
void EEPROM_READ_BYTE(u16 Byte_Address, u8* Data);

#endif /* EEPROM_INTERFACE_H_ */