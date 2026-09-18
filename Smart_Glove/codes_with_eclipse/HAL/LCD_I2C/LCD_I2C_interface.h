/*
 * LCD_I2C_interface.h
 *
 *  Created on: Sep 13, 2026
 *      Author: m7dm
 */

#ifndef LCD_I2C_INTERFACE_H
#define LCD_I2C_INTERFACE_H

#include "../../lib/STD_Types.h"

void LCD_I2C_Init(void);
void LCD_I2C_Clear(void);
void LCD_I2C_SetCursor(u8 Copy_u8Col, u8 Copy_u8Row);
void LCD_I2C_WriteChar(u8 Copy_u8Char);
void LCD_I2C_WriteString(const char *Copy_pcString);

#endif /* LCD_I2C_INTERFACE_H */
