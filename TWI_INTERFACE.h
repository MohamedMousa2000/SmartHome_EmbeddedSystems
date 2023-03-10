/*
 * TWI_INTERFACE.h
 *
 * Created: 12/16/2022 7:30:57 PM
 * Author: Mohamed Mousa & Mohamed Ibrahim
 */ 


#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

/*TWCR Register*/
enum {TWIE, TWEN = 2, TWWC, TWSTO, TWSTA, TWEA, TWINT};

/*TWSR Register*/
enum {TWPS0, TWPS1};

/*TWDR Register*/
enum {TWD0};

/*TWAR Register*/
enum {TWGCE};

/**
 * @brief: A function that initialize the master
 * 
 */
void TWI_INIT_MASTER(void);

/**
 * @brief: A function that send a start condition (1-Bit)
 * 
 */
void TWI_SEND_START_CONDITION(void);

/**
 * @brief: A function that send a repeated 
 *         start condition (1-Bit)
 * 
 */
void TWI_SEND_REP_START_CONDITION(void);


/**
 * @brief: A function that send a stop condition (1-Bit)
 * 
 */
void TWI_SEND_STOP_CONDITION(void);

/**
 * @brief: A function that send the slave address with write condition
 * 
 * @param Slave_Address: The address of the slave
 */
void TWI_SEND_SLAVE_ADDRESS_WITH_WRITE(u8 Slave_Address);

/**
 * @brief: A function that send the slave address with read condition
 * 
 * @param Slave_Address: The address of the slave
 */
void TWI_SEND_SLAVE_ADDRESS_WITH_READ(u8 Slave_Address);

/**
 * @brief: A function that send the data to the slaves
 * 
 * @param Data: The data to be sent to the slave
 */
void TWI_SEND_MASTER_BYTE_DATA(u8 Data);

/**
 * @brief: A function that read the data from the slaves
 * 
 * @param Returned_Data: The data to be read from the slave
 */
void TWI_Read_MASTER_BYTE_DATA(u8* Returned_Data);


#endif /* TWI_INTERFACE_H_ */