/*
 * SmartHomeTest.c
 *
 * Created: 2/28/2023 12:48:03 AM
 * Author : DELL
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

int main(void)
{
    /*Initialize the system prephirals*/
    SystemInit();
    //DATABASE_RESET(); /*TO RESET THE EEPROM -> REMOVE THE COMMENT */
    /*USER OR ADMIN TOKEN Initialization*/
    u8 AdminActive = 1;
    u8 UserActive = 2;
    /*Buzzer variable for the admin*/
    u8 AdminBuzz = 0;
    UART_TransmitDataString("Login:\n");
    //SignUp(AdminActive);  /*TO SIGNUP A NEW ADMIN AND OVERWRITE THE OLD ONE -> REMOVE THE COMMENT*/
    /*Variable to know if the admin is on or not*/
    u8 AdminLogin;  
    /*Start the login for the admin (And check if the username and password are correct)*/
    for(u8 i = 0; i < 3; i++)
    {
        UART_TransmitDataString("Admin->\nUsername:\nPassword:");
        UART_TransmitDataString("You-Have-Three-Trials!!!\n");
        AdminLogin = LogIn(AdminActive);
        _delay_ms(100);
        if(AdminLogin != 1)
        {
            UART_TransmitDataString("WrongTrial\n");
            AdminBuzz++; /*Increment the buzzer if the entry was wrong*/
        }
        else
        {
            break; // For
        }
    }
    /*Check on the number of entries*/
    if(AdminBuzz == 3)
    {
        /*Activate the buzzer and breakdown the system*/
        BreakDownSystem(); 
    }
    else
    {
        /*Continue to the next stage*/
    }

    ///////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////

    /*Variable to know if the User is on or not*/
    u8 UserLogin = 0;
    /*A loop that's activated only if the admin is ON*/
    while(AdminLogin)
    {
        /*Specifies the admin order*/
        u8 AdminOrder = 0;
        UART_TransmitDataString("a.SignNewUser:\n");
        UART_TransmitDataString("b.EnterSystemAsAdmin:\n");
        UART_TransmitDataString("c.UserLogin:\n");
        UART_TransmitDataString("r.RemoveUser:\n");
        UART_RxChar(&AdminOrder);
        /*SignUp new user*/
        if(AdminOrder == 'a')
        {
            UART_TransmitDataString("UserName\nPassword:\n");
            
            SignUp(UserActive);
        }
        /*Enter the system as admin*/
        else if(AdminOrder == 'b')
        {
            break;
        }
        /*LogIn a User*/
        else if(AdminOrder == 'c')
        {
            /*Buzzer variable for the user*/
            u8 UserBuzz = 0;
            for(u8 i = 0; i < 3; i++)
            {
                LCD_writeString("User->\nUsername:\nPassword:");
                _delay_ms(1000);
                LCD_clear();
                LCD_writeString("Three Trials!\n");
                _delay_ms(1000);
                UserLogin = LogIn(UserActive);
                _delay_ms(100);
                if(UserLogin != 1)
                {
                    LCD_writeString("WrongTrial\n");
                    UserBuzz++; /*Increment the number of trials*/
                }
                else
                {
                    break; // For
                }
            }
            /*Check on the number of trials*/
            if(UserBuzz == 3)
            {
                BreakDownSystem();
            }
            else
            {
                break; // While
            }
        }
        /*Remove an existing User*/
        else if(AdminOrder == 'r')
        {
            u8 Success = RemoveUser();
            if(Success == 1)
            {
                UART_TransmitDataString("Done!");
            }
            else
            {
                UART_TransmitDataString("Doesn'tExist!");
            }
        }

        else
        {
            UART_TransmitDataString("Wrong_Input!!!\n");
        }
    }

    ///////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////

    /*The System loop (Only Activated if the user or the admin are ON)*/
    while((AdminLogin) || (UserLogin))
    {
        /*Check on who are using the system*/
        /*To activate the user options -> the user must be already ON and we press the start button for the user*/
        if ((DIO_GET_PIN_VAL(DIO_PORTB, DIO_PIN0) == 1) && (UserLogin))      //User PB
        {
            /*Specifies the user order*/
            u8 UserOrder = 0;
            LCD_writeString("Welcome User :)\n");
            _delay_ms(1000);
            LCD_clear();
            _delay_ms(200);
            LCD_writeString("Enter an order: \n");
            /*Polling to wait for the user input*/
            while (1)
            {
              KPD_GET_VAL(&UserOrder);

              if (UserOrder != KPD_NOT_PRESSED)
              {
                break;
              }
              
            }
            
            LCD_sendChar(UserOrder);
            _delay_ms(1000);
            LCD_clear();
            switch(UserOrder)
            {
                case '0': LCD_clear(); DIO_TOG_PIN_VAL(DIO_PORTC, DIO_PIN2);               LCD_writeString("LED 0 Toggled");break;
                case '1': LCD_clear(); DIO_TOG_PIN_VAL(DIO_PORTC, DIO_PIN7);               LCD_writeString("LED 1 Toggled");break;
                case '2': LCD_clear(); DIO_TOG_PIN_VAL(DIO_PORTD, DIO_PIN3);               LCD_writeString("LED 2 Toggled");break;
                case '3': LCD_clear(); DIO_TOG_PIN_VAL(DIO_PORTD, DIO_PIN2);               LCD_writeString("LED 3 Toggled");break;
                case '4': LCD_clear(); DIO_TOG_PIN_VAL(DIO_PORTD, DIO_PIN4);               LCD_writeString("LED 4 Toggled");break;
                case '5': LCD_clear(); DIO_SET_PIN_VAL(DIO_PORTA, DIO_PIN0, DIO_PIN_HIGH); LCD_writeString("Dimmer is ON"); break;
                default:  LCD_clear(); LCD_writeString("WrongInput!!!");                                                    break;
            }
            
        }

        /*To activate the admin options -> the admin must be already ON and we press the start button for the admin*/
        else if((DIO_GET_PIN_VAL(DIO_PORTD, DIO_PIN6) == 1) && (AdminLogin)) //Admin PB
        {
            /*Specifies the admin order*/
            u8 AdminOrder = 0;
            UART_TransmitDataString("WelcomeAdmin:)\n");
            UART_TransmitDataString("WhatDoYouWant??\n");
            UART_RxChar(&AdminOrder);
            switch(AdminOrder)
            {
                case '0': DIO_TOG_PIN_VAL(DIO_PORTC, DIO_PIN2);               UART_TransmitDataString("LED 0 Toggled");break;
                case '1': DIO_TOG_PIN_VAL(DIO_PORTC, DIO_PIN7);               UART_TransmitDataString("LED 1 Toggled");break;
                case '2': DIO_TOG_PIN_VAL(DIO_PORTD, DIO_PIN3);               UART_TransmitDataString("LED 2 Toggled");break;
                case '3': DIO_TOG_PIN_VAL(DIO_PORTD, DIO_PIN2);               UART_TransmitDataString("LED 3 Toggled");break;
                case '4': DIO_TOG_PIN_VAL(DIO_PORTD, DIO_PIN4);               UART_TransmitDataString("LED 4 Toggled");break;
                case '5': DIO_SET_PIN_VAL(DIO_PORTA, DIO_PIN0, DIO_PIN_HIGH); UART_TransmitDataString("Dimmer is ON"); break;
                case 'o': OpenDoor();                                         UART_TransmitDataString("Door Opened");  break;
                case 'c': CloseDoor();                                        UART_TransmitDataString("Door Closed");  break;
                default: UART_TransmitDataString("WrongInput!!!");                                                     break;
            }
        } 
    }
}
