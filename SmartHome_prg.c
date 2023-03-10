/*
 * SmartHome_prg.c
 *
 * Created: 2/28/2023 1:04:46 AM
 * Author: Mohamd Mousa & Mohamed Ibrahim
 */ 

#define F_CPU 16000000UL 
/*UTILS*/
#include "DATA_TYPES.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"
#include <util/delay.h>
/*MCAL*/
#include "DIO_INTERFACE.h"
#include "TWI_INTERFACE.h"
#include "UART_interface.h"
#include "GI_INTERFACE.h"
#include "TMR_CONFIG.h"
#include "TMR_INTERFACE.h"
#include "ADC_INTERFACE.h"
/*HAL*/
#include "EEPROM_INTERFACE.h"
#include "LCD_interface.h"
#include "KPD_CONFIG.h"
#include "KPD_INTERFACE.h"
#include "RELAY_interface.h"
/*APP*/
#include "SmartHome_int.h"


/**
 * @brief: A function that initialize the system pins and communications
 * 
 */
void SystemInit(void)
{
    DIO_SET_PIN_DIR(DIO_PORTC, DIO_PIN2, DIO_PIN_OUTPUT); //LED0
    DIO_SET_PIN_DIR(DIO_PORTC, DIO_PIN7, DIO_PIN_OUTPUT); //LED1
	DIO_SET_PIN_DIR(DIO_PORTD, DIO_PIN3, DIO_PIN_OUTPUT); //LED2
    DIO_SET_PIN_DIR(DIO_PORTD, DIO_PIN2, DIO_PIN_OUTPUT); //LED3
    DIO_SET_PIN_DIR(DIO_PORTD, DIO_PIN4, DIO_PIN_OUTPUT); //LED4
    DIO_SET_PIN_DIR(DIO_PORTA, DIO_PIN0, DIO_PIN_OUTPUT); //Dimmer
    DIO_SET_PIN_DIR(DIO_PORTD, DIO_PIN1, DIO_PIN_OUTPUT); //TX
    DIO_SET_PIN_DIR(DIO_PORTD,DIO_PIN0,DIO_PIN_INPUT);    //RX
    DIO_SET_PIN_DIR(DIO_PORTA,DIO_PIN3,DIO_PIN_OUTPUT);   //Buzzer
    
	GI_ENABLE();                                          //Global Interrupt
    UART_init();                                          //UART (For Admin Communication)
    RELAY_init();                                         //Relay (For controlling the Fan in the AirConditioning)
    TWI_INIT_MASTER();                                    //TWI (I2C) (For EEPROM communication)
    KPD_INIT();                                           //KeyPad (For User Communication)
    LCD_init();                                           //LCD to visualize the system response to users
    TMR_TIMER1_INIT();                                    //Timer 1 to send a PWM to control the servo motor for door simulation
    ADC_INIT();                                           //ADC to read the potentiometer as a simulation for the tempreture sensor
    TMR_TIMER0_CTC_SET_CALLBACK(&AirConditioning);        //SetCallBack function that takes the airconditioning address and read from POT every 1.5 seconds 
    TMR_TIMER0_SET_COMPARE_MATCH_VAL(249);                //The compare match upon which we calculate the 1.5 seconds
    TMR_TIMER0_INIT();                                    //Timer 0 to interrupt the system every 1.5 seconds and read the Temprature
}

/**
 * @brief: A function that askes the user or the admin to enter a username and a password
 *         and store them in the EEPROM
 * 
 * @param UserOrAdmin: Token to indicate is it for the user or the admin
 */
void SignUp(u8 UserOrAdmin)
{
    
    u8 NewUser[Max_UsernameArray_Size - 1];
	u8 NewPassword[Max_PasswordArray_Size - 1];
    /*A loop that makes sure that the input in username or password is not a 0*/
	while(1)
        {
            u8 OK = 0;
            UART_TransmitDataString("Dont'tEnter(0)!!!\n");
            UART_ReciveString(NewUser);
            UART_ReciveString(NewPassword);
            for(u8 i = 0; i < 4; i++)
            {
                if(NewUser[i] == '0' || NewPassword[i] == '0')
                {
                    break;
                }
                else
                {
                    OK++;
                    continue;
                }
            }
            if(OK == 4)
            {
                break;
            }
            else
            {
                continue;
            }
        }
    /*Check on the token*/
    /*In case of User SignUp*/
    if(UserOrAdmin == 2)
    {
        for(u8 Address = 4; Address < USERNAME_Addresses; Address = Address + 4)
        {
            /*Check if the current address is an empty address (Contains 0)*/
            u8 Empty = 1;
            EEPROM_READ_BYTE(Address, &Empty);
            _delay_ms(5);
            if(Empty == 0)
            {
                /*Store the new Username and Password*/
                for(u8 i = 0; i < Max_UsernameArray_Size - 1; i++)
                {
                    EEPROM_WRITE_BYTE(Address + i, NewUser[i]);     
                    EEPROM_WRITE_BYTE(Address + i + USERNAME_Addresses, NewPassword[i]);
                }
                break;
            }
        }
    }
    /*In case of Admin SignUp*/
    else if(UserOrAdmin == 1)
    {
        /*Storing the New Admin (We don't to do that every time (Just after the rest of the EEPROM))*/
        for(u8 i = 0; i < Max_UsernameArray_Size - 1; i++)
        {
            EEPROM_WRITE_BYTE(i, NewUser[i]);     
            EEPROM_WRITE_BYTE(i + USERNAME_Addresses, NewPassword[i]);
        }
    }
}

/**
 * @brief: A function that checks if the entered username and password are
 *         exist or not in the EEPROM
 * 
 * @param UserOrAdmin: Token to indicate is it for the user or the admin
 * @return u8 : if success return 1 else return 0
 */
u8 LogIn(u8 UserOrAdmin)
{
   
    u8 NewUser[Max_UsernameArray_Size - 1];
    u8 NewPass[Max_PasswordArray_Size - 1];
    /*Check on the token*/
    if(UserOrAdmin == 1)
    {
        /*A loop that makes sure that the input in username or password is not a 0*/
        while(1)
        {
            u8 OK = 0;
            UART_TransmitDataString("Dont'tEnter(0)!!!\n");
            UART_ReciveString(NewUser);
            UART_ReciveString(NewPass);
            for(u8 i = 0; i < 4; i++)
            {
                if(NewUser[i] == '0' || NewPass[i] == '0')
                {
                    break;
                }
                else
                {
                    OK++;
                    continue;
                }
            }
            if(OK == 4)
            {
                break;
            }
            else
            {
                continue;
            }
        }
    }
	else if(UserOrAdmin == 2)
    {
        /*A loop that makes sure that the input in username or password is not a 0*/
        while(1)
        {
            u8 OK = 0;
            LCD_clear();
            LCD_writeString("Don't Enter (0)!");
            _delay_ms(1000);
            LCD_clear();
            LCD_writeString("Username: ");
            /*Getting the username by polling*/
            for(u8 i = 0; i < Max_UsernameArray_Size - 1; i++)
            {
                while(1)
                {
                    KPD_GET_VAL(NewUser + i);
                    if(NewUser[i] != KPD_NOT_PRESSED)
                    {
                        LCD_sendChar(NewUser[i]);
                        break;
                    }
                }
            }
            LCD_clear();
            LCD_writeString("Password: ");
            /*Getting the password by polling*/
            for(u8 i = 0; i < Max_PasswordArray_Size - 1; i++)
            {
                while(1)
                {
                    KPD_GET_VAL(NewPass + i);
                    if(NewPass[i] != KPD_NOT_PRESSED)
                    {
                        LCD_sendChar(NewPass[i]);
                        break;
                    }
                }
            }
            LCD_clear();
            /*Check on 0 entry*/
            for(u8 i = 0; i < 4; i++)
            {
                if(NewUser[i] == '0' || NewPass[i] == '0')
                {
                    break;
                }
                else
                {
                    OK++;
                    continue;
                }
            }
            if(OK == 4)
            {
                break;
            }
            else
            {
                continue;
            }
        }
    }
    u8 Found = 0;
	u32 j;
    u8 FetchedUser[4];
    u8 FetchedPass[4];
    /*Depending on the token, we LogIn Admin or User*/
   if(UserOrAdmin == 1)
   {
        /*Searching for the admin username in the first 4 addresses in EEPROM and first (after 1024) 4 addresses for password*/
        for(j = 0; j < Max_UsernameArray_Size - 1; j++)
        {
            EEPROM_READ_BYTE(j, &FetchedUser[j]);
            EEPROM_READ_BYTE(j + USERNAME_Addresses, &FetchedPass[j]);
            if((FetchedUser[j] == NewUser[j]) && (FetchedPass[j] == NewPass[j]))
            {
                Found++;
                continue;
            }
            else
            {
                break;
            }
        }
        if(Found == Max_UsernameArray_Size - 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
   }
   /*In case of User LogIn*/
   else if(UserOrAdmin == 2)
   {
        /*Start Searching from the address no 4*/
        for(u32 CurrentAddress = 4; CurrentAddress < USERNAME_Addresses; CurrentAddress = CurrentAddress + 4)
        { 
                Found = 0;
                u8 Empty = 1;
                /*Check that the current address is not empty*/
                EEPROM_READ_BYTE(CurrentAddress, &Empty);
                if(Empty != 0)
                {
                    /*Start comparing the entry with what is stored*/
                    for(j = 0; j < Max_UsernameArray_Size - 1; j++)
                    {
                        EEPROM_READ_BYTE(j + CurrentAddress, &FetchedUser[j]);
                        EEPROM_READ_BYTE(j + CurrentAddress + USERNAME_Addresses, &FetchedPass[j]);
                        if((FetchedUser[j] == NewUser[j]) && (FetchedPass[j] == NewPass[j]))
                        {
                            Found++;
                            continue;
                        }
                        else
                        {
                            break;
                        }
                    }
                    if(Found == Max_UsernameArray_Size - 1)
                    {
                        return 1;
                    }
                    else
                    {
                        continue;
                    }
                }
        }
        return 0;
   }
}

/**
 * @brief: A function that breaks the system down and activate the alarm
 * 
 */
void BreakDownSystem(void)
{
    UART_TransmitDataString("THIEF!!!!!");
    while(1)
    {
        /*Buzzer Enabled*/
        DIO_SET_PIN_VAL(DIO_PORTA,DIO_PIN3,DIO_PIN_HIGH);
    }
}

/**
 * @brief: A function that use Timer1 to open the door using servo motor
 * 
 */
void OpenDoor(void)
{
    /*Sending PWM to Servo*/
    TMR_TIMER1_SET_COMPARE_MATCH_VAL(499);
}

/**
 * @brief: A function that use Timer1 to close the door using servo motor
 * 
 */
void CloseDoor(void)
{
    /*Sending PWM to Servo*/
    TMR_TIMER1_SET_COMPARE_MATCH_VAL(249);
}

/**
 * @brief: A function the Control the Fan using the relay and set as an address to Timer0_SETCALLBACK
 * 
 */
void AirConditioning(void)
{
    u16 Temp = 0;
    /*Get The readings from the POT*/
	ADC_GET_DIGITAL_VAL(ADC_CHANNEL1, &Temp);
    /*Mappin representation to simulate the temprature*/
    u16 Analog_Val = (Temp * 5000UL)/1024;
    /*In case the Temp is less than 22 C*/
    if(Analog_Val < 1500)
    {
        RELAY_off();
    }
    /*In case the Temp is greater than 28 C*/
    else if (Analog_Val > 3000 )
    {
        RELAY_on();
    }

}

/**
 * @brief: A function that set in all the EEPROM addresses 0s to help in the searching and removing processes
 * 
 */
void DATABASE_RESET(void)
{
    for(u8 i = 0; i < 1024; i++)
    {
        EEPROM_WRITE_BYTE(i, 0);
        EEPROM_WRITE_BYTE(i + 1024, 0);
        DIO_TOG_PIN_VAL(DIO_PORTD, DIO_PIN3); //To indicate that the process is finished
        _delay_ms(5);
    }
}

/**
 * @brief: A function that removes users from EEPROM
 * 
 * @return u8: if success return 1 else return 0
 */
u8 RemoveUser(void)
{
    u8 NewUser[Max_UsernameArray_Size - 1];
    u8 NewPass[Max_PasswordArray_Size - 1];
    UART_TransmitDataString("Username:\n");
    UART_TransmitDataString("Password:\n");
    /*A loop that makes sure that the input in username or password is not a 0*/
    while(1)
    {
        u8 OK = 0;
        UART_TransmitDataString("Dont'tEnter(0)!!!\n");
        UART_ReciveString(NewUser);
        UART_ReciveString(NewPass);
        for(u8 i = 0; i < 4; i++)
        {
            if(NewUser[i] == '0' || NewPass[i] == '0')
            {
                break;
            }
            else
            {
                OK++;
                continue;
            }
        }
        if(OK == 4)
        {
            break;
        }
        else
        {
            continue;
        }
    }
    u8 FetchedUser[4];
    u8 FetchedPass[4];
    /*Start Searching from the 4th address in the EEPROM*/
    for(u32 CurrentAddress = 4; CurrentAddress < 1024; CurrentAddress = CurrentAddress + 4)
    { 
        u8 Found = 0;
        u8 Empty = 1;
        /*Check that the current address is not empty*/
        EEPROM_READ_BYTE(CurrentAddress, &Empty);
        if(Empty != 0)
        {
            /*Start comparing to find the User to be deleted*/
            for(u8 j = 0; j < Max_UsernameArray_Size - 1; j++)
            {
                EEPROM_READ_BYTE(j + CurrentAddress, &FetchedUser[j]);
                EEPROM_READ_BYTE(j + CurrentAddress + 1024, &FetchedPass[j]);
                if((FetchedUser[j] == NewUser[j]) && (FetchedPass[j] == NewPass[j]))
                {
                    Found++;
                    continue;
                }
                else
                {
                    break;
                }
            }
            if(Found == Max_UsernameArray_Size - 1)
            {
                /*Removing the User by setting in the corresponding EEPROM addresses 0s*/
                for(u8 Remove = CurrentAddress; Remove < Max_UsernameArray_Size - 1 + CurrentAddress; Remove++)
                {
                    EEPROM_WRITE_BYTE(Remove, 0);
                    EEPROM_WRITE_BYTE(Remove + USERNAME_Addresses, 0);
                }
                return 1;
            }
            else
            {
                continue;
            }
        }
    }
    return 0;
}