/*
 * ADC_INTERFACE.h
 *
 * Created: 11/11/2022 9:47:32 PM
 * Author: Mohamed Mousa & Mohamed Ibrahim
 */ 


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_



#define ADC_CHANNEL0    0
#define ADC_CHANNEL1    1
#define ADC_CHANNEL2    2
#define ADC_CHANNEL3    3
#define ADC_CHANNEL4    4
#define ADC_CHANNEL5    5
#define ADC_CHANNEL6    6
#define ADC_CHANNEL7    7


/**
 * @brief: A function that Intialize the ADC
 * 
 */
void ADC_INIT(void);

/**
 * @brief: A function that takes the channel number and the address 
 *         of the variable which we will return in it the converged
 *         value
 * 
 * @param Channel_Num: Channel Number in MUX 
 * @param Digital_Val: Pointer to unsigned 16 in which we will assign 
 *                     the digital value
 */
void ADC_GET_DIGITAL_VAL(u8 Channel_Num, u16* Digital_Val);



#endif /* ADC_INTERFACE_H_ */