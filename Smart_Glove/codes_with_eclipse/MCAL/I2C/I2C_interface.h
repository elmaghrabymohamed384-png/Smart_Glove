/*
 * I2C_interface.h
 *
 *  Created on: Sep 8, 2026
 *      Author: jana
 */

#ifndef MCAL_I2C_I2C_INTERFACE_H_
#define MCAL_I2C_I2C_INTERFACE_H_

#include "../../lib/STD_Types.h"

typedef enum
{
	I2C_Ok,
	I2C_SC_Error,
	I2C_RSC_Error,
	I2C_MT_SLA_W_Error,
	I2C_MR_SLA_R_Error,
	I2C_MT_Data_Error,
	I2C_MR_Data_Error
}I2C_Error_State;

void I2C_MasterInit (void);
I2C_Error_State I2C_SendSTARTCond (void) ;
I2C_Error_State I2C_Send_repeatedSTARTCond (void) ;
I2C_Error_State I2C_SendSlaveADD_Write (u8 address);
I2C_Error_State I2C_SlaveADD_Read (u8 slaveAdd);
I2C_Error_State I2C_SendDATA (u8 data);
I2C_Error_State I2C_ReadDATA (u8 *returnData);
I2C_Error_State I2C_ReadLastDATA(u8 *returnData);
void I2C_SendSTOPCond (void);

#endif /* MCAL_I2C_I2C_INTERFACE_H_ */
