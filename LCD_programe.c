/*
 * LCD_programe.c
 *
 * Created: 9/11/2022 11:28:38 AM
 * Author: Mohamed Mousa & Mohamed Ibrahim
 */ 

#define F_CPU 16000000UL
#include <util/delay.h> 

/* UTILES_LIB */
#include "DATA_TYPES.h"
#include "BIT_MATH.h"
#include "ATMEGA32_REG.h"

/* MCAL */
#include "DIO_interface.h"

/* HAL */
#include "LCD_interface.h"
#include "LCD_config.h"

/**
 * @brief: A function that initializes the LCD
 * 
 */
void LCD_init(void)
{
	DIO_SET_PIN_DIR(DIO_PORTB, DIO_PIN1, DIO_PIN_OUTPUT);
	DIO_SET_PIN_DIR(DIO_PORTB, DIO_PIN2, DIO_PIN_OUTPUT);
	DIO_SET_PIN_DIR(DIO_PORTB, DIO_PIN3, DIO_PIN_OUTPUT);

	DIO_SET_PIN_DIR(DIO_PORTA, DIO_PIN4, DIO_PIN_OUTPUT);
	DIO_SET_PIN_DIR(DIO_PORTA, DIO_PIN5, DIO_PIN_OUTPUT);
	DIO_SET_PIN_DIR(DIO_PORTA, DIO_PIN6, DIO_PIN_OUTPUT);
	DIO_SET_PIN_DIR(DIO_PORTA, DIO_PIN7, DIO_PIN_OUTPUT);	
	
	_delay_ms(35);
	
#if LCD_MODE == LCD_8_BIT_MODE
	LCD_sendCmnd(0b00111000); // Function Set command 2*16 LCD
#elif LCD_MODE == LCD_4_BIT_MODE
    // set Rs pin = 0 (write command)
	DIO_SET_PIN_VAL(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_LOW);
	
	// set Rw pin = 0 (write)
	DIO_SET_PIN_VAL(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_LOW);
	writeHalfPort(0b0010);
	/* Enable Pulse *//* H => L */
	DIO_SET_PIN_VAL(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_SET_PIN_VAL(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);
	
	LCD_sendCmnd(0b00101000);
#endif
    _delay_us(45);
	
	// Display on off Control (DisplayOn, Cursor on, Blink on)
	LCD_sendCmnd(0b00001111);
	_delay_us(45);
	
	// Clear Display
	LCD_sendCmnd(0b00000001);
	_delay_ms(2);
	
	// Set Entry Mode
	LCD_sendCmnd(0b00000110);
}

/**
 * @brief: A function that send a certain command to the LCD
 * 
 * @param Cmnd: The command to be sent
 */
void LCD_sendCmnd(u8 Cmnd)
{
	// set Rs pin = 0 (write command)
	DIO_SET_PIN_VAL(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_LOW);
	
    // set Rw pin = 0 (write)
	DIO_SET_PIN_VAL(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_LOW);
	
#if LCD_MODE == LCD_8_BIT_MODE	
	DIO_SET_PIN_VAL(LCD_DATA_PORT,Cmnd);
    /* Enable Pulse *//* H => L */
	DIO_SET_PIN_VAL(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_SET_PIN_VAL(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);
	
#elif LCD_MODE == LCD_4_BIT_MODE	
	// Write The Most 4 bits Of command on Data Pins
	writeHalfPort(Cmnd>>4);
	
    /* Enable Pulse *//* H => L */
	DIO_SET_PIN_VAL(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_SET_PIN_VAL(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);
	
	// Write The Least 4 bits Of command on Data Pins
	writeHalfPort(Cmnd);
	
	/* Enable Pulse *//* H => L */
	DIO_SET_PIN_VAL(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_SET_PIN_VAL(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);
#endif
}

/**
 * @brief: A function that send a certain character to the LCD
 * 
 * @param data: The character to be sent
 */
void LCD_sendChar(u8 data)
{
    // set Rs pin = 1 (write data)
	DIO_SET_PIN_VAL(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_HIGH);
	
	// set Rw pin = 0 (write)
	DIO_SET_PIN_VAL(LCD_RW_PORT,LCD_RW_PIN,DIO_PIN_LOW);
	
#if LCD_MODE == LCD_8_BIT_MODE	
	DIO_setPortValue(LCD_DATA_PORT,data);
    /* Enable Pulse *//* H => L */
	DIO_SET_PIN_VAL(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_SET_PIN_VAL(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);
	
#elif LCD_MODE == LCD_4_BIT_MODE	
	// Write The Most 4 bits Of Data on Data Pins
	writeHalfPort(data>>4);
	
    /* Enable Pulse *//* H => L */
	DIO_SET_PIN_VAL(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_SET_PIN_VAL(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);
	
	// Write The Least 4 bits Of Data on Data Pins
	writeHalfPort(data);
	
	/* Enable Pulse *//* H => L */
	DIO_SET_PIN_VAL(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_SET_PIN_VAL(LCD_EN_PORT,LCD_EN_PIN,DIO_PIN_LOW);
#endif
}

/**
 * @brief: A function that send a string on the LCD
 * 
 * @param String: The string to be sent ("Example")
 */
void LCD_writeString(u8* String)
{
	if(String != NULL)
	{
		u8 stringLength = 0;
	   while(String[stringLength] != '\0')
	  {
		 LCD_sendChar(String[stringLength]);
		 ++stringLength;
	  }
	}
}

/**
 * @brief: A function that write numbers on LCD
 * 
 * @param number: The number to be written
 */
void LCD_writeNumber(u32 number)
{
	u32 Local_reversed = 1;
	if (number == 0)
	{
		LCD_sendChar('0');
	}
	else
	{
		// Reverse Number
		while (number != 0)
		{
			Local_reversed = Local_reversed*10 + (number%10);
			number /= 10;
		}
		
		do 
		{
			LCD_sendChar((Local_reversed%10)+'0');
			Local_reversed /= 10;
		}while (Local_reversed != 1);
	} 
}

/**
 * @brief: A function that clears the LCD
 * 
 */
void LCD_clear(void)
{
	// Clear Display
	LCD_sendCmnd(0b00000001);
	_delay_ms(2);
}

/**
 * @brief: A function that moves the curser to left or right
 * 
 * @param shifttingDirection: The direction
 */
void LCD_shift(u8 shifttingDirection)
{
	if (shifttingDirection == LCD_SHIFT_LEFT)
	{
		LCD_sendCmnd(0b00011000);
		_delay_ms(10);
	}
	else if (shifttingDirection == LCD_SHIFT_RIGHT)
	{
		LCD_sendCmnd(0b00011100);
		_delay_ms(10);
	}
}

/**
 * @brief: A function that move the curser to a specific location
 * 
 * @param LineNumber: Which line
 * @param Position: Which position
 */
void LCD_goToSpecificPosition(u8 LineNumber, u8 Position)
{
	if(LineNumber == LCD_LINE_ONE)
	{
		if(Position <= 15)
		{
			LCD_sendCmnd(0x80 + Position);
		}
	}

	else if (LineNumber == LCD_LINE_TWO)
	{
		if(Position <= 15)
		{
			LCD_sendCmnd(0xc0 + Position);
		}
	}
}

/**
 * @brief: A static function to write a half port in LCD if needed
 * 
 * @param value: The value to be written
 */
static void writeHalfPort(u8 Value)
{
	if (0 == GET_BIT(Value, 0))
	{
		DIO_SET_PIN_VAL(LCD_D4_PORT, LCD_D4_PIN, DIO_PIN_LOW);
	}
	else 
	{
		DIO_SET_PIN_VAL(LCD_D4_PORT, LCD_D4_PIN, DIO_PIN_HIGH);
	}
	
	if (0 == GET_BIT(Value, 1))
	{
		DIO_SET_PIN_VAL(LCD_D5_PORT, LCD_D5_PIN, DIO_PIN_LOW);
	}
	else 
	{
		DIO_SET_PIN_VAL(LCD_D5_PORT, LCD_D5_PIN, DIO_PIN_HIGH);
	}
	
	if (0 == GET_BIT(Value, 2))
	{
		DIO_SET_PIN_VAL(LCD_D6_PORT, LCD_D6_PIN, DIO_PIN_LOW);
	}
	else 
	{
		DIO_SET_PIN_VAL(LCD_D6_PORT, LCD_D6_PIN, DIO_PIN_HIGH);
	}
	
	if (0 == GET_BIT(Value, 3))
	{
		DIO_SET_PIN_VAL(LCD_D7_PORT, LCD_D7_PIN, DIO_PIN_LOW);
	}
	else 
	{
		DIO_SET_PIN_VAL(LCD_D7_PORT, LCD_D7_PIN, DIO_PIN_HIGH);
	}
}