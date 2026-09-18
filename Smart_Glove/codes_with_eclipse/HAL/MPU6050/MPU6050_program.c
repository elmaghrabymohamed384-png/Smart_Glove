#include "MPU6050_interface.h"

#define REG_PWR_MGMT_1   0x6B
#define REG_ACCEL_XOUT_H 0x3B
#define REG_GYRO_XOUT_H  0x43

static void WriteReg(u8 reg, u8 val)
{
    I2C_SendSTARTCond();
    I2C_SendSlaveADD_Write(MPU6050_I2C_ADDRESS);
    I2C_SendDATA(reg);
    I2C_SendDATA(val);
    I2C_SendSTOPCond();
}

static void ReadBurst(u8 startReg, s16 *x, s16 *y, s16 *z)
{
    u8 h, l;

    I2C_SendSTARTCond();
    I2C_SendSlaveADD_Write(MPU6050_I2C_ADDRESS);
    I2C_SendDATA(startReg);

    I2C_Send_repeatedSTARTCond();
    I2C_SlaveADD_Read(MPU6050_I2C_ADDRESS);

    I2C_ReadDATA(&h);      I2C_ReadDATA(&l);      *x = (s16)((h << 8) | l);
    I2C_ReadDATA(&h);      I2C_ReadDATA(&l);      *y = (s16)((h << 8) | l);
    I2C_ReadDATA(&h);      I2C_ReadLastDATA(&l);  *z = (s16)((h << 8) | l);   /* NACK */

    I2C_SendSTOPCond();
}

void MPU6050_voidInit(void)
{
    WriteReg(REG_PWR_MGMT_1, 0x00);
    /* مش بننادي I2C_MasterInit هنا — main هي اللي بيناديها */
}

void MPU6050_voidReadAccel(s16 *X, s16 *Y, s16 *Z) { ReadBurst(REG_ACCEL_XOUT_H, X, Y, Z); }
void MPU6050_voidReadGyro (s16 *X, s16 *Y, s16 *Z) { ReadBurst(REG_GYRO_XOUT_H,  X, Y, Z); }
