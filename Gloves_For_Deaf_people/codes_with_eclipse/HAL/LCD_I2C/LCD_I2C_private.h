/*
 * LCD_I2C_private.h
 *
 *  Created on: Sep 13, 2026
 *      Author: m7dm
 */

#ifndef LCD_I2C_PRIVATE_H
#define LCD_I2C_PRIVATE_H

/* خريطة بتات PCF8574 */
#define LCD_I2C_RS_BIT         0
#define LCD_I2C_RW_BIT         1
#define LCD_I2C_EN_BIT         2
#define LCD_I2C_BL_BIT         3

#define LCD_I2C_BACKLIGHT_ON   (1 << LCD_I2C_BL_BIT)

/* أوامر HD44780 */
#define LCD_I2C_CMD_CLEAR             0x01
#define LCD_I2C_CMD_ENTRY_MODE_SET    0x06
#define LCD_I2C_CMD_DISPLAY_ON        0x0C
#define LCD_I2C_CMD_FUNCTION_SET_4BIT 0x28

#endif /* LCD_I2C_PRIVATE_H */
