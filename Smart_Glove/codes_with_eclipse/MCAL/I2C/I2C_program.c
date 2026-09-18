#include "I2C_interface.h"
#include "I2C_private.h"
#include "../../lib/STD_Types.h"
#include "../../lib/BIT_MATH.h"

#define I2C_TIMEOUT   40000

void I2C_MasterInit(void)
{
    CLR_BIT(TWSR, TWPS0);
    CLR_BIT(TWSR, TWPS1);
    TWBR = 32;
    SET_BIT(TWCR, TWEA);
    SET_BIT(TWCR, TWEN);
}

I2C_Error_State I2C_SendSTARTCond(void)
{
    u16 to = I2C_TIMEOUT;
    TWCR = (1<<TWSTA) | (1<<TWINT) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT)) && to) to--;
    if (!to) return I2C_SC_Error;
    if ((TWSR & 0xF8) != STAcond_ACK) return I2C_SC_Error;
    return I2C_Ok;
}

I2C_Error_State I2C_Send_repeatedSTARTCond(void)
{
    u16 to = I2C_TIMEOUT;
    TWCR = (1<<TWSTA) | (1<<TWINT) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT)) && to) to--;
    if (!to) return I2C_RSC_Error;
    if ((TWSR & 0xF8) != Re_STAcond_ACK) return I2C_RSC_Error;
    return I2C_Ok;
}

I2C_Error_State I2C_SendSlaveADD_Write(u8 address)
{
    u16 to = I2C_TIMEOUT;
    TWDR = address << 1;
    CLR_BIT(TWDR, 0);
    TWCR = (1<<TWINT) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT)) && to) to--;
    if (!to) return I2C_MT_SLA_W_Error;
    if ((TWSR & 0xF8) != SLA_W_ACK) return I2C_MT_SLA_W_Error;
    return I2C_Ok;
}

I2C_Error_State I2C_SlaveADD_Read(u8 slaveAdd)
{
    u16 to = I2C_TIMEOUT;
    TWDR = slaveAdd << 1;
    SET_BIT(TWDR, 0);
    TWCR = (1<<TWINT) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT)) && to) to--;
    if (!to) return I2C_MR_SLA_R_Error;
    if ((TWSR & 0xF8) != SLA_R_ACK) return I2C_MR_SLA_R_Error;
    return I2C_Ok;
}

I2C_Error_State I2C_SendDATA(u8 data)
{
    u16 to = I2C_TIMEOUT;
    TWDR = data;
    TWCR = (1<<TWINT) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT)) && to) to--;
    if (!to) return I2C_MT_Data_Error;
    if ((TWSR & 0xF8) != TransData_ACK) return I2C_MT_Data_Error;
    return I2C_Ok;
}

I2C_Error_State I2C_ReadDATA(u8 *returnData)
{
    u16 to = I2C_TIMEOUT;
    TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT)) && to) to--;
    if (!to) return I2C_MR_Data_Error;
    if ((TWSR & 0xF8) != ReceiveData_ACK) return I2C_MR_Data_Error;
    *returnData = TWDR;
    return I2C_Ok;
}

I2C_Error_State I2C_ReadLastDATA(u8 *returnData)
{
    u16 to = I2C_TIMEOUT;
    TWCR = (1<<TWINT) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT)) && to) to--;
    if (!to) return I2C_MR_Data_Error;
    if ((TWSR & 0xF8) != ReceiveData_NACK) return I2C_MR_Data_Error;
    *returnData = TWDR;
    return I2C_Ok;
}

void I2C_SendSTOPCond(void)
{
    TWCR = (1<<TWSTO) | (1<<TWINT) | (1<<TWEN);
}
