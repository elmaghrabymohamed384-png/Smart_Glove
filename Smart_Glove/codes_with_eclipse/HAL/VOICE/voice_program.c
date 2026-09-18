#include "voice_interface.h"
#include "../../MCAL/UART/UART_interface.h"

static void SendString(const char *Copy_pcString)
{
    while (*Copy_pcString)
    {
        UART_SendData((u8)*Copy_pcString);
        Copy_pcString++;
    }
    UART_SendData((u8)'\n');
}

void VOICE_Init(void)
{
    UART_Init();
}

void VOICE_Say(u8 Copy_u8PatternID)
{
    switch (Copy_u8PatternID)
    {
        case 1:  SendString("Hi"); break;
        case 2:  SendString("I use this system to speak"); break;
        case 3:  SendString("Lets try it"); break;
        case 4:  SendString("I want water"); break;
        case 5:  SendString("I am hungry"); break;
        case 6:  SendString("I need help"); break;
        case 7:  SendString("I need a doctor"); break;
        case 8:  SendString("I am happy today"); break;
        case 9:  SendString("Nice to meet you"); break;
        case 10: SendString("Thanks for your time"); break;
        default: break;
    }
}
