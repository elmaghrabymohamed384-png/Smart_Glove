/*
 * tch_program.c
 *
 *  Created on: Sep 14, 2026
 *      Author: jana
 */

#include "tch_interface.h"
#include "../../lib/STD_Types.h"
#include "../../MCAL/DIO/interface.h"

void TOUCH_Init(void){
   DIO_Set_Pin_Direction(PORTB,PIN0,PIN_INPUT);
   DIO_Set_Pin_Direction(PORTB,PIN1,PIN_INPUT);
   DIO_Set_Pin_Direction(PORTB,PIN2,PIN_INPUT);
   DIO_Set_Pin_Direction(PORTB,PIN3,PIN_INPUT);

   //Internal PULL UP
   DIO_Set_Pin_Value(PORTB,PIN0,PIN_HIGH);
   DIO_Set_Pin_Value(PORTB,PIN1,PIN_HIGH);
   DIO_Set_Pin_Value(PORTB,PIN2,PIN_HIGH);
   DIO_Set_Pin_Value(PORTB,PIN3,PIN_HIGH);

}


 /* u8 TOUCH_Read(u8 touch_pin){
	u8 reading=0;

	if (touch_pin != T_NONE){

	 switch(touch_pin){
	 case T1: reading = !DIO_GET_Pin_Value(PORTB,PIN0);break;
	 case T2: reading = !DIO_GET_Pin_Value(PORTB,PIN1);break;
	 case T3: reading = !DIO_GET_Pin_Value(PORTB,PIN2);break;
	 case T4: reading = !DIO_GET_Pin_Value(PORTB,PIN3);break;

	 }
	 return reading;
	}
	else {
		if(!DIO_GET_Pin_Value(PORTB,PIN0)){
			return T1;
		}
		else if(!DIO_GET_Pin_Value(PORTB,PIN1)){
			return T2;
		}
		else if(!DIO_GET_Pin_Value(PORTB,PIN2)){
			return T3;
		}
		else if(!DIO_GET_Pin_Value(PORTB,PIN3)){
			return T4;
		}
		else {
			return T_NONE;
		}

	}
}
*/


 /*********/
u8 TOUCH_Read(void)
{
    u8 result = T_NONE;


    if (DIO_GET_Pin_Value(PORTB, PIN0) == PIN_LOW)
        result |= T1;   /* Index  */

    if (DIO_GET_Pin_Value(PORTB, PIN1) == PIN_LOW)
        result |= T2;   /* Middle */

    if (DIO_GET_Pin_Value(PORTB, PIN2) == PIN_LOW)
        result |= T4;   /* Ring   */

    if (DIO_GET_Pin_Value(PORTB, PIN3) == PIN_LOW)
        result |= T8;   /* Pinky  */

    return result;
}

