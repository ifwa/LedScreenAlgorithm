/*
*********************************************************************************************************
*                                    (c) Copyright 2016, Ive Wang
*                                        All Rights Reserved
*
*
* File  : EffectLaser.c
* By    : Ive Wang
* Date  : 2016-04-26
*********************************************************************************************************
*/

#define __EFFECT_LASER_C

/*
********************************************************************************************************* 
*                                           INCLUDE HEADER FILES
********************************************************************************************************* 
*/

#include "../App/Includes.h"

/*
*********************************************************************************************************
*                                          Effect_LaserDisappear
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

void Effect_LaserDisappear(void *arg)
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

    for (i = 0; i < disCnt + 1; i++) {
        fmBuf->buf[i] = scBuf->buf[disCnt + 1];
    }
    for (i = disCnt + 1; i < 48; i++) {
        fmBuf->buf[i] = scBuf->buf[i];
    }
}

/*
*********************************************************************************************************
*                                          Effect_LaserAppear
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

void Effect_LaserAppear(void *arg)
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

    for (i = 0; i < appCnt + 1; i++) {
        fmBuf->buf[i] = scBuf->buf[i];
    }
    for (i = appCnt + 1; i < 48; i++) {
        fmBuf->buf[i] = scBuf->buf[appCnt];
    }
}

/*
*********************************************************************************************************
*                                       End of file EffectLaser.c
*********************************************************************************************************
*/
