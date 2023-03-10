"# SmartHome_EmbeddedSystems" 
Authers:
1. Mohamed Mousa    -> moh.hassan.2000@gmail.com
2. Mohamed Ibrahim -> mi8651937@gmail.com

Description:

1. Before applying this project, please uncomment the DatabaseRest() function and turn off the system, then comment it again, and uncomment the SignUp(AdminActive) function, to assign new admin, then turn off the system, and comment the SignUp(ActiveAdmin) function to be ready for use (This is the pre-use process to prepare the system for new home)

2.This project is built using AVR ATmega32.

3. The project is a smart home that has database for the house owners that's represented in EEPROM.

4.There's a security system algorithm that prevent anyone from logging into the system except the users and the admin.

5.The admin can communicate with the system using mobile application and through UART communication protocol using a bluetooth module.

6.The EEPROM can be accessed through TWI (I2C) communication protocol.


7.The user can access the system using only keypad and LCD, and that will be done through the admin.

8.The admin and the user can control 5 LEDS including a dimmer circuit, and only the admin can control the door of the house.

9.There's an option in the admin mode to add any users, or to remove any user.

10.The system will breakdown if anyone tried 3 times to access and failed.

11.There's a simulation of a temprature sensor represented in potentiometer, if the temprature is above 28 C, the aircodtioning will start, and it will stop when the temprature be below 22 C.
