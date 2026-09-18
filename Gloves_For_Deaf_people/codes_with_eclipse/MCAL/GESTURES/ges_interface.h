/*
 * ges_interface.h
 *
 *  Created on: Sep 14, 2026
 *      Author: jana
 */

#ifndef HAL_GESTURES_GES_INTERFACE_H_
#define HAL_GESTURES_GES_INTERFACE_H_

#include "../../lib/STD_Types.h"
#include "../TOUCH/tch_interface.h"

#define Threshold 6000

#define FLAT  0
#define RIGHT 1
#define LEFT  2
#define UP    3
#define DOWN  4

typedef struct {
	u8 hall[5];
	u8 mpu;
	u8 touch;
	u8 sent_no;
}Gesture;

u8 Gest_accDir(s16 accX, s16 accY, s16 accZ);
u8 Gest_Detect(u8* gest_hall ,u8 gest_mpu , u8 gest_touch);

#endif /* HAL_GESTURES_GES_INTERFACE_H_ */
