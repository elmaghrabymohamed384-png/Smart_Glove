/*
 * hall_program.c
 *
 *  Created on: Sep 11, 2026
 *      Author: jana
 */


#include "hall_interface.h"
#include "../../MCAL/ADC/adc_interface.h"
#include "../../MCAL/DIO/interface.h"

void HALL_Init (void){
	ADC_Init();

	DIO_Set_Pin_Value (PORTA,PIN0,PIN_LOW);
	DIO_Set_Pin_Value (PORTA,PIN1,PIN_LOW);
	DIO_Set_Pin_Value (PORTA,PIN2,PIN_LOW);
	DIO_Set_Pin_Value (PORTA,PIN3,PIN_LOW);
	DIO_Set_Pin_Value (PORTA,PIN4,PIN_LOW);
}

static u8 HALL_AnalogRange (u16 channel){
	u16 Analog = 0, Digital = 0;
		u8 range = 0;

		Digital = ADC_GetDigitalValue(channel);
		Analog = ((Digital * 5000UL) / 1024);

		if (Analog >= 3833) {
			range = 2;
		} else if (Analog >= 3167) {
			range = 1;
		} else {
			range = 0;
		}
		return range;
}

void HALL_Read (u8* fingerRange){

	fingerRange[0]=HALL_AnalogRange(F1);
	fingerRange[1]=HALL_AnalogRange(F2);
	fingerRange[2]=HALL_AnalogRange(F3);
	fingerRange[3]=HALL_AnalogRange(F4);
	fingerRange[4]=HALL_AnalogRange(F5);

}


