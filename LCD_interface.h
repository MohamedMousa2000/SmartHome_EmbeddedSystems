/*
 * LCD_interface.h
 *
 * Created: 9/11/2022 11:28:58 AM
 * Author: Mohamed Mousa & Mohamed Ibrahim
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#define LCD_8_BIT_MODE          1 
#define LCD_4_BIT_MODE          2

/* Macros For LCD Line Id */
#define LCD_LINE_ONE            1
#define LCD_LINE_TWO            2

/* Macros For LCD Shifting Direction */
#define LCD_SHIFT_LEFT          0
#define LCD_SHIFT_RIGHT         1

/**
 * @brief: A function that initializes the LCD
 * 
 */
void LCD_init(void);

/**
 * @brief: A function that send a certain command to the LCD
 * 
 * @param Cmnd: The command to be sent
 */
void LCD_sendCmnd(u8 Cmnd);

/**
 * @brief: A function that send a certain character to the LCD
 * 
 * @param data: The character to be sent
 */
void LCD_sendChar(u8 data);

/**
 * @brief: A static function to write a half port in LCD if needed
 * 
 * @param value: The value to be written
 */
static void writeHalfPort(u8 value);

/**
 * @brief: A function that send a string on the LCD
 * 
 * @param String: The string to be sent ("Example")
 */
void LCD_writeString(u8* String);

/**
 * @brief: A function that write numbers on LCD
 * 
 * @param number: The number to be written
 */
void LCD_writeNumber(u32 number);

/**
 * @brief: A function that clears the LCD
 * 
 */
void LCD_clear(void);

/**
 * @brief: A function that moves the curser to left or right
 * 
 * @param shifttingDirection: The direction
 */
void LCD_shift(u8 shifttingDirection);

/**
 * @brief: A function that move the curser to a specific location
 * 
 * @param LineNumber: Which line
 * @param Position: Which position
 */
void LCD_goToSpecificPosition(u8 LineNumber, u8 Position);
/*void LCD_writeSpecialChar(u8 *pattern, u8 charPosition, u8 LineNumber, u8 Position);*/

#endif /* LCD_INTERFACE_H_ */