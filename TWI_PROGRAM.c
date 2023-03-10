/*
 * TWI_PROGRAM.c
 *
 * Created: 12/16/2022 7:30:41 PM
 * Author: Mohamed Mousa & Mohamed Ibrahim
 */ 
/*UTILS*/
#include "ATMEGA32_REG.h"
#include "DATA_TYPES.h"
#include "BIT_MATH.h"
/*MCAL*/
#include "TWI_INTERFACE.h"

/**
 * @brief: A function that initialize the master
 * 
 */
void TWI_INIT_MASTER(void)
{
    /*Set the freq = 400 KHz*/
    CLR_BIT(TWSR, TWPS0);
    CLR_BIT(TWSR, TWPS1);
    TWBR = 12;
    /*Enable the Acknowledge Bit*/
    SET_BIT(TWCR, TWEA);
    /*Enable the TWI Prephreral*/
    SET_BIT(TWCR, TWEN);
}

/**
 * @brief: A function that send a start condition (1-Bit)
 * 
 */
void TWI_SEND_START_CONDITION(void)
{
    /*Send Start condition*/
    SET_BIT(TWCR, TWSTA);
    /*Clear the Flag TWINT to start the current job*/
    SET_BIT(TWCR, TWINT);
    /*Wait for the flag*/
    while(0 == GET_BIT(TWCR, TWINT));
    /*Check ACK = Start_Condition ACK*/
    while((TWSR & 0xF8) != 0x08);
}

/**
 * @brief: A function that send a repeated 
 *         start condition (1-Bit)
 * 
 */
void TWI_SEND_REP_START_CONDITION(void)
{
    /*Send Start condition*/
    SET_BIT(TWCR, TWSTA);
    /*Clear the Flag TWINT to start the current job*/
    SET_BIT(TWCR, TWINT);
    /*Wait for the flag*/
    while(0 == GET_BIT(TWCR, TWINT));
    /*Check ACK = Repeated_Start_Condition ACK*/
    while((TWSR & 0xF8) != 0x10);
}


/**
 * @brief: A function that send a stop condition (1-Bit)
 * 
 */
void TWI_SEND_STOP_CONDITION(void)
{
    /*Send Stop Condition*/
    SET_BIT(TWCR, TWSTO);
    /*Clear the Flag TWINT to start the current job*/
    SET_BIT(TWCR, TWINT);
}

/**
 * @brief: A function that send the slave address with write condition
 * 
 * @param Slave_Address: The address of the slave
 */
void TWI_SEND_SLAVE_ADDRESS_WITH_WRITE(u8 Slave_Address)
{
    if(Slave_Address < 128)
    {
        /*Write the slave address in the TWDR REG (Data_REG)*/
        TWDR = Slave_Address << 1;
        /*Select Wirte operation*/
        CLR_BIT(TWDR, TWD0);
        /*Clear the Start Condition Bit*/
        CLR_BIT(TWCR, TWSTA);
        /*Clear the Flag TWINT to start the current job*/
        SET_BIT(TWCR, TWEN);/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        SET_BIT(TWCR, TWINT);
        /*Wait for the flag*/
        while(0 == GET_BIT(TWCR, TWINT));
        /*Check ACK = Slave_Address_Write_OP ACK*/
        while((TWSR & 0xF8) != 0x18);

    }
    else
    {
        /*Do_Nothing*/
    }
}

/**
 * @brief: A function that send the slave address with read condition
 * 
 * @param Slave_Address: The address of the slave
 */
void TWI_SEND_SLAVE_ADDRESS_WITH_READ(u8 Slave_Address)
{
    if(Slave_Address < 128)
    {
        /*Write the slave address in the TWDR REG (Data_REG)*/
        TWDR = Slave_Address << 1;
        /*Select Read operation*/
        SET_BIT(TWDR, TWD0);
        /*Clear the Start Condition Bit*/
        CLR_BIT(TWCR, TWSTA);//////////////////////////////////////////////////////////////////////////////////////////////////////
        /*Clear the Flag TWINT to start the current job*/
        SET_BIT(TWCR, TWEN);////////////////////////////////////////////////////////////////////////////////////////////////////////
        SET_BIT(TWCR, TWINT);
        /*Wait for the flag*/
        while(0 == GET_BIT(TWCR, TWINT));
        /*Check ACK = Slave_Address_Read_OP ACK*/
        while((TWSR & 0xF8) != 0x40);

    }
    else
    {
        /*Do_Nothing*/
    }
}

/**
 * @brief: A function that send the data to the slaves
 * 
 * @param Data: The data to be sent
 */
void TWI_SEND_MASTER_BYTE_DATA(u8 Data)
{
    /*Send the data*/
    TWDR = Data;
    /*Clear the Flag TWINT to start the current job*/
    SET_BIT(TWCR, TWEN);/////////////////////////////////////////////////////////////////////////////////////////////////////////
    SET_BIT(TWCR, TWINT);
    /*Wait for the flag*/
    while(0 == GET_BIT(TWCR, TWINT));
    /*Check ACK = Master_Sent_Data ACK*/
    while((TWSR & 0xF8) != 0x28);
}

/**
 * @brief: A function that read the data from the slaves
 * 
 * @param Data: The data to be read
 */
void TWI_Read_MASTER_BYTE_DATA(u8* Returned_Data)
{
    if(Returned_Data != NULL)
    {
        /*TO CHECK THE RECIEVE -> Clear the flag first*/
        /*Clear the Flag TWINT to start the current job*/
        
        //SET_BIT(TWCR, TWEN);///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //SET_BIT(TWCR, TWEA);////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //SET_BIT(TWCR, TWINT);
        TWCR = (1 << TWINT) | (1 << TWEN);
        /*Wait for the flag*/
        while(0 == GET_BIT(TWCR, TWINT));
        /*Check ACK = Master_Sent_Data NACK*/
        while((TWSR & 0xF8) != 0x58);
        /*Read Data*/
        *Returned_Data = TWDR;

    }
    else
    {
        /*Do_Nothing*/
    }
}
