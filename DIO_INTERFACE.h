/*
 * DIO_INTERFACE.h
 *
 * Created: 10/22/2022 11:08:41 PM
 * Author: Mohamed Mousa & Mohamed Ibrahim
 */ 
#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#include "DATA_TYPES.h"

#define DIO_PORTA      0
#define DIO_PORTB      1
#define DIO_PORTC      2
#define DIO_PORTD      3

#define DIO_PIN_INPUT   0
#define DIO_PIN_OUTPUT  1

#define DIO_PIN_LOW   0
#define DIO_PIN_HIGH  1

#define DIO_PIN0       0
#define DIO_PIN1       1
#define DIO_PIN2       2
#define DIO_PIN3       3
#define DIO_PIN4       4
#define DIO_PIN5       5
#define DIO_PIN6       6
#define DIO_PIN7       7

/**
 * @brief: A function that set the direction of the pin either (1  or  0)
 *                                                             (OUT / IN)
 * 
 * @param PortID: Port Number
 * @param PinID : Pin Number 
 * @param PinDir: Pin Direction
 */
void DIO_SET_PIN_DIR(u8 PortID, u8 PinID, u8 PinDir);

/**
 * @brief: A function that choose the value of the pin either SET (1) Or CLR (0)
 * 
 * @param PortID: Port Number
 * @param PinID : Pin Number
 * @param PinVal: Pin Value
 */
void DIO_SET_PIN_VAL(u8 PortID, u8 PinID, u8 PinVal);

/**
 * @brief: A function that return the value of a specific pin in a specific port
 * 
 * @param PortID: Port Number
 * @param PinID : Pin Number 
 * @return u8   : unsigned Char
 */
u8 DIO_GET_PIN_VAL(u8 PortID, u8 PinID);

/**
 * @brief: A function that toggle a specific bit in a specific port
 * 
 * @param PortID: Port Number
 * @param PinID : Pin Number
 */
void DIO_TOG_PIN_VAL(u8 PortID, u8 PinID);

/**
 * @brief: A function that activate the pull up resistor on a specific pin in a specific port
 * 
 * @param PortID: Port Number
 * @param PinID : Pin Number
 */
void DIO_ACTIVATE_PULL_UP(u8 PortID, u8 PinID);


#endif /* DIO_INTERFACE_H_ */