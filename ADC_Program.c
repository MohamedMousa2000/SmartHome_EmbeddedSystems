/*
 * ADC_Program.c
 *
 * Created: 11/11/2022 9:47:14 PM
 * Author: Mohamed Mousa & Mohamed Ibrahim
 */ 

/* UTILES LIB */
#include "ATMEGA32_REG.h"
#include "DATA_TYPES.h"
#include "BIT_MATH.h"
/* MCAL */
#include "ADC_INTERFACE.h"

/**
 * @brief: A function that Intialize the ADC
 * 
 */
void ADC_INIT(void)
{
    /* Select Vref = AVCC */
    SET_BIT(ADMUX, 6);
    CLR_BIT(ADMUX, 7);

    /* Select the Adjustment = R */
    CLR_BIT(ADMUX, 5);

    /* Select Single Conversion Mode */
    CLR_BIT(ADCSRA, 5);

    /* Select Prescaler value = 128 */
    SET_BIT(ADCSRA, 0);
    SET_BIT(ADCSRA, 1);
    SET_BIT(ADCSRA, 2);

    /* Enable The ADC */
    SET_BIT(ADCSRA, 7);

}

/**
 * @brief: A function that takes the channel number and the address 
 *         of the variable which we will return in it the converged
 *         value
 * 
 * @param Channel_Num: Channel Number in MUX 
 * @param Digital_Val: Pointer to unsigned 16 in which we will assign 
 *                     the digital value
 */
void ADC_GET_DIGITAL_VAL(u8 Channel_Num, u16* Digital_Val)
{
    if((Channel_Num < 32) && (Digital_Val != NULL))
    {
        /* Ensure that the first 5 Bits are zero */
        ADMUX &= 0b11100000;
        /* Select the Channel Number */
        ADMUX |= Channel_Num;
        /* Start Conversion */
        SET_BIT(ADCSRA, 6);

        /* Wait for the flag of ADC */
        while(GET_BIT(ADCSRA, 4) == 0);

        /* Clear Flag */
        SET_BIT(ADCSRA, 4);

        /* Read Digital Value */
        *Digital_Val = ADC_U16;
    }
}

