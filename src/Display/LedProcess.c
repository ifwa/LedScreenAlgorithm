/******************************************************************************
 * LedProcess.c
 *
 * Copyright (C) 2017  WANG YIFU
 *
 * Auther: Wang Yifu
 * E-mail: 340064514@qq.com
 *
 * Note:
 *
 ******************************************************************************/

#define __LED_PROCESS_C

#include "../App/Includes.h"


const LED_SCREEN_BUF FullScrBuf = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
                                   0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
                                   0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
                                   0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

const LED_SCREEN_BUF EmptyScrBuf = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// These are just for tests.

// "暴走漫画" (Rage Comic)
UINT8 bzmh[96] = {
    0x40,0x02,0x50,0x09,0xDF,0x04,0x55,0x05,
    0x75,0x0A,0xD5,0x0F,0x55,0x02,0x75,0x05,
    0xD5,0x04,0x5F,0x09,0x50,0x02,0x40,0x02,

    0x10,0x08,0x14,0x04,0xD4,0x03,0x14,0x02,
    0x14,0x04,0xFF,0x07,0x94,0x08,0x94,0x08,
    0x94,0x08,0xD6,0x08,0x94,0x08,0x10,0x08,

    0x84,0x00,0x89,0x0F,0x72,0x00,0x00,0x08,
    0x70,0x09,0x5F,0x0B,0x75,0x05,0x55,0x05,
    0x75,0x0D,0x5F,0x0B,0x70,0x09,0x00,0x08,

    0x02,0x00,0xF2,0x0F,0x02,0x04,0xFA,0x05,
    0x2A,0x05,0xFA,0x05,0x2A,0x05,0x2A,0x05,
    0xFA,0x05,0x02,0x04,0xF3,0x0F,0x02,0x00
};

// "美国队长" (Captain America)
UINT8 mgdz[96] = {
    0x20, 0x08, 0xA2, 0x08, 0xAA, 0x04, 0xAB, 0x04,
    0xAA, 0x02, 0xFE, 0x01, 0xAA, 0x01, 0xAB, 0x02,
    0xAA, 0x02, 0xAA, 0x04, 0xA2, 0x08, 0x20, 0x08,

    0x00, 0x00, 0xFE, 0x0F, 0x02, 0x05, 0x2A, 0x05,
    0x2A, 0x05, 0xFA, 0x05, 0x2A, 0x05, 0x6A, 0x05,
    0xAA, 0x05, 0x02, 0x05, 0xFF, 0x0F, 0x02, 0x00,

    0x00, 0x00, 0xFE, 0x0F, 0x92, 0x00, 0x2A, 0x09,
    0xC6, 0x04, 0x00, 0x03, 0xC0, 0x00, 0x3F, 0x00,
    0xC0, 0x00, 0x00, 0x03, 0x00, 0x04, 0x00, 0x08,

    0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0xFF, 0x0F,
    0x30, 0x04, 0x68, 0x04, 0xA8, 0x00, 0x24, 0x01,
    0x22, 0x02, 0x21, 0x04, 0x30, 0x04, 0x20, 0x04
};

// "动物森林" (Animal forest)
UINT8 dwsl[96] = {
    0x10, 0x01, 0x92, 0x03, 0x52, 0x01, 0x32, 0x09,
    0x92, 0x09, 0x10, 0x05, 0x08, 0x02, 0x88, 0x01,
    0x7F, 0x00, 0x08, 0x04, 0x08, 0x08, 0xF8, 0x07,

    0xBC, 0x00, 0x88, 0x00, 0xFF, 0x0F, 0x48, 0x00,
    0x50, 0x05, 0x88, 0x04, 0x47, 0x02, 0x3C, 0x05,
    0xC4, 0x08, 0x3C, 0x08, 0x84, 0x07, 0x7C, 0x00,

    0x42, 0x04, 0x52, 0x02, 0x52, 0x01, 0xEA, 0x0F,
    0x4A, 0x01, 0x46, 0x04, 0x5F, 0x02, 0x46, 0x01,
    0xEA, 0x0F, 0x4A, 0x01, 0x52, 0x02, 0x42, 0x04,

    0x08, 0x01, 0xC8, 0x00, 0x28, 0x00, 0xFF, 0x0F,
    0x48, 0x00, 0x08, 0x01, 0xC8, 0x00, 0x28, 0x00,
    0xFF, 0x0F, 0x48, 0x00, 0x8C, 0x00, 0x08, 0x01
};

void LED_DisplayCurScrUpd(LED_DISPLAY *ledDisp)
{
    UINT8 i;
    if (ledDisp->act[ledDisp->actCnt].effect.screenCnt == 0) {
		for (i = 0; i < 48; i++) {
			ledDisp->curScreenBuf->buf[i] = (UINT16)bzmh[i * 2 + 1] * 256 + bzmh[i * 2];
		}
    }
    else if (ledDisp->act[ledDisp->actCnt].effect.screenCnt == 1) {
		for (i = 0; i < 48; i++) {
			ledDisp->curScreenBuf->buf[i] = (UINT16)mgdz[i * 2 + 1] * 256 + mgdz[i * 2];
		}
    }
    else {
		for (i = 0; i < 48; i++) {
			ledDisp->curScreenBuf->buf[i] = (UINT16)dwsl[i * 2 + 1] * 256 + dwsl[i * 2];
		}
    }
//    UINT8 *buf;
//    UINT16 capBytes;
//    UINT16 startByte;
//    UINT8 i,j,k;
//    UINT16 temp;
//    // buf = ;
//
//    if (ledDisp->actCnt == 0) {
//        startByte = 48;
//    } else {
//        startByte = 48 + buf[11 + (ledDisp->actCnt - 1) * 4] + buf[12 + (ledDisp->actCnt - 1) * 4] * 256;
//    }
//    capBytes = buf[13 + ledDisp->actCnt * 4] + buf[14 + ledDisp->actCnt * 4];
//
//    for (i = 0; i < 6; i++) {
//        if (ledDisp->actCnt * 6 + i < capBytes) {
//            for (j = 0; j < 8; j++) {
//                temp = 0;
//                for (k = 0; k < 12; k++) {
//                    temp |= ((buf[startByte + (ledDisp->actCnt * 6 + i) * 12 + k] >> (7 - j)) % 2) << k;
//                }
//                ledDisp->curScreenBuf->buf[i * 8 + j] = temp;
//            }
//        } else {
//            for (j = 0; j < 8; j++) {
//                ledDisp->curScreenBuf->buf[i * 8 + j] = 0;
//            }
//        }
//    }
}

void LED_DisplayNxtScrUpd(LED_DISPLAY *ledDisp)
{
    UINT8 i;
    if (ledDisp->act[ledDisp->actCnt].effect.screenCnt == 0) {
		for (i = 0; i < 48; i++) {
			ledDisp->nxtScreenBuf->buf[i] = (UINT16)mgdz[i * 2 + 1] * 256 + mgdz[i * 2];
		}
    }
    else if (ledDisp->act[ledDisp->actCnt].effect.screenCnt == 1) {
		for (i = 0; i < 48; i++) {
			ledDisp->nxtScreenBuf->buf[i] = (UINT16)dwsl[i * 2 + 1] * 256 + dwsl[i * 2];
		}
    }
    else {
		for (i = 0; i < 48; i++) {
			ledDisp->nxtScreenBuf->buf[i] = 0;
		}
    }
}

void LED_DisplayLstScrUpd(LED_DISPLAY *ledDisp)
{
    UINT8 i;
    if (ledDisp->act[ledDisp->actCnt].effect.screenCnt == 0) {
		for (i = 0; i < 48; i++) {
			ledDisp->lstScreenBuf->buf[i] = 0;
		}
    }
    else if (ledDisp->act[ledDisp->actCnt].effect.screenCnt == 1) {
		for (i = 0; i < 48; i++) {
			ledDisp->lstScreenBuf->buf[i] = (UINT16)bzmh[i * 2 + 1] * 256 + bzmh[i * 2];
		}
    }
    else {
		for (i = 0; i < 48; i++) {
			ledDisp->lstScreenBuf->buf[i] = (UINT16)mgdz[i * 2 + 1] * 256 + mgdz[i * 2];
		}
    }
}

void LED_DisplayColRefresh(LED_SCREEN_BUF *buf, UINT8 col)
{
    int i, j;

    for (i = col * 2; i < (col + 1) * 2 + 1; i++) {
        for (j = 0; j < 12; j++) {
//            if ((LedDisplay.curFrameBuf->buf[i] >> j) % 2 != 0) {
            if ((buf->buf[i] >> j) % 2 != 0) {
                Sim_DrawDot(i, j);
            } else {
                Sim_ClearDot(i, j);
            }
        }
    }
    Sim_LedScreenRefresh();
}

void LED_DisplayColClear(LED_SCREEN_BUF *buf, UINT8 col)
{
    int i, j;

    for (i = col * 2; i < (col + 1) * 2; i++) {
        for (j = 0; j < 12; j++) {
            Sim_ClearDot(i, j);
        }
    }
    Sim_LedScreenRefresh();
}

void LED_DisplayColFull(LED_SCREEN_BUF * buf, UINT8 col)
{
    int i, j;

    for (i = col * 2; i < (col + 1) * 2 + 1; i++) {
        for (j = 0; j < 12; j++) {
            Sim_DrawDot(i, j);
        }
    }
    Sim_LedScreenRefresh();
}

void LED_DisplayInit(void)
{
    LedDisplay.curFrameBuf  = &LedFrameBuf1;
    LedDisplay.nxtFrameBuf  = &LedFrameBuf2;
    LedDisplay.curScreenBuf = &LedScreenBuf1;
    LedDisplay.nxtScreenBuf = &LedScreenBuf2;
    LedDisplay.lstScreenBuf = &LedScreenBuf2;

    LedDisplay.actCnt = 0;
    LedDisplay.act[0].effect.stat = LED_EFFECT_STAT_NONE;
    LedDisplay.act[1].effect.stat = LED_EFFECT_STAT_NONE;
    LedDisplay.act[2].effect.stat = LED_EFFECT_STAT_NONE;
    LedDisplay.act[3].effect.stat = LED_EFFECT_STAT_NONE;
    LedDisplay.act[4].effect.stat = LED_EFFECT_STAT_NONE;
    LedDisplay.act[5].effect.stat = LED_EFFECT_STAT_NONE;
    LedDisplay.act[6].effect.stat = LED_EFFECT_STAT_NONE;
    LedDisplay.act[7].effect.stat = LED_EFFECT_STAT_NONE;

    LedDisplay.act[0].enable = 0;
    LedDisplay.act[1].enable = 0;
    LedDisplay.act[2].enable = 0;
    LedDisplay.act[3].enable = 0;
    LedDisplay.act[4].enable = 0;
    LedDisplay.act[5].enable = 0;
    LedDisplay.act[6].enable = 0;
    LedDisplay.act[7].enable = 0;

    //
    LedDisplay.act[0].enable = 1;
    LedDisplay.act[1].enable = 1;
    LedDisplay.act[2].enable = 1;
    LedDisplay.act[3].enable = 1;
    LedDisplay.act[4].enable = 1;
    LedDisplay.act[5].enable = 1;
    LedDisplay.act[6].enable = 1;
    LedDisplay.act[7].enable = 1;

    LED_EffectSet(&(LedDisplay.act[0].effect), LED_EFFECT_LASER, 2);
    LedDisplay.act[0].speedMax = 0;
    LedDisplay.act[0].speedSuper = 0;
    LedDisplay.act[0].twinkTms = 0;
    LedDisplay.act[0].horseTms = 0;
    //LedDisplay.act[0].horseTms = 25;

    LED_EffectSet(&(LedDisplay.act[1].effect), LED_EFFECT_SNOW, 2);
    LedDisplay.act[1].speedMax = 0;
    LedDisplay.act[1].speedSuper = 0;
    LedDisplay.act[1].twinkTms = 0;
    LedDisplay.act[1].horseTms = 0;

    LED_EffectSet(&(LedDisplay.act[2].effect), LED_EFFECT_LEFT, 2);
    LedDisplay.act[2].speedMax = 0;
    LedDisplay.act[2].speedSuper = 0;
    LedDisplay.act[2].twinkTms = 0;
    LedDisplay.act[2].horseTms = 0;

    LED_EffectSet(&(LedDisplay.act[3].effect), LED_EFFECT_RIGHT, 2);
    LedDisplay.act[3].speedMax = 0;
    LedDisplay.act[3].speedSuper = 0;
    LedDisplay.act[3].twinkTms = 0;
    LedDisplay.act[3].horseTms = 0;

    LED_EffectSet(&(LedDisplay.act[4].effect), LED_EFFECT_UP, 2);
    LedDisplay.act[4].speedMax = 0;
    LedDisplay.act[4].speedSuper = 0;
    LedDisplay.act[4].twinkTms = 0;
    LedDisplay.act[4].horseTms = 0;

    LED_EffectSet(&(LedDisplay.act[5].effect), LED_EFFECT_DOWN, 2);
    LedDisplay.act[5].speedMax = 0;
    LedDisplay.act[5].speedSuper = 0;
    LedDisplay.act[5].twinkTms = 0;
    LedDisplay.act[5].horseTms = 0;

    LED_EffectSet(&(LedDisplay.act[6].effect), LED_EFFECT_SCROLL, 2);
    LedDisplay.act[6].speedMax = 0;
    LedDisplay.act[6].speedSuper = 0;
    LedDisplay.act[6].twinkTms = 0;
    LedDisplay.act[6].horseTms = 0;

    LED_EffectSet(&(LedDisplay.act[7].effect), LED_EFFECT_LEFT, 2);
    LedDisplay.act[7].speedMax = 0;
    LedDisplay.act[7].speedSuper = 0;
    LedDisplay.act[7].twinkTms = 0;
    LedDisplay.act[7].horseTms = 25;

    LedDisplay.mode = LED_DISPLAY_MODE_NOR;
    LedDisplay.brightness = 3;
}

void LED_Process(void)
{
    if (LedDisplay.refresh == 0) {
        return;
    }
    LedDisplay.refresh = 0;

    switch (LedDisplay.mode) {
        case LED_DISPLAY_MODE_NOR:
            LED_ActHandle((void *)&LedDisplay);
            break;
        case LED_DISPLAY_MODE_BAT:
            // Do something to handle the battery mode, e.g. LED_BatteryHandle(&LedDisplay);
            // But it has nothing to do with this algorithm.
            break;
        case LED_DISPLAY_MODE_OFF:
        default:
            // Do something to clear the screen.
            // But it has nothing to do with this algorithm either.
            break;
    }
}

void LED_TimerIsrHdl(void)
{
    // 写在定时器ISR中，417us调用一次本函数
    // This function should be called every 417 us in the timer ISR.

    LED_SCREEN_BUF *tmpBuf;

    if (LedDisplay.brightCnt <= LedDisplay.brightness && LedDisplay.mode != LED_DISPLAY_MODE_OFF) {
        LED_DisplayColRefresh(LedDisplay.curFrameBuf, LedDisplay.colCnt);

    } else {
        LED_DisplayColClear(LedDisplay.curFrameBuf, LedDisplay.colCnt);

    }

    if (LedDisplay.mode == LED_DISPLAY_MODE_OFF) {
        return;
    }
        
    if (LedDisplay.brightCnt == 0 && LedDisplay.colCnt == 0) {
        LedDisplay.refresh = 1;
    }

    LedDisplay.colCnt++;
    if (LedDisplay.colCnt > LED_SCREEN_MAX_COL) {
        LedDisplay.colCnt = 0;
        LedDisplay.brightCnt++;
        if (LedDisplay.brightCnt > LED_DISPLAY_BRIGHT_LEVEL_MAX) {
            LedDisplay.brightCnt = 0;
            tmpBuf = LedDisplay.curFrameBuf;
            LedDisplay.curFrameBuf = LedDisplay.nxtFrameBuf;
            LedDisplay.nxtFrameBuf = tmpBuf;
        }
    }
}
