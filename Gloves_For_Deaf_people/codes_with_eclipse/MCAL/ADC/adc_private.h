/*
 * adc_private.h
 *
 *  Created on: Sep 2, 2026
 *      Author: jana
 */

#ifndef MCAL_ADC_ADC_PRIVATE_H_
#define MCAL_ADC_ADC_PRIVATE_H_

#define ADMUX   (*(volatile u8*)0x27)
#define ADCH    (*(volatile u8*)0x25)
#define ADCL    (*(volatile u8*)0x24)
#define ADCSRA  (*(volatile u8*)0x26)
#define ADCSRA  (*(volatile u8*)0x26)

#define ADC     *((volatile u16*)0x24)

//ADMUX BITS
#define ADMUX_CHANNEL_MASK  0b11100000
#define ADLAR 5
#define REFS0 6
#define REFS1 7

//ADCSRA BITS
#define ADPS0 0
#define ADPS1 1
#define ADPS2 2
#define ADIE  3
#define ADIF  4
#define ADATE 5
#define ADSC  6
#define ADEN  7


#endif /* MCAL_ADC_ADC_PRIVATE_H_ */
