/******************************************************************************
 * LedAct.c
 *
 * Copyright (C) 2017  WANG YIFU
 *
 * Auther: Wang Yifu
 * E-mail: 340064514@qq.com
 *
 * Note:
 *
 ******************************************************************************/

#define __LED_ACT_C

#include "../App/Includes.h"


void LED_ActTwinkHandle(LED_ACT *act, LED_SCREEN_BUF *fmBuf)
{
    UINT8 i;

    if (act->twinkTms == 0) {
        return;
    }

    if (act->twinkCnt >= act->twinkTms / 2) {
        for (i = 0; i < 48; i++) {
            fmBuf->buf[i] = 0;
        }
    } 

    act->twinkCnt++;
    if (act->twinkCnt >= act->twinkTms) {
        act->twinkCnt = 0;
    }
}

void LED_ActHorseHandle(LED_ACT *act, LED_SCREEN_BUF *fmBuf)
{
    UINT8 i;

    if (act->horseTms == 0) {
        return;
    }

    if (act->horseCnt < act->horseTms / 4) {
        for (i = 0; i < 48; i++) {
            // The far left column
            if (i == 0) {
                fmBuf->buf[i] = 0x0111;
            }
            // The far right column
            if (i == 47) {
                fmBuf->buf[i] = 0x0222;
            }
            // The top row
            if (i % 4 == 0) {
                fmBuf->buf[i] |= 0x0001;
            } else {
                fmBuf->buf[i] &= ~0x0001;
            }
            // The bottom row
            if (i % 4 == 1) {
                fmBuf->buf[i] |= 0x0800;
            } else {
                fmBuf->buf[i] &= ~0x0800;
            }
        }
    } else if (act->horseCnt < act->horseTms / 2) {
        for (i = 0; i < 48; i++) {
            // The far left column
            if (i == 0) {
                fmBuf->buf[i] = 0x0222;
            }
            // The far right column
            if (i == 47) {
                fmBuf->buf[i] = 0x0111;
            }
            // The top row
            if (i % 4 == 3) {
                fmBuf->buf[i] |= 0x0001;
            } else {
                fmBuf->buf[i] &= ~0x0001;
            }
            // The bottom row
            if (i % 4 == 2) {
                fmBuf->buf[i] |= 0x0800;
            } else {
                fmBuf->buf[i] &= ~0x0800;
            }
        }
    } else if (act->horseCnt < act->horseTms / 4 * 3) {
        for (i = 0; i < 48; i++) {
            // The far left column
            if (i == 0) {
                fmBuf->buf[i] = 0x0444;
            }
            // The far right column
            if (i == 47) {
                fmBuf->buf[i] = 0x0888;
            }
            // The top row
            if (i % 4 == 2) {
                fmBuf->buf[i] |= 0x0001;
            } else {
                fmBuf->buf[i] &= ~0x0001;
            }
            // The bottom row
            if (i % 4 == 3) {
                fmBuf->buf[i] |= 0x0800;
            } else {
                fmBuf->buf[i] &= ~0x0800;
            }
        }
    } else {
        for (i = 0; i < 48; i++) {
            // The far left column
            if (i == 0) {
                fmBuf->buf[i] = 0x0888;
            }
            // The far right column
            if (i == 47) {
                fmBuf->buf[i] = 0x0444;
            }
            // The top row
            if (i % 4 == 1) {
                fmBuf->buf[i] |= 0x0001;
            } else {
                fmBuf->buf[i] &= ~0x0001;
            }
            // The bottom row
            if (i % 4 == 0) {
                fmBuf->buf[i] |= 0x0800;
            } else {
                fmBuf->buf[i] &= ~0x0800;
            }
        }
    }

    act->horseCnt++;
    if (act->horseCnt >= act->horseTms) {
        act->horseCnt = 0;
    }
}

void LED_ActSwitch(void *arg)
{
    LED_DISPLAY *ledDisp;
    
    ledDisp = (LED_DISPLAY *)arg;

    do {
        ledDisp->actCnt++;
        if (ledDisp->actCnt > CONFIG_LED_SCREEN_ACTS - 1) {
            ledDisp->actCnt = 0;
        }
    } while (ledDisp->act[ledDisp->actCnt].enable == 0);
}

void LED_ActSet()
{
}

void LED_ActHandle(void *arg)
{
    LED_DISPLAY *ledDisp;
    LED_ACT *act;
    UINT8 i;
    
    ledDisp = (LED_DISPLAY *)arg;
    act = &(ledDisp->act[ledDisp->actCnt]);

    if (act->speedSuper > 0) {
        for (i = 0; i < act->speedSuper; i++) {
            LED_EffectHandle((void *)ledDisp);
        }
    } else {
        act->speedCnt++;
        if (act->speedCnt > act->speedMax) {
            act->speedCnt = 0;
            LED_EffectHandle((void *)ledDisp);
        } else {
            for (i = 0; i < LED_SCREEN_MAX_WORDS; i++) {
                ledDisp->nxtFrameBuf->buf[i] = ledDisp->curFrameBuf->buf[i];
            }
        }
    }

    LED_ActTwinkHandle(act, ledDisp->nxtFrameBuf);
    
    LED_ActHorseHandle(act, ledDisp->nxtFrameBuf);
}
