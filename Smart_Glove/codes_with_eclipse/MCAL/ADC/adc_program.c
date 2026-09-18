/*
 * adc_program.c
 *
 *  Created on: Sep 2, 2026
 *      Author: jana
 */

#include "adc_private.h"
#include "adc_interface.h"
#include "../../lib/BIT_MATH.h"
#include "../../lib/STD_Types.h"
#include "../../MCAL/DIO/interface.h"

void ADC_Init(void){
	SET_BIT(ADCSRA,ADEN);

	CLR_BIT(ADMUX,ADLAR);    //LOW REG

	SET_BIT(ADMUX,REFS0);    //VCC+cap
    CLR_BIT(ADMUX,REFS1);

    SET_BIT(ADCSRA,ADPS0);   //Prescaler=8
    SET_BIT(ADCSRA,ADPS1);
    CLR_BIT(ADCSRA,ADPS2);

}

u16 ADC_GetDigitalValue(ADC_CHANNELS channel_num){

	 ADMUX &=ADMUX_CHANNEL_MASK;        //CLEAR channel no. bits
	 ADMUX |=channel_num;               //CHOOSE the channel

	 SET_BIT(ADCSRA,ADSC);              //Start conversion

	 u8 flag=0;
	 while(flag== 0){
		 flag=GET_BIT(ADCSRA,ADIF) ;    //Polling on flag
	 }
	 SET_BIT(ADCSRA,ADIF);

	 return ADC;
}


