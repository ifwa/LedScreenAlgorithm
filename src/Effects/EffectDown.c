/*
*********************************************************************************************************
*                                    (c) Copyright 2016, Ive Wang
*                                        All Rights Reserved
*
*
* File  : EffectDown.c
* By    : Ive Wang
* Date  : 2016-05-07
*********************************************************************************************************
*/

#define __EFFECT_DOWN_C

/*
*********************************************************************************************************
*                                           INCLUDE HEADER FILES
*********************************************************************************************************
*/

#include "../App/Includes.h"

/*
*********************************************************************************************************
*                                          Effect_DownDisappear
*
* Description :
*
* Arguments   :
*
* Returns     :
*
* Note(s)     :
*
*********************************************************************************************************
*/

void Effect_DownDisappear(void *arg)
{
    LED_DISPLAY *ledDisp;
    LED_SCREEN_BUF *fmBuf;
    LED_SCREEN_BUF *scBuf;
    UINT32 disCnt;
    UINT8 i;

    ledDisp = (LED_DISPLAY *)arg;
    fmBuf = ledDisp->nxtFrameBuf;
    scBuf = ledDisp->curScreenBuf;
    disCnt = ledDisp->act[ledDisp->actCnt].effect.disappearCnt;

    for (i = 0; i < 48; i++) {
        fmBuf->buf[i] = scBuf->buf[i] << (1 + disCnt);
    }
}

/*
*********************************************************************************************************
*                                          Effect_DownAppear
*
* Description :
*
* Arguments   :
*
* Returns     :
*
* Note(s)     :
*
*********************************************************************************************************
*/

void Effect_DownAppear(void *arg)
{
    LED_DISPLAY *ledDisp;
    LED_SCREEN_BUF *fmBuf;
    LED_SCREEN_BUF *scBuf;
    UINT32 appCnt;
    UINT8 i;
    
    ledDisp = (LED_DISPLAY *)arg;
    fmBuf = ledDisp->nxtFrameBuf;
    scBuf = ledDisp->curScreenBuf;
    appCnt = ledDisp->act[ledDisp->actCnt].effect.appearCnt;

    for (i = 0; i < 48; i++) {
        fmBuf->buf[i] = scBuf->buf[i] >> (11 - appCnt);
    }
}

/*
*********************************************************************************************************
*                                       End of file EffectDown.c
*********************************************************************************************************
*/

