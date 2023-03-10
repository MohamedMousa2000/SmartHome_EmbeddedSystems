/*
 * TMR_INTERFACE.h
 *
 * Created: 11/12/2022 10:15:24 PM
 * Author: Mohamed Mousa & Mohamed Ibrahim
 */ 


#ifndef TMR_INTERFACE_H_
#define TMR_INTERFACE_H_

/* TIMER_0 */
/* Modes */
#define TMR_TIMER0_NORMAL_MODE       1
#define TMR_TIMER0_CTC_MODE          2
#define TMR_TIMER0_FAST_PWM_MODE     3

                /**** TIMER -> 0  ****/

/**
 * @brief: A function that initialize Timer 0
 * 
 */
void TMR_TIMER0_INIT(void);

/**
 * @brief: A function that set the desired value for timer 0 in the OCR0 REG
 * 
 * @param Value 
 */
void TMR_TIMER0_SET_COMPARE_MATCH_VAL(u8 Compare_Value);

/**
 * @brief: Set callback function to CTC Interrupt
 * 
 * @param Ptr: Pointer to function
 */
void TMR_TIMER0_CTC_SET_CALLBACK(void (*Ptr)(void));

/***************************************************************/

                /**** TIMER -> 1  ****/
/**
 * @brief: A function that initialize Timer 1
 * 
 */
void TMR_TIMER1_INIT(void);

/**
 * @brief: A function that set the desired value for timer 1 in the OCR1A/B REG
 * 
 * @param Value 
 */
void TMR_TIMER1_SET_COMPARE_MATCH_VAL(u16 Compare_value);

#endif /* TMR_INTERFACE_H_ */