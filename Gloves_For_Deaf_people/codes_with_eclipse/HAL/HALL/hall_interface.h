/*
 * hall_interface.h
 *
 *  Created on: Sep 11, 2026
 *      Author: jana
 */

#ifndef HAL_HALL_HALL_INTERFACE_H_
#define HAL_HALL_HALL_INTERFACE_H_

#include "../../MCAL/ADC/adc_interface.h"

#define F1 ADC_CHANNEL0
#define F2 ADC_CHANNEL1
#define F3 ADC_CHANNEL2
#define F4 ADC_CHANNEL3
#define F5 ADC_CHANNEL4

void HALL_Init (void);
void HALL_Read (u8* fingerRange);


#endif /* HAL_HALL_HALL_INTERFACE_H_ */
