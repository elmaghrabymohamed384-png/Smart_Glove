/*
 * adc_interface.h
 *
 *  Created on: Sep 2, 2026
 *      Author: jana
 */

#ifndef MCAL_ADC_ADC_INTERFACE_H_
#define MCAL_ADC_ADC_INTERFACE_H_

#include "../../lib/STD_Types.h"
typedef enum {

	ADC_CHANNEL0,
	ADC_CHANNEL1,
	ADC_CHANNEL2,
	ADC_CHANNEL3,
	ADC_CHANNEL4,
	ADC_CHANNEL5,
	ADC_CHANNEL6,
	ADC_CHANNEL7

} ADC_CHANNELS;


void ADC_Init(void);
u16 ADC_GetDigitalValue(ADC_CHANNELS channel_num);   //READ from the CHANNEL


#endif /* MCAL_ADC_ADC_INTERFACE_H_ */
