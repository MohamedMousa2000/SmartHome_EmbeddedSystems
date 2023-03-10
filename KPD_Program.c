/*
 * KPD_Program.c
 *
 * Created: 10/29/2022 11:26:42 PM
 * Author: Mohamed Mousa & Mohamed Ibrahim
 * 
 */ 

/* UTILS_LIB */
#include "DATA_TYPES.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

/* MCAL */
#include "DIO_INTERFACE.h"

/* HAL */
#include "KPD_INTERFACE.h"
#include "KPD_CONFIG.h"

/* Global Variables */
static u8 KPD_COL_PINS[4] = {KPD_C0_PIN, KPD_C1_PIN, KPD_C2_PIN, KPD_C3_PIN};
static u8 KPD_ROW_PINS[4] = {KPD_R0_PIN, KPD_R1_PIN, KPD_R2_PIN, KPD_R3_PIN};

/**
 * @brief: A function that initialize the KeyPad
 * 
 */
void KPD_INIT(void)
{
    /* Initialize columns pins as OUTPUTS */
    DIO_SET_PIN_DIR(KPD_COL_PORT, KPD_C0_PIN, DIO_PIN_OUTPUT);
    DIO_SET_PIN_DIR(KPD_COL_PORT, KPD_C1_PIN, DIO_PIN_OUTPUT);
    DIO_SET_PIN_DIR(KPD_COL_PORT, KPD_C2_PIN, DIO_PIN_OUTPUT);
    DIO_SET_PIN_DIR(KPD_COL_PORT, KPD_C3_PIN, DIO_PIN_OUTPUT);

    /* Initialize ROWs pins as OUTPUTS */
    DIO_SET_PIN_DIR(KPD_ROW_PORT, KPD_R0_PIN, DIO_PIN_INPUT);
    DIO_SET_PIN_DIR(KPD_ROW_PORT, KPD_R1_PIN, DIO_PIN_INPUT);
    DIO_SET_PIN_DIR(KPD_ROW_PORT, KPD_R2_PIN, DIO_PIN_INPUT);
    DIO_SET_PIN_DIR(KPD_ROW_PORT, KPD_R3_PIN, DIO_PIN_INPUT);

    /* Activate Pull Up Resistor */
    DIO_ACTIVATE_PULL_UP(KPD_ROW_PORT, KPD_R0_PIN);
    DIO_ACTIVATE_PULL_UP(KPD_ROW_PORT, KPD_R1_PIN);
    DIO_ACTIVATE_PULL_UP(KPD_ROW_PORT, KPD_R2_PIN);
    DIO_ACTIVATE_PULL_UP(KPD_ROW_PORT, KPD_R3_PIN);

}

/**
 * @brief: A function that change a variable value with the number pressed
 * 
 * @param Returned_Val: Pointer to Char that changes the value of the variable
 *                      by reference
 */
void KPD_GET_VAL(u8* Returned_Val)
{
	/* Initialize the variables */
    u8 KPD_KEYS[4][4] = {{'1','2','3','A'},
                         {'4','5','6','B'},
                         {'7','8','9','C'},
                         {'*','0','#','D'}};
							 
    u8 COL_Counter, ROW_Counter, Pin_Val;
    u8 Pin_Flag = 0;
	
	/* Checking the key pressed */
	*Returned_Val = KPD_NOT_PRESSED;
    
	/* Activate Columns */
    for(COL_Counter = 0; COL_Counter < 4; COL_Counter++)
    {
        DIO_SET_PIN_VAL(KPD_COL_PORT, KPD_COL_PINS[COL_Counter], DIO_PIN_LOW);
        /* Check on each ROW */
        for(ROW_Counter = 0; ROW_Counter < 4; ROW_Counter++)
        {
            Pin_Val = DIO_GET_PIN_VAL(KPD_ROW_PORT, KPD_ROW_PINS[ROW_Counter]);
            if(Pin_Val == 0)
            {
                *Returned_Val = KPD_KEYS[ROW_Counter][COL_Counter];
                /* Check that we left our finger from the key (To prevent repeatation of the character during one press) */
                while (Pin_Val == 0)
                {
                    Pin_Val = DIO_GET_PIN_VAL(KPD_ROW_PORT, KPD_ROW_PINS[ROW_Counter]);
                }
                /* Setting Flag to indicate that we found the character */
                Pin_Flag = 1;
                break;
            }
        }
        /* Deactivate the column value */
        DIO_SET_PIN_VAL(KPD_COL_PORT, KPD_COL_PINS[COL_Counter], DIO_PIN_HIGH);
        /* Check that we got a character */
        if(Pin_Flag == 1)
        {
            break;
        }
    }
}
