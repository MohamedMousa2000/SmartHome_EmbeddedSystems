/*
 * KPD_INTERFACE.h
 *
 * Created: 10/29/2022 11:26:58 PM
 * Author: Mohamed Mousa & Mohamed Ibrahim
 * 
 */ 


#ifndef KPD_INTERFACE_H_
#define KPD_INTERFACE_H_

#define KPD_NOT_PRESSED	0xFF

/**
 * @brief: A function that initialize the KeyPad
 * 
 */
void KPD_INIT(void);

/**
 * @brief: A function that change a variable value with the number pressed
 * 
 * @param Returned_Val: Pointer to Char that changes the value of the variable
 *                      by reference
 */
void KPD_GET_VAL(u8* Returned_Val);




#endif /* KPD_INTERFACE_H_ */