/*
 * Timer_interface.h
 *
 *  Created on: Sep 13, 2026
 *      Author: m7dm
 */

#ifndef TIMER_TIMER_INTERFACE_H_
#define TIMER_TIMER_INTERFACE_H_
#include "../../lib/STD_Types.h"

void Timer_voidInit(void);
void Timer_voidDelayMs(u16 Copy_u16Ms);
u32  Timer_u32GetTick(void);



#endif /* TIMER_TIMER_INTERFACE_H_ */
