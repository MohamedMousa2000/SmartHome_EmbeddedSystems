/*
 * SmartHome_int.h
 *
 * Created: 2/28/2023 1:05:13 AM
 * Author: Mohamd Mousa & Mohamed Ibrahim
 */ 


#ifndef SMARTHOME_INT_H_
#define SMARTHOME_INT_H_

/*UTILS*/
#include "DATA_TYPES.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"



#define Max_UsernameArray_Size 5 //Username length must not exceed for characters
#define Max_PasswordArray_Size 5 //password length must not exceed for characters
#define Max_NumOfUsers         256
#define USERNAME_Addresses     1024

/**
 * @brief: A function that askes the user or the admin to enter a username and a password
 *         and store them in the EEPROM
 * 
 * @param UserOrAdmin: Token to indicate is it for the user or the admin
 */
void SignUp(u8 UserOrAdmin);

/**
 * @brief: A function that checks if the entered username and password are
 *         exist or not in the EEPROM
 * 
 * @param UserOrAdmin: Token to indicate is it for the user or the admin
 * @return u8 : if success return 1 else return 0
 */
u8 LogIn(u8 UserOrAdmin);

/**
 * @brief: A function that initialize the system pins and communications
 * 
 */
void SystemInit(void);

/**
 * @brief: A function that breaks the system down and activate the alarm
 * 
 */
void BreakDownSystem(void);

/**
 * @brief: A function that use Timer1 to open the door using servo motor
 * 
 */
void OpenDoor(void);

/**
 * @brief: A function that use Timer1 to close the door using servo motor
 * 
 */
void CloseDoor(void);

/**
 * @brief: A function the Control the Fan using the relay and set as an address to Timer0_SETCALLBACK
 * 
 */
void AirConditioning(void);

/**
 * @brief: A function that set in all the EEPROM addresses 0s to help in the searching and removing processes
 * 
 */
void DATABASE_RESET(void);

/**
 * @brief: A function that removes users from EEPROM
 * 
 * @return u8: if success return 1 else return 0
 */
u8 RemoveUser(void);

#endif /* SMARTHOME_INT_H_ */