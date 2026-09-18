/*
 * UART_interface.h
 *
 *  Created on: Sep 6, 2026
 *      Author: jana
 */

#ifndef MCAL_UART_UART_INTERFACE_H_
#define MCAL_UART_UART_INTERFACE_H_

#include "../../lib/STD_Types.h"

#define ParityDis    0
#define ParityEven   2
#define ParityOdd    3

#define Asynchronous 0
#define Synchronous  1

#define StopBit1     0
#define StopBit2     1

#define DataBit5     5
#define DataBit6     6
#define DataBit7     7
#define DataBit8     8
#define DataBit9     9

void UART_Init (void);
void UART_SendData (u8 data);
u8 UART_RecieveData (void);
void UART_PrintData(u8 PrintData[]);


#endif /* MCAL_UART_UART_INTERFACE_H_ */
