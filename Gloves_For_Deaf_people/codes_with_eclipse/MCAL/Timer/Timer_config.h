/*
 * Timer_config.h
 *
 *  Created on: Sep 13, 2026
 *      Author: m7dm
 */

#ifndef TIMER_TIMER_CONFIG_H_
#define TIMER_TIMER_CONFIG_H_


#define TIMER0_PRESCALER 64



#define TIMER0_OCR_VALUE     ((F_CPU / TIMER0_PRESCALER / 1000UL) - 1)

#endif



