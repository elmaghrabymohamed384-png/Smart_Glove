/*
 * UART_program.c
 *
 *  Created on: Sep 6, 2026
 *      Author: jana
 */
#define F_CPU   8000000UL

#include <util/delay.h>
#include "UART_private.h"
#include "UART_interface.h"
#include "UART_config.h"
#include "../../lib/BIT_MATH.h"
#include "../../lib/STD_Types.h"

void UART_Init(void){
	UBRRL= (u8)UBRR_VALUE ;
	UBRRH= (u8)(UBRR_VALUE>>8) ;

    UCSRB=(1<<RXEN)|(1<<TXEN)|(0<<UCSZ2);

    UCSRC=(1<<URSEL)|(0<<UMSEL)|(0<<UPM1)|(0<<UPM0)|(0<<USBS)|(1<<UCSZ1)|(1<<UCSZ0);

}

void UART_SendData (u8 data){

	while(GET_BIT(UCSRA,UDRE) == 0);   //POLLING IF THE UDR EMPTY

	UDR=data;
}


u8 UART_RecieveData(void){

	while (GET_BIT(UCSRA,RXC) == 0);  //POLLING IF RXC HAVE DATA

	return UDR;
}


void UART_PrintData(u8 PrintData[]){

    u8 i=0;
    while(PrintData[i] !='\0'){

    	UART_SendData(PrintData[i]);
    	i++;
    }
}





