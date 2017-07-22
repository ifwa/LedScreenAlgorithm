/*
*********************************************************************************************************
*                                    (c) Copyright 2016, Ive Wang
*                                        All Rights Reserved
*
*
* File  : EffectLeft.c
* By    : Ive Wang
* Date  : 2016-05-07
*********************************************************************************************************
*/

#define __EFFECT_LEFT_C

/*
********************************************************************************************************* 
*                                           INCLUDE HEADER FILES
********************************************************************************************************* 
*/

#include "../App/Includes.h"

/*
*********************************************************************************************************
*                                          Effect_LeftRoll
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

void Effect_LeftRoll(void *arg)
{
    LED_DISPLAY *ledDisp;
    LED_SCREEN_BUF *fmBuf;
    LED_SCREEN_BUF *curScBuf;
    LED_SCREEN_BUF *nxtScBuf;
    UINT32 appCnt;
    UINT8 i;
    
    ledDisp = (LED_DISPLAY *)arg;
    fmBuf = ledDisp->nxtFrameBuf;
    curScBuf = ledDisp->curScreenBuf;
    nxtScBuf = ledDisp->nxtScreenBuf;
    appCnt = ledDisp->act[ledDisp->actCnt].effect.appearCnt;

    for (i = 0; i < 48; i++) {
        if (i < 47 - appCnt) {
            fmBuf->buf[i] = curScBuf->buf[i + 1 + appCnt];
        } else {
            fmBuf->buf[i] = nxtScBuf->buf[i - (47 - appCnt)];
        }
    }
}

/*
*********************************************************************************************************
*                                          Effect_LeftAppear
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

void Effect_LeftAppear(void *arg)
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
        if (i < 47 - appCnt) {
            fmBuf->buf[i] = 0;
        } else {
            fmBuf->buf[i] = scBuf->buf[i - (47 - appCnt)];
        }
    }
}

/*
*********************************************************************************************************
*                                       End of file EffectLeft.c
*********************************************************************************************************
*/
