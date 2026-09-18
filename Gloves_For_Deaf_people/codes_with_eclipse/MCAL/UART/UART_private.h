/*
 * UART_private.h
 *
 *  Created on: Sep 6, 2026
 *      Author: jana
 */

#ifndef MCAL_UART_UART_PRIVATE_H_
#define MCAL_UART_UART_PRIVATE_H_

#define UDR *((volatile u8 *)0x2C)

#define TXB   0
#define RXB   1

#define UCSRA *((volatile u8 *)0x2B)
#define MPCM   0
#define U2X    1
#define PE     2
#define DOR    3
#define FE     4
#define UDRE   5
#define TXC    6
#define RXC    7

#define UCSRB *((volatile u8 *)0x2A)
#define TXB8   0
#define RXB8   1
#define UCSZ2  2
#define TXEN   3
#define RXEN   4
#define UDRIE  5
#define TXCIE  6
#define RXCIE  7

#define UCSRC *((volatile u8 *)0x40)
#define UCPOL  0
#define UCSZ0  1
#define UCSZ1  2
#define USBS   3
#define UPM0   4
#define UPM1   5
#define UMSEL  6
#define URSEL  7

#define UBRR_VALUE  (Fosc/16/BaudRate-1)

#define UBRRL *((volatile u8 *)0x29)

#define UBRRH *((volatile u8 *)0x40)
#define URSEL  7

#endif /* MCAL_UART_UART_PRIVATE_H_ */

