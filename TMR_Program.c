/*
 * TMR_Program.c
 *
 * Created: 11/12/2022 10:15:07 PM
 * Author: Mohamed Mousa & Mohamed Ibrahim
 */ 

/* UTILS LIBS */
#include "ATMEGA32_REG.h"
#include "DATA_TYPES.h"
#include "BIT_MATH.h"
/* MCAL */
#include "TMR_CONFIG.h"
#include "TMR_INTERFACE.h"


                /**** TIMER -> 0  ****/

static void (*TIMER0_CTC_pCALLBACK)(void) = NULL;

/**
 * @brief: A function that initialize Timer 0
 * 
 */
void TMR_TIMER0_INIT(void)
{
    #if TMR_TIMER0_MODE == TMR_TIMER0_NORMAL_MODE

        /* Select Mode = Normal Mode */
        CLR_BIT(TCCR0, 3);
        CLR_BIT(TCCR0, 6);

        /* Select Preload Value (We are building this because we want one second counter) */
        TCNT0 = TMR_TIMER0_PRELOAD_VAL;

        /* Enable The Overflow Interrupt */
        SET_BIT(TIMSK, 0);

    #elif TMR_TIMER0_MODE == TMR_TIMER0_CTC_MODE

        /* Select Mode = CTC Mode */
        SET_BIT(TCCR0, 3);
        CLR_BIT(TCCR0, 6);

        /* Enable The Compare Match Interrupt */
        SET_BIT(TIMSK, 1);

    #elif TMR_TIMER0_MODE == TMR_TIMER0_FAST_PWM_MODE

        /* Select Mode = Fast PWM Mode */
        SET_BIT(TCCR0, 3);
        SET_BIT(TCCR0, 6);

        /* Select Non Inverting Mode */
        CLR_BIT(TCCR0, 4);
        SET_BIT(TCCR0, 5);

        /* Set OC0 as OUTPUT Pin */
        SET_BIT(DDRB, 3);
    #endif
    /* Select Prescaler = 64 */
    SET_BIT(TCCR0, 0);
    SET_BIT(TCCR0, 1);
    CLR_BIT(TCCR0, 2);
}

/**
 * @brief: A function that set the desired value for timer 0 in the OCR0 REG
 * 
 * @param Value 
 */
void TMR_TIMER0_SET_COMPARE_MATCH_VAL(u8 Compare_Value)
{
    /* Init the OCR0 */
    OCR0 = Compare_Value;
}

/**
 * @brief: Set callback function to CTC Interrupt
 * 
 * @param Ptr: Pointer to function
 */
void TMR_TIMER0_CTC_SET_CALLBACK(void (*Ptr)(void))
{
    TIMER0_CTC_pCALLBACK = Ptr;
}


/* ISR Function Prototype for TOV0 */
void __vector_11(void) __attribute__ ((signal));
void __vector_11(void)
{
    static u16 Counter_OV = 0;
    Counter_OV++;
    if(Counter_OV == TMR_TIMER0_FINAL_OVERFLOW)
    {
        /* Set Preload Value (To maintain the fractions in calculations (0.56)) */
        TCNT0 = TMR_TIMER0_PRELOAD_VAL;
        /* Clear Counter to be able to iterate */
        Counter_OV = 0;
        /* Toggle Pin */
        //DIO_TOG_PIN_VAL(DIO_PORTC, DIO_PIN7);
    }
}

/* ISR Function Prototype for CTC0 */
void __vector_10(void) __attribute__ ((signal));
void __vector_10(void)
{
    static u16 Counter_CTC = 0;
    Counter_CTC++;
    if(Counter_CTC == TMR_TIMER0_FINAL_CTC)
    {
        /* Clear Counter to be able to iterate */
        Counter_CTC = 0;
        /* Toggle Pins using pointer to function */
        TIMER0_CTC_pCALLBACK();
    }
}


/***************************************************************/

                /**** TIMER -> 1  ****/
/**
 * @brief: A function that initialize Timer 1
 * 
 */
void TMR_TIMER1_INIT(void)
{
    /*Set OC1A as Output Pin*/
    SET_BIT(DDRD, 5);
    /*Select Mode FPWM = Mode 14*/
    CLR_BIT(TCCR1A, 0);
    SET_BIT(TCCR1A, 1);
    SET_BIT(TCCR1B, 3);
    SET_BIT(TCCR1B, 4);
    /* Select Non Inverting Mode */
    CLR_BIT(TCCR1A, 6);
    SET_BIT(TCCR1A, 7);
    
    /*ICR1 >> Period Time*/
    ICR1_u16 = 4999; /*50 Hz for Servo Motor (20 ms / 4 us = 5000 us)*/
    
    /* Select Prescaler = 64 */
    SET_BIT(TCCR1B, 0);
    SET_BIT(TCCR1B, 1);
    CLR_BIT(TCCR1B, 2);

}

/**
 * @brief: A function that set the desired value for timer 1 in the OCR1A/B REG
 * 
 * @param Value 
 */
void TMR_TIMER1_SET_COMPARE_MATCH_VAL(u16 Compare_Value)
{
    /*Init Timer 1 with Compare_Value*/
    OCR1A_u16 = Compare_Value;
}