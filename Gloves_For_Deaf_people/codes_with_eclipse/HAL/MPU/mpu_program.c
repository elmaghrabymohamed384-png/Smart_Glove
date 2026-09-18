/*
 * mpu_program.c
 *
 *  Created on: Sep 11, 2026
 *      Author: jana
 */

#include "mpu_interface.h"
#include "mpu_private.h"
#include "../../lib/STD_Types.h"
#include "../../MCAL/DIO/interface.h"
#include "../../MCAL/I2C/I2C_interface.h"

void MPU_Init (void){

	I2C_MasterInit();
	I2C_SendSTARTCond();
	I2C_SendSlaveADD_Write(MPU6050_ADDRESS);
	I2C_SendDATA(PWR_MGMT_1);
	I2C_SendDATA(WAKE_UP_VALUE);
	I2C_SendSTOPCond();
}

u8 MPU_Acc(s16* AccX ,s16* AccY ,s16* AccZ ){
    u8 xaH,xaL,yaH,yaL,zaH,zaL;

    I2C_SendSTARTCond() ;
    I2C_SendSlaveADD_Write(MPU6050_ADDRESS);
    I2C_SendDATA(ACCEL_XOUT_H);

    I2C_Send_repeatedSTARTCond();
    I2C_SlaveADD_Read(MPU6050_ADDRESS);
    I2C_ReadDATA(&xaH);
    I2C_ReadDATA(&xaL);
    I2C_ReadDATA(&yaH);
    I2C_ReadDATA(&yaL);
    I2C_ReadDATA(&zaH);
    I2C_ReadDATA(&zaL);

    I2C_SendSTOPCond();

    *AccX=(xaH<<8)|xaL;
    *AccY=(yaH<<8)|yaL;
    *AccZ=(zaH<<8)|zaL;

    return 0;
}
u8 MPU_Gyro(s16* GyroX ,s16* GyroY ,s16* GyroZ ){
u8 xgH,xgL,ygH,ygL,zgH,zgL;
	  I2C_SendSTARTCond();
	  I2C_SendSlaveADD_Write(MPU6050_ADDRESS);
	  I2C_SendDATA(GYRO_XOUT_H);

	  I2C_Send_repeatedSTARTCond();
	  I2C_SlaveADD_Read(MPU6050_ADDRESS);
	  I2C_ReadDATA(&xgH);
	  I2C_ReadDATA(&xgL);
	  I2C_ReadDATA(&ygH);
	  I2C_ReadDATA(&ygL);
	  I2C_ReadDATA(&zgH);
	  I2C_ReadDATA(&zgL);

	  I2C_SendSTOPCond();

	  *GyroX=(xgH<<8)|xgL;
	  *GyroY=(ygH<<8)|ygL;
	  *GyroZ=(zgH<<8)|zgL;


      return 0;
}





