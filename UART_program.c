/*
 * UART_program.c
 *
 * Created: 12/10/2022 7:11:32 PM
 * Author: Mohamed Mousa & Mohamed Ibrahim
 */ 

#include "DATA_TYPES.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

#define ARRAY_LENGTH(ARR)       ((sizeof(ARR)) / (sizeof(ARR[0])))

/**
 * @brief: A function that initializes the UART
 * 
 */
void UART_init(void)
{
//set data size 8bit , 1 stop bit , asynchronous mode , no parity mode

UCSRC = 0x86;
CLR_BIT(UCSRB,2);
	
//setting baud rate 9600
UBRRL = 103;	
	
//enable transmit
SET_BIT(UCSRB,3);

//enable receive
//SET_BIT(UCSRB,4);

}


/**
 * @brief: A function the send a character through UART
 * 
 * @param data: The data to be sent
 */
void UART_TxChar(u8 data)
{
UDR = data;

while( 0 == GET_BIT(UCSRA,5));		

}


/**
 * @brief: A function that recieves a character through UART
 * 
 * @param returnedData: Pointer the character to recieve the data
 */
void UART_RxChar (u8* returnedData)
{  
	
	
	if (returnedData != NULL )
	{
		//enable receive
		SET_BIT(UCSRB,4);
		while( 0 == GET_BIT(UCSRA,7));	
		*returnedData = UDR;
		//disable receive
		CLR_BIT(UCSRB,4);

	}
	else
	{
		// DO NOTHING          
	}
}

/**
 * @brief: A function that transmit a string
 * 
 * @param string: The string to be sent as a pointer ("Example")
 */
void UART_TransmitDataString(u8* string)
{
	u8 i=0;
	while(string[i] !='\0')
	{
		UART_TxChar(string[i]);
		i++;
	}
	string[i]='\0';

}

/**
 * @brief: A function that recieves a string in a pointer
 * 
 * @param arr: the array of characters that stores the recieved string
 */
void UART_ReciveString(u8*arr)
{
	for(u8 i=0; i<4;i++)
	{
		UART_RxChar(&arr[i]);
	}
}

/**
 * @brief: A function that compares to strings
 * 
 * @param ptr: Pointer to charcter
 * @param password: The Password to be compared
 * @return u8: return 1 if success and 0 otherwise
 */
u8 Compare_String(u8 *ptr, u8*password)

{
	u8 i =0;
	while (password[i] != '\0')
	
	{
		if (ptr[i] == password[i])
		{
			i++;
			continue;
			
		}
		else
		{
			return 0;
		}
	}
	return 1;
}
