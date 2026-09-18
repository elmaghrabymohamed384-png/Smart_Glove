/*
 *  file Name : LCD_Program.c
 *  Created on: ??þ/??þ/???? at ?:??:?? Õ
 *  Author    : Ziad_Elmeakwy
 *  Description :
 */

#define F_CPU 8000000UL
#include <util/delay.h>

#include "LCD_Interface.h"
#include "LCD_Config.h"

void LCD_Init			(void)
{
	// 1- must wait more than 30 ms before any action (VDD rises to 4.5 v)
	_delay_ms(50);
	// All Pins as OutPut pins
	DIO_Set_Port_Direction (LCD_DATA_PORT, PORT_OUTPUT);
	DIO_Set_Pin_Direction (LCD_CONTROL_PORT, LCD_RS, PIN_OUTPUT);
	DIO_Set_Pin_Direction (LCD_CONTROL_PORT, LCD_RW, PIN_OUTPUT);
	DIO_Set_Pin_Direction (LCD_CONTROL_PORT, LCD_EN, PIN_OUTPUT);

	/* Return cursor to the first position on the first line  */
	LCD_Send_Command(lcd_Home);
	_delay_ms(1);

	/*FUNCTION SET Command : 2 lines , 5*8 font size */
	LCD_Send_Command(EIGHT_BITS); // 8 Bit Mode ==> 0x38
	_delay_ms(1); // wait more than 39 Ms

	/* DISPLAY & Cursor (ON / OFF) Control */
	LCD_Send_Command( lcd_DisplayOn_CursorOff);
	_delay_ms(1);

	/* DISPLAY CLEAR */
	LCD_Clear_Screen();

	/* ENTRY MODE  SET*/
	LCD_Send_Command( lcd_EntryMode);
	_delay_ms(1);
}

void LCD_Send_Data		(u8 data)
{
	// 1 - Send Data at data pins (D0 -D7)
	DIO_Set_Port_Value(LCD_DATA_PORT , data);
	// 2 - Select Register from RS pin
	DIO_Set_Pin_Value(LCD_CONTROL_PORT , LCD_RS , PIN_HIGH);
	// 3 - Select read or write using R/W pin
	DIO_Set_Pin_Value(LCD_CONTROL_PORT , LCD_RW , PIN_LOW);
	// 4 - Enable to EN pin by Falling edge
	LCD_Send_Falling_Edge();
}

void LCD_Send_Command	(u8 command)
{
	// 1 - Send Data at data pins (D0 -D7)
	    DIO_Set_Port_Value(LCD_DATA_PORT , command);
		// 2 - Select Register from RS pin
	    DIO_Set_Pin_Value(LCD_CONTROL_PORT , LCD_RS , PIN_LOW);
		// 3 - Select read or write using R/W pin
	    DIO_Set_Pin_Value(LCD_CONTROL_PORT , LCD_RW , PIN_LOW);
		// 4 - Enable to EN pin by Falling edge
		LCD_Send_Falling_Edge();
}

void LCD_Send_String	(u8 *string)
{
	u8 LOC_u8Iterator = 0 ;

	while( string[LOC_u8Iterator] != '\0' ){

		LCD_Send_Data( string[LOC_u8Iterator] );
		LOC_u8Iterator++ ;

	}
}

void LCD_Send_Number	(u8 Number)
{
	u64 LOC_u64Reversed = 1 ;

	if( Number == 0 ){ LCD_Send_Data('0'); }

	else{

		while( Number != 0 ){

			LOC_u64Reversed = ( LOC_u64Reversed * 10 ) + ( Number % 10 );
			Number /= 10 ;

		}
		while( LOC_u64Reversed != 1 ){

			LCD_Send_Data( ( LOC_u64Reversed % 10 ) + 48 );
			LOC_u64Reversed /= 10 ;

		}

	}
}

void LCD_Clear_Screen	(void)
{
	LCD_Send_Command(lcd_Clear);
}

void LCD_Send_Falling_Edge		(void )
{
	DIO_Set_Pin_Value(LCD_CONTROL_PORT , LCD_EN , PIN_HIGH);
	_delay_ms(1);
	DIO_Set_Pin_Value(LCD_CONTROL_PORT , LCD_EN , PIN_LOW);
	_delay_ms(1);
}
void LCD_Set_Position ( u8 Copy_u8Row , u8 Copy_u8Col ){

	u8 LOC_u8data ;

	/* In These cases will set at (0,0) ==> if the user enter invalid location */
	if(Copy_u8Row>2||Copy_u8Row<1||Copy_u8Col>16||Copy_u8Col<1)  //check
	{
		LOC_u8data = lcd_SetCursor ;   // first location
	}

	else if( Copy_u8Row == CLCD_ROW_1 ){

		LOC_u8data = ( ( lcd_SetCursor ) + ( Copy_u8Col - 1 ) );              //Row1 -> 0x80+col-1

	}

	else if( Copy_u8Row == CLCD_ROW_2 ){

		LOC_u8data = ( ( lcd_SetCursor ) + (64) + ( Copy_u8Col - 1 ) );       //Row2 -> 0xc0+col-1

	}
	LCD_Send_Command ( LOC_u8data );
	_delay_ms(1);

}

void LCD_Shift_Display(u8 Copy_u8Direction, u8 Copy_u8Steps, u16 Copy_u16Delay_ms)
{
    u8 LOC_u8Command;
    u8 LOC_u8Iterator;

    /* Choose command based on direction */
    if(Copy_u8Direction == LCD_SHIFT_RIGHT)
    {
        LOC_u8Command = lcd_ShiftDisplayRight;
    }
    else
    {
        LOC_u8Command = lcd_ShiftDisplayLeft;
    }

    /* Send command for each step with delay */
    for(LOC_u8Iterator = 0; LOC_u8Iterator < Copy_u8Steps; LOC_u8Iterator++)
    {
        LCD_Send_Command(LOC_u8Command);
        _delay_ms(Copy_u16Delay_ms);
    }
}

void LCD_Shift_String(u8 *Copy_u8String, u8 Copy_u8Row, u8 Copy_u8Direction, u8 Copy_u8Steps, u16 Copy_u16Delay_ms)
{
    u8 LOC_u8Iterator;
    u8 LOC_u8StartCol;

    if(Copy_u8Direction == LCD_SHIFT_LEFT)
    {
        /* Start from rightmost possible position and go left */
        for(LOC_u8Iterator = 0; LOC_u8Iterator < Copy_u8Steps; LOC_u8Iterator++)
        {
            LCD_Clear_Screen();
            LOC_u8StartCol = 16 - LOC_u8Iterator;  // Move left
            LCD_Set_Position(Copy_u8Row, LOC_u8StartCol);
            LCD_Send_String(Copy_u8String);
            _delay_ms(Copy_u16Delay_ms);
        }
    }
    else if(Copy_u8Direction == LCD_SHIFT_RIGHT)
    {
        /* Start from leftmost position and go right */
        for(LOC_u8Iterator = 0; LOC_u8Iterator < Copy_u8Steps; LOC_u8Iterator++)
        {
            LCD_Clear_Screen();
            LOC_u8StartCol = 1 + LOC_u8Iterator;   // Move right
            LCD_Set_Position(Copy_u8Row, LOC_u8StartCol);
            LCD_Send_String(Copy_u8String);
            _delay_ms(Copy_u16Delay_ms);
        }
    }
}
