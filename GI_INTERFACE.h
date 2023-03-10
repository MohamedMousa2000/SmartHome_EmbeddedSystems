/*
 * GI_INTERFACE.h
 *
 * Created: 11/12/2022 10:49:49 PM
 * Author: Mohamed Mousa & Mohamed Ibrahim
 */ 


#ifndef GI_INTERFACE_H_
#define GI_INTERFACE_H_

/**
 * @brief: A function that Enable the global interrupt in SREG register
 * 
 */
void GI_ENABLE(void);

/**
 * @brief: A function that Disable the global interrupt in SREG register
 * 
 */
void GI_DISABLE(void);



#endif /* GI_INTERFACE_H_ */