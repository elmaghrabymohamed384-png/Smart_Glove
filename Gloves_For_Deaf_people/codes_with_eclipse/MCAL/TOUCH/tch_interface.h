/*
 * tch_interface.h
 *
 *  Created on: Sep 14, 2026
 *      Author: jana
 */

#ifndef HAL_TOUCH_TCH_INTERFACE_H_
#define HAL_TOUCH_TCH_INTERFACE_H_

#include "../../lib/STD_Types.h"

#define T_NONE 0x00

#define T1 0x01
#define T2 0x02
#define T4 0x04
#define T8 0x07


void TOUCH_Init(void);
u8 TOUCH_Read(void);

#endif
