/*
 * LCD_I2C_program.c
 *
 *  Created on: Sep 13, 2026
 *      Author: m7dm
 */

#include "LCD_I2C_config.h"
#include "LCD_I2C_interface.h"
#include "LCD_I2C_private.h"
#include "../../MCAL/I2C/I2C_interface.h"
#include "../../MCAL/Timer/Timer_interface.h"

/* ============ دوال داخلية ============ */

static void WriteRaw(u8 Copy_u8Value)
{
    I2C_SendSTARTCond();
    I2C_SendSlaveADD_Write(LCD_I2C_ADDRESS);
    I2C_SendDATA(Copy_u8Value);
    I2C_SendSTOPCond();
}

static void PulseEnable(u8 Copy_u8Value)
{
    WriteRaw(Copy_u8Value | (1 << LCD_I2C_EN_BIT));
    WriteRaw(Copy_u8Value & ~(1 << LCD_I2C_EN_BIT));
}

static void SendNibble(u8 Copy_u8Nibble, u8 Copy_u8IsData)
{
    u8 Local_u8Value = (Copy_u8Nibble << 4) | LCD_I2C_BACKLIGHT_ON;

    if (Copy_u8IsData)
    {
        Local_u8Value |= (1 << LCD_I2C_RS_BIT);
    }

    PulseEnable(Local_u8Value);
}

static void SendByte(u8 Copy_u8Byte, u8 Copy_u8IsData)
{
    SendNibble((Copy_u8Byte >> 4) & 0x0F, Copy_u8IsData);
    SendNibble(Copy_u8Byte & 0x0F, Copy_u8IsData);
}

/* ============ الدوال العامة ============ */

void LCD_I2C_Init(void)
{
    Timer_voidDelayMs(15);

    SendNibble(0x03, 0);
    Timer_voidDelayMs(5);

    SendNibble(0x03, 0);
    Timer_voidDelayMs(1);

    SendNibble(0x03, 0);
    Timer_voidDelayMs(1);

    SendNibble(0x02, 0);

    SendByte(LCD_I2C_CMD_FUNCTION_SET_4BIT, 0);
    SendByte(LCD_I2C_CMD_DISPLAY_ON, 0);
    SendByte(LCD_I2C_CMD_CLEAR, 0);
    Timer_voidDelayMs(2);
    SendByte(LCD_I2C_CMD_ENTRY_MODE_SET, 0);
}

void LCD_I2C_Clear(void)
{
    SendByte(LCD_I2C_CMD_CLEAR, 0);
    Timer_voidDelayMs(2);
}

void LCD_I2C_SetCursor(u8 Copy_u8Col, u8 Copy_u8Row)
{
    u8 Local_u8Addr = Copy_u8Col + (Copy_u8Row == 0 ? 0x00 : 0x40);
    SendByte(0x80 | Local_u8Addr, 0);
}

void LCD_I2C_WriteChar(u8 Copy_u8Char)
{
    SendByte(Copy_u8Char, 1);
}

void LCD_I2C_WriteString(const char *Copy_pcString)
{
    while (*Copy_pcString)
    {
        LCD_I2C_WriteChar((u8)*Copy_pcString);
        Copy_pcString++;
    }
}
