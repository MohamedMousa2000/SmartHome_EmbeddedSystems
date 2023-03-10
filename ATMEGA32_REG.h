/*
 * ATMEGA32_REG.h
 *
 * Created: 10/22/2022 11:12:42 PM
 * Author: Mohamed Mousa & Mohamed Ibrahim
 */ 


#ifndef ATMEGA32_REG_H_
#define ATMEGA32_REG_H_

#include "DATA_TYPES.h"

/********** DIO ***********/
/* Port A Registers */
#define PORTA     (*(volatile u8*)0x3B)
#define DDRA      (*(volatile u8*)0x3A)
#define PINA      (*(volatile u8*)0x39)
/* Port B Registers */
#define PORTB     (*(volatile u8*)0x38)
#define DDRB      (*(volatile u8*)0x37)
#define PINB      (*(volatile u8*)0x36)
/* Port C Registers */
#define PORTC     (*(volatile u8*)0x35)
#define DDRC      (*(volatile u8*)0x34)
#define PINC      (*(volatile u8*)0x33)
/* Port D Registers */
#define PORTD     (*(volatile u8*)0x32)
#define DDRD      (*(volatile u8*)0x31)
#define PIND      (*(volatile u8*)0x30)
  
/********** INTERRUPTS ***********/
/* Global Interrupt Register (SREG) */
#define SREG      (*(volatile u8*)0x5F)
/* External Interrupt Registers */
#define MCUCR     (*(volatile u8*)0x55)
#define MCUCSR    (*(volatile u8*)0x54)
#define GICR      (*(volatile u8*)0x5B)
#define GIFR      (*(volatile u8*)0x5A)
  
/********** ADC ***********/
/* ADC MUX Selection REG */
#define ADMUX     (*(volatile u8*)0x27)
/* ADC Control and Status REG B */
#define ADCSRA    (*(volatile u8*)0x26)
/* ADC Data REG */
#define ADCL      (*(volatile u8*)0x24)
#define ADCH      (*(volatile u8*)0x25)
#define ADC_U16   (*(volatile u16*)0x24)
/* Special Function IO */
#define SFIOR     (*(volatile u8*)0x50)
  
/********** TIMERS ***********/
 
/* Timer/Counter  Interrupt Mask Register */
#define TIMSK     (*(volatile u8*)0x59)
/* Timer/Counter  Interrupt Flag Register */
#define TIFR      (*(volatile u8*)0x58)
          
          /*TIMER  0*/
 
/* Timer/Counter  (0) Control Register */
#define TCCR0     (*(volatile u8*)0x53)
/* Timer/Counetr  (0) Register */
#define TCNT0     (*(volatile u8*)0x52)
/* Output Compare (0) Register */
#define OCR0      (*(volatile u8*)0x5C)
 
           /*TIMER 1*/
            
/* Timer/Counter  (1A) Control Register */
#define TCCR1A    (*(volatile u8*)0x4F)
/* Timer/Counter  (1B) Control Register */
#define TCCR1B    (*(volatile u8*)0x4E)
/* Timer/Counter (1) Register (L and H in one REG in L)*/
/* As they come after each other */
#define TCNT1_u16 (*(volatile u16*)0x4C)
/* Output Compare (1A) Register (L and H in one REG in L) */
/* As they come after each other */
#define OCR1A_u16 (*(volatile u16*)0x4A)
/* Output Compare (1B) Register (L and H in one REG in L) */
/* As they come after each other */
#define OCR1B_u16 (*(volatile u16*)0x48)
/* Input Capture Unit Register (L and H in one REG in L) */
/* As they come after each other */
#define ICR1_u16  (*(volatile u16*)0x46)

/********** UART ***********/
/* DATA Register */
#define UDR       (*(volatile u8*)0x2C)
/* Control and Status Registers */
#define UCSRA     (*(volatile u8*)0x2B)
#define UCSRB     (*(volatile u8*)0x2A)
#define UCSRC     (*(volatile u8*)0x40)
/* Baud Rate Register */
#define UBRRH     (*(volatile u8*)0x40)
#define UBRRL     (*(volatile u8*)0x29)

/********** SPI ***********/
/* DATA Register */
#define SPDR      (*(volatile u8*)0x2F)
/* Control and Status Registers */
#define SPCR      (*(volatile u8*)0x2D)
/* Status Register */
#define SPSR      (*(volatile u8*)0x2E)

/********** TWI (I2C) ***********/
/* Bit Rate Register */
#define TWBR      (*(volatile u8*)0x20)
/* Control Register */
#define TWCR      (*(volatile u8*)0x56)
/* Status Register */
#define TWSR      (*(volatile u8*)0x21)
/* Data Register */
#define TWDR      (*(volatile u8*)0x23)
/* (Slave) Adress Register */
#define TWAR      (*(volatile u8*)0x22)

/********** EEPROM ***********/
#define EEAR      (*(volatile u16*)0x3E)
#define EEDR      (*(volatile u8*)0x3D)
#define EECR      (*(volatile u8*)0x3C)

#endif /* ATMEGA32_REG_H_ */