
#include <util/delay.h>

#include "LIB/BIT_MATH.h"
#include "LIB/STD_Types.h"
#include "MCAL/Timer/Timer_interface.h"
#include "MCAL/I2C/I2C_interface.h"
#include "HAL/HALL/hall_interface.h"
#include "HAL/MPU6050/MPU6050_interface.h"
#include "HAL/LCD_I2C/LCD_I2C_interface.h"
#include "HAL/VOICE/voice_interface.h"
#include "MCAL/GESTURES/ges_interface.h"




static void DisplayGesture(u8 GestureNumber)
{
    LCD_I2C_Clear();

    switch(GestureNumber)
    {
        case 1:
            /* Hi */
            LCD_I2C_SetCursor(0, 0);
            LCD_I2C_WriteString("Hi :)");
            VOICE_Say(1);
            break;

        case 2:
            /* I use this system to speak */
            LCD_I2C_SetCursor(0, 0);
            LCD_I2C_WriteString("I use this");
            LCD_I2C_SetCursor(0, 1);
            LCD_I2C_WriteString("system to speak");
            VOICE_Say(2);
            break;

        case 3:
            /* Let's try it */
            LCD_I2C_SetCursor(0, 0);
            LCD_I2C_WriteString("Let's try it");
            VOICE_Say(3);
            break;

        case 4:
            /* I want water */
            LCD_I2C_SetCursor(0, 0);
            LCD_I2C_WriteString("I want water");
            VOICE_Say(4);
            break;

        case 5:
            /* I am hungry */
            LCD_I2C_SetCursor(0, 0);
            LCD_I2C_WriteString("I am hungry");
            VOICE_Say(5);
            break;

        case 6:
            /* I need help */
            LCD_I2C_SetCursor(0, 0);
            LCD_I2C_WriteString("I need help");
            VOICE_Say(6);
            break;

        case 7:
            /* I need a doctor */
            LCD_I2C_SetCursor(0, 0);
            LCD_I2C_WriteString("I need a doctor");
            VOICE_Say(7);
            break;

        case 8:
            /* I am happy today */
            LCD_I2C_SetCursor(0, 0);
            LCD_I2C_WriteString("I am happy today");
            VOICE_Say(8);
            break;

        case 9:
            /* Nice to meet you */
            LCD_I2C_SetCursor(0, 0);
            LCD_I2C_WriteString("Nice to meet you");
            VOICE_Say(9);
            break;

        case 10:
            /* Thanks for your time */
            LCD_I2C_SetCursor(0, 0);
            LCD_I2C_WriteString("Thanks for your");
            LCD_I2C_SetCursor(0, 1);
            LCD_I2C_WriteString("time :)");
            VOICE_Say(10);
            break;

        default:
            break;
    }
}


/* =========================================================
 * Main
 * ========================================================= */

int main(void)
{
    /* -----------------------------------------------------
     * Variables
     * ----------------------------------------------------- */

    u8 HallValues[5];

    u8 TouchValue;
    u8 Direction;

    u8 CurrentGesture;
    u8 LastGesture    = 0;
    u8 StableCounter  = 0;     

    s16 AccX;
    s16 AccY;
    s16 AccZ;

    Timer_voidInit();
    I2C_MasterInit();
    HALL_Init();
    TOUCH_Init();
    MPU6050_voidInit();
    LCD_I2C_Init();
    VOICE_Init();

    LCD_I2C_Clear();

    LCD_I2C_SetCursor(0, 0);
    LCD_I2C_WriteString("Gesture System");

    LCD_I2C_SetCursor(0, 1);
    LCD_I2C_WriteString("Ready...");

    _delay_ms(1000);

    LCD_I2C_Clear();




    while(1)
    {
        HALL_Read(HallValues);
        TouchValue = TOUCH_Read();

        MPU6050_voidReadAccel(&AccX, &AccY, &AccZ);

        Direction = Gest_accDir(AccX, AccY, AccZ);

        CurrentGesture = Gest_Detect(
                            HallValues,
                            Direction,
                            TouchValue
                         );

        if (CurrentGesture != 0)
        {
            if (CurrentGesture == LastGesture)
            {

                if (StableCounter < STABLE_THRESHOLD)
                {
                    StableCounter++;
                }
            }
            else
            {
               
                LastGesture   = CurrentGesture;
                StableCounter = 1;
            }

          
            if (StableCounter == STABLE_THRESHOLD)
            {
                DisplayGesture(CurrentGesture);

                StableCounter = STABLE_THRESHOLD + 1; 
            }
        }
        else
        {
            /* مفيش إيماءة — صفّر كل حاجة */
            LastGesture   = 0;
            StableCounter = 0;
        }


        /* -------------------------------------------------
         * 7. Small delay for sensor stability
         * ------------------------------------------------- */

        _delay_ms(50);
    }

    return 0;   /* Never reached — kept for the compiler */
}
