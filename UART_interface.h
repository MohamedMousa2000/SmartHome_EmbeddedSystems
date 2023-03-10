/*
 * UART_interface.h
 *
 * Created: 12/10/2022 7:11:57 PM
 * Author: Mohamed Mousa & Mohamed Ibrahim
 */ 


#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

/**
 * @brief: A function that initializes the UART
 * 
 */
void UART_init(void);

/**
 * @brief: A function the send a character through UART
 * 
 * @param data: The data to be sent
 */
void UART_TxChar(u8 data);

/**
 * @brief: A function that recieves a character through UART
 * 
 * @param returnedData: Pointer the character to recieve the data
 */
void UART_RxChar (u8* returnedData);

/**
 * @brief: A function that transmit a string
 * 
 * @param string: The string to be sent as a pointer ("Example")
 */
void UART_TransmitDataString(u8* string);

/**
 * @brief: A function that recieves a string in a pointer
 * 
 * @param arr: the array of characters that stores the recieved string
 */
void UART_ReciveString(u8*arr);

/**
 * @brief: A function that compares to strings
 * 
 * @param ptr: Pointer to charcter
 * @param password: The Password to be compared
 * @return u8: return 1 if success and 0 otherwise
 */
u8 Compare_String(u8 *ptr, u8*password);

#endif /* UART_INTERFACE_H_ */