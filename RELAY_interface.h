/*
 * RELAY_interface.h
 *
 *  Created on: Feb 3, 2023
 *  Author: Mohamed Mousa & Mohamed Ibrahim
 */

#ifndef RELAY_INTERFACE_H_
#define RELAY_INTERFACE_H_

/**
 * @brief: A function that initialize the relay pin
 * 
 */
void RELAY_init(void);

/**
 * @brief: A function that turn on the relay through its DIO pin
 * 
 */
void RELAY_on  (void);

/**
 * @brief: A function that turn off the relay through its DIO pin
 * 
 */
void RELAY_off (void);


#endif /* RELAY_INTERFACE_H_ */
