/*
 * mpu_interface.h
 *
 *  Created on: Sep 11, 2026
 *      Author: jana
 */

#ifndef HAL_MPU_MPU_INTERFACE_H_
#define HAL_MPU_MPU_INTERFACE_H_

#include"../../lib/STD_Types.h"


void MPU_Init (void);
u8 MPU_Acc(s16* AccX ,s16* AccY ,s16* AccZ );
u8 MPU_Gyro(s16* GyroX ,s16* GyroY ,s16* GyroZ );

#endif /* HAL_MPU_MPU_INTERFACE_H_ */
