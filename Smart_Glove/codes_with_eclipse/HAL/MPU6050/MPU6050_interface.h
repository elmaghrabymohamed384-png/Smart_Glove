#ifndef MPU6050_INTERFACE_H
#define MPU6050_INTERFACE_H

#include "../../lib/STD_Types.h"
#include "../../MCAL/I2C/I2C_interface.h"


#define MPU6050_I2C_ADDRESS   0x68

void MPU6050_voidInit(void);
void MPU6050_voidReadAccel(s16 *X, s16 *Y, s16 *Z);
void MPU6050_voidReadGyro (s16 *X, s16 *Y, s16 *Z);

#endif
