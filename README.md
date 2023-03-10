"# SmartHome_EmbeddedSystems" 
Authers:
1. Mohamed Mousa   -> moh.hassan.2000@gmail.com
2. Mohamed Ibrahim -> mi8651937@gmail.com

Description:

This project is built using AVR ATmega32.
The project is a smart home that has database for the house owners that's represented in EEPROM.
There's a security system algorithm that prevent anyone from logging into the system except the users and the admin.
The admin can communicate with the system using mobile application and through UART communication protocol using a bluetooth module.
The EEPROM can be accessed through TWI (I2C) communication protocol.
The user can access the system using only keypad and LCD, and that will be done through the admin.
The admin and the user can control 5 LEDS including a dimmer circuit, and only the admin can control the door of the house.
There's an option in the admin mode to add any users, or to remove any user.
The system will breakdown if anyone tried 3 times to access and failed.
There's a simulation of a temprature sensor represented in potentiometer, if the temprature is above 28 C, the aircodtioning will start, and it will stop when the temprature be below 22 C.
