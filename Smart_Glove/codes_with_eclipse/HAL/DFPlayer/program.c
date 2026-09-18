/*
 * program.c
 * DFPlayer Mini driver — Implementation
 */

#include "interface.h"
#include "../../lib/STD_Types.h"
#include "../../lib/BIT_MATH.h"
#include "../../MCAL/UART/UART_interface.h"
#include "../../MCAL/Timer/Timer_interface.h"

/* ============ أوامر DFPlayer ============ */
#define DFPLAYER_START       0x7E
#define DFPLAYER_VERSION     0xFF
#define DFPLAYER_LENGTH      0x06
#define DFPLAYER_FEEDBACK    0x00
#define DFPLAYER_END         0xEF

#define DFPLAYER_CMD_PLAY    0x03
#define DFPLAYER_CMD_VOLUME  0x06

/* ============================================================
 *                  تهيئة DFPlayer
 * ============================================================
 * مش بننادي UART_Init هنا — main لازم يناديها قبل.
 * بنستنى بس وقت الـ boot (1.5-2 ثانية).
 * ============================================================ */
void DFPlayer_Init(void)
{
    /* انتظر ~2 ثانية لحد ما DFPlayer يـ boot ويقرأ الـ SD card */
    Timer_voidDelayMs(2000);
}

/* ============================================================
 *                  تشغيل ملف صوتي
 * ============================================================ */
void DFPlayer_PlayTrack(u16 Track)
{
    u8  Frame[10];
    u16 Checksum;
    u8  Index;

    /* بناء الفريم */
    Frame[0] = DFPLAYER_START;
    Frame[1] = DFPLAYER_VERSION;
    Frame[2] = DFPLAYER_LENGTH;
    Frame[3] = DFPLAYER_CMD_PLAY;
    Frame[4] = DFPLAYER_FEEDBACK;

    /* رقم الملف (16-bit) */
    Frame[5] = (u8)(Track >> 8);
    Frame[6] = (u8)(Track);

    /* حساب الـ checksum */
    Checksum = 0;
    for (Index = 1; Index <= 6; Index++)
    {
        Checksum += Frame[Index];
    }
    Checksum = 0xFFFF - Checksum + 1;   /* 2's complement */

    Frame[7] = (u8)(Checksum >> 8);
    Frame[8] = (u8)(Checksum);
    Frame[9] = DFPLAYER_END;

    /* إرسال الفريم */
    for (Index = 0; Index < 10; Index++)
    {
        UART_SendData(Frame[Index]);
    }
}

/* ============================================================
 *                  ضبط الصوت
 * ============================================================ */
void DFPlayer_SetVolume(u8 Volume)
{
    u8  Frame[10];
    u16 Checksum;
    u8  Index;

    if (Volume > 30) Volume = 30;

    Frame[0] = DFPLAYER_START;
    Frame[1] = DFPLAYER_VERSION;
    Frame[2] = DFPLAYER_LENGTH;
    Frame[3] = DFPLAYER_CMD_VOLUME;
    Frame[4] = DFPLAYER_FEEDBACK;
    Frame[5] = 0x00;
    Frame[6] = Volume;

    Checksum = 0;
    for (Index = 1; Index <= 6; Index++)
    {
        Checksum += Frame[Index];
    }
    Checksum = 0xFFFF - Checksum + 1;

    Frame[7] = (u8)(Checksum >> 8);
    Frame[8] = (u8)(Checksum);
    Frame[9] = DFPLAYER_END;

    for (Index = 0; Index < 10; Index++)
    {
        UART_SendData(Frame[Index]);
    }
}
