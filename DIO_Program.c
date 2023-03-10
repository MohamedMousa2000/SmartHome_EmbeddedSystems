/*
 * DIO_Programe.c
 *
 * Created: 10/22/2022 11:08:19 PM
 * Author: Mohamed Mousa & Mohamed Ibrahim
 * 
 */ 

#include "DATA_TYPES.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

#include "DIO_INTERFACE.h"

/**
 * @brief: A function that set the direction of the pin either (1  or  0)
 *                                                             (OUT / IN)
 * 
 * @param PortID: Port Number
 * @param PinID : Pin Number 
 * @param PinDir: Pin Direction
 */
void DIO_SET_PIN_DIR(u8 PortID, u8 PinID, u8 PinDir)
{
    switch(PortID)
    {
        case DIO_PORTA:
        {
            if (PinDir == DIO_PIN_OUTPUT)
            {
                SET_BIT(DDRA, PinID);
            }
            else
            {
                CLR_BIT(DDRA, PinID);
            }
            
            break;
        }
        case DIO_PORTB:
        {
            if (PinDir == DIO_PIN_OUTPUT)
            {
                SET_BIT(DDRB, PinID);
            }
            else
            {
                CLR_BIT(DDRB, PinID);
            }
            
            break;
        }
        case DIO_PORTC:
        {
            if (PinDir == DIO_PIN_OUTPUT)
            {
                SET_BIT(DDRC, PinID);
            }
            else
            {
                CLR_BIT(DDRC, PinID);
            }
            
            break;
        }
        case DIO_PORTD:
        {
            if (PinDir == DIO_PIN_OUTPUT)
            {
                SET_BIT(DDRD, PinID);
            }
            else
            {
                CLR_BIT(DDRD, PinID);
            }
            
            break;
        }   
    }
}

/**
 * @brief: A function that choose the value of the pin either SET (1) Or CLR (0)
 * 
 * @param PortID: Port Number
 * @param PinID : Pin Number
 * @param PinVal: Pin Value
 */
void DIO_SET_PIN_VAL(u8 PortID, u8 PinID, u8 PinVal)
{
    switch(PortID)
    {
        case DIO_PORTA:
        {
            if(PinVal == DIO_PIN_HIGH)
            {
                SET_BIT(PORTA, PinID);
            }
            else
            {
                CLR_BIT(PORTA, PinID);
            }

            break;
        }
         case DIO_PORTB:
        {
            if(PinVal == DIO_PIN_HIGH)
            {
                SET_BIT(PORTB, PinID);
            }
            else
            {
                CLR_BIT(PORTB, PinID);
            }

            break;
        }
         case DIO_PORTC:
        {
            if(PinVal == DIO_PIN_HIGH)
            {
                SET_BIT(PORTC, PinID);
            }
            else
            {
                CLR_BIT(PORTC, PinID);
            }

            break;
        }
         case DIO_PORTD:
        {
            if(PinVal == DIO_PIN_HIGH)
            {
                SET_BIT(PORTD, PinID);
            }
            else
            {
                CLR_BIT(PORTD, PinID);
            }

            break;
        }
    }
}

/**
 * @brief: A function that return the value of a specific pin in a specific port
 * 
 * @param PortID: Port Number
 * @param PinID : Pin Number 
 * @return u8   : unsigned char
 */
u8 DIO_GET_PIN_VAL(u8 PortID, u8 PinID)
{
    u8 Pin_State;
    
    switch(PortID)
    {
        case DIO_PORTA:
        {
            Pin_State = GET_BIT(PINA, PinID);
            break;
        }
        case DIO_PORTB:
        {
            Pin_State = GET_BIT(PINB, PinID);
            break;
        }
        case DIO_PORTC:
        {
            Pin_State = GET_BIT(PINC, PinID);
            break;
        }
        case DIO_PORTD:
        {
            Pin_State = GET_BIT(PIND, PinID);
            break;
        }
    }

    return Pin_State;
}

/**
 * @brief: A function that toggle a specific bit in a specific port
 * 
 * @param PortID: Port Number
 * @param PinID : Pin Number
 */
void DIO_TOG_PIN_VAL(u8 PortID, u8 PinID)
{
    switch(PortID)
    {
        case DIO_PORTA:
        {
            TOG_BIT(PORTA, PinID);
            break;
        }
        case DIO_PORTB:
        {
            TOG_BIT(PORTB, PinID);
            break;
        }
        case DIO_PORTC:
        {
            TOG_BIT(PORTC, PinID);
            break;
        }
        case DIO_PORTD:
        {
            TOG_BIT(PORTD, PinID);
            break;
        }
    }
}

/**
 * @brief: A function that activate the pull up resistor on a specific pin in a specific port
 * 
 * @param PortID: Port Number
 * @param PinID : Pin Number
 */
void DIO_ACTIVATE_PULL_UP(u8 PortID, u8 PinID)
{
    switch(PortID)
    {
        case DIO_PORTA:
        {
            SET_BIT(PORTA, PinID);
            break;
        }
        case DIO_PORTB:
        {
            SET_BIT(PORTB, PinID);
            break;
        }
        case DIO_PORTC:
        {
            SET_BIT(PORTC, PinID);
            break;
        }
        case DIO_PORTD:
        {
            SET_BIT(PORTD, PinID);
            break;
        }
    }
}