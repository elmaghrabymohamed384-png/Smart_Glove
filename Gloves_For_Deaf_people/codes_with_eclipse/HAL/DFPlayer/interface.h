/*
 * interface.h
 * DFPlayer Mini driver — Header
 */

#ifndef DFPLAYER_INTERFACE_H_
#define DFPLAYER_INTERFACE_H_

#include "../../lib/STD_Types.h"

/* تهيئة DFPlayer (وقت انتظار للـ boot) */
void DFPlayer_Init(void);

/* تشغيل ملف صوتي (1 إلى 3000) */
void DFPlayer_PlayTrack(u16 Track);

/* ضبط الصوت (0 إلى 30) */
void DFPlayer_SetVolume(u8 Volume);

#endif /* DFPLAYER_INTERFACE_H_ */
