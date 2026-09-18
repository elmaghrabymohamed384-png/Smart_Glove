/*
t * interface.h
 *
 *  Created on: Aug 23, 2026
 *      Author: jana
 */

#ifndef MCAL_DIO_INTERFACE_H_
#define MCAL_DIO_INTERFACE_H_

#include "../../lib/STD_Types.h"


#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3

#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

#define PIN_INPUT 0
#define PIN_OUTPUT 1

#define PIN_LOW 0
#define PIN_HIGH 1

#define PORT_INPUT 0x00
#define PORT_OUTPUT 0xff

#define PORT_LOW 0x00
#define PORT_HIGH 0xff


void DIO_Set_Pin_Direction (u8 port , u8 pin,u8 direction);
void DIO_Set_Pin_Value (u8 port , u8 pin,u8 value);
u8   DIO_GET_Pin_Value (u8 port, u8 pin );


void DIO_Set_Port_Direction (u8 port , u8 direction);
void DIO_Set_Port_Value (u8 port ,u8 value);


#endif /* MCAL_DIO_INTERFACE_H_ */
