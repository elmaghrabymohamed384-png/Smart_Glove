/*
 * program.c
 *
 *  Created on: Aug 23, 2026
 *      Author: jana
 */
#include "../../lib/BIT_MATH.h"
#include "private.h"
#include "interface.h"

void DIO_Set_Pin_Direction(u8 port, u8 pin, u8 direction)
{
    if(direction == PIN_OUTPUT)
    {
        switch(port)
        {
            case PORTA: SET_BIT(DDRA_Register, pin); break;
            case PORTB: SET_BIT(DDRB_Register, pin); break;
            case PORTC: SET_BIT(DDRC_Register, pin); break;
            case PORTD: SET_BIT(DDRD_Register, pin); break;
        }
    }
    else if(direction == PIN_INPUT)
    {
        switch(port)
        {
            case PORTA: CLR_BIT(DDRA_Register, pin); break;
            case PORTB: CLR_BIT(DDRB_Register, pin); break;
            case PORTC: CLR_BIT(DDRC_Register, pin); break;
            case PORTD: CLR_BIT(DDRD_Register, pin); break;
        }
    }
}


void DIO_Set_Pin_Value(u8 port, u8 pin, u8 value)
{

	if(value == PIN_HIGH){

		switch(port) {
		case PORTA : SET_BIT (PORTA_Register , pin);
		break;
		case PORTB: SET_BIT(PORTB_Register , pin);
				break;
		case PORTC : SET_BIT(PORTC_Register , pin);
				break;
		case PORTD : SET_BIT(PORTD_Register , pin);
				break;

		}

	}
	else if (value == PIN_LOW){

		switch(port) {
		case PORTA : CLR_BIT(PORTA_Register , pin);
		break;
		case PORTB: CLR_BIT(PORTB_Register , pin);
		break;
		case PORTC : CLR_BIT(PORTC_Register , pin);
		break;
		case PORTD : CLR_BIT(PORTD_Register , pin);
		break;

	   }
	}
}
u8 DIO_GET_Pin_Value(u8 port, u8 pin ) {

	u8 value=PIN_LOW;

		switch (port) {
			case PORTA:
			value= GET_BIT(PINA_Register, pin);
			break;
			case PORTB:
		    value= GET_BIT(PINB_Register, pin);
			break;
			case PORTC:
			value= GET_BIT(PINC_Register, pin);
			break;
			case PORTD:
			value= GET_BIT(PIND_Register, pin);
			break;
		}
     return value;

}

void DIO_Set_Port_Direction (u8 port , u8 direction)
{
	if((port>=PORTA) && (port<=PORTD))
	    {
	        switch(port)
	        {
	            case PORTA: DDRA_Register = direction; break;
	            case PORTB: DDRB_Register = direction; break;
	            case PORTC: DDRC_Register = direction; break;
	            case PORTD: DDRD_Register = direction; break;
	        }

	    }

}
void DIO_Set_Port_Value (u8 port ,u8 value)
{
	if( (port>=PORTA) && (port<=PORTD) )

    {
    switch(port)
    {
        case PORTA: PORTA_Register = value; break;
        case PORTB: PORTB_Register = value; break;
        case PORTC: PORTC_Register = value; break;
        case PORTD: PORTD_Register = value; break;
    }
    }
}




