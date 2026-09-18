#include "Timer_interface.h"
#include "Timer_config.h"
#include "Timer_private.h"
#include <avr/io.h>
#include <avr/interrupt.h>

static volatile u32 Timer_u32TickCount = 0;

ISR(TIMER0_COMP_vect)
{
    Timer_u32TickCount++;
}

void Timer_voidInit(void)
{
    TCCR0 = (1 << WGM01);
    TCCR0 |= (1 << CS01) | (1 << CS00);

     OCR0 = TIMER0_OCR_VALUE;

    TIMSK |= (1 << OCIE0);

    sei();
}

u32 Timer_u32GetTick(void)
{
    u32 tick;
    u8  sreg = SREG;
    cli();
    tick = Timer_u32TickCount;
    SREG = sreg;
    return tick;
}

void Timer_voidDelayMs(u16 Copy_u16Ms)
{
    u32 start = Timer_u32GetTick();
    while ((Timer_u32GetTick() - start) < (u32)Copy_u16Ms);
}
