/*
 * RELAY_program.c
 *
 *  Created on: Feb 3, 2023
 *  Author: Mohamed Mousa & Mohamed Ibrahim
 */


/* UTILES_LIB */
#include "DATA_TYPES.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

/* MCAL */
#include "DIO_INTERFACE.h"

/* HAL */
#include "RELAY_interface.h"

/**
 * @brief: A function that initialize the relay pin
 * 
 */
void RELAY_init(void)
{
    DIO_SET_PIN_DIR(DIO_PORTA, DIO_PIN2, DIO_PIN_OUTPUT);
}

/**
 * @brief: A function that turn on the relay through its DIO pin
 * 
 */
void RELAY_on  (void)
{
    DIO_SET_PIN_VAL(DIO_PORTA, DIO_PIN2, DIO_PIN_HIGH);
}

/**
 * @brief: A function that turn off the relay through its DIO pin
 * 
 */
void RELAY_off (void)
{
    DIO_SET_PIN_VAL(DIO_PORTA, DIO_PIN2, DIO_PIN_LOW);
}