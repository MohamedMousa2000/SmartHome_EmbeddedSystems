/*
 * GI_Program.c
 *
 * Created: 11/12/2022 10:49:35 PM
 * Author: Mohamed Mousa & Mohamed Ibrahim
 */ 
/* UTILS LIBS */
#include "ATMEGA32_REG.h"
#include "DATA_TYPES.h"
#include "BIT_MATH.h"
/* MCAL */
#include "GI_INTERFACE.h"

/**
 * @brief: A function that Enable the global interrupt in SREG register
 * 
 */
void GI_ENABLE(void)
{
    SET_BIT(SREG, 7);
}

/**
 * @brief: A function that Disable the global interrupt in SREG register
 * 
 */
void GI_DISABLE(void)
{
    CLR_BIT(SREG, 7);
}
