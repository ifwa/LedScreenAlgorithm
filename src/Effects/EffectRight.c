/*
*********************************************************************************************************
*                                    (c) Copyright 2016, Ive Wang
*                                        All Rights Reserved
*
*
* File  : EffectRight.c
* By    : Ive Wang
* Date  : 2016-05-07
*********************************************************************************************************
*/

#define __EFFECT_RIGHT_C

/*
********************************************************************************************************* 
*                                           INCLUDE HEADER FILES
********************************************************************************************************* 
*/

#include "../App/Includes.h"

/*
*********************************************************************************************************
*                                          Effect_RightRoll
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

void Effect_RightRoll(void *arg)
{
    LED_DISPLAY *ledDisp;
    LED_SCREEN_BUF *fmBuf;
    LED_SCREEN_BUF *curScBuf;
    LED_SCREEN_BUF *lstScBuf;
    UINT32 appCnt;
    UINT8 i;
    
    ledDisp = (LED_DISPLAY *)arg;
    fmBuf = ledDisp->nxtFrameBuf;
    curScBuf = ledDisp->curScreenBuf;
    lstScBuf = ledDisp->lstScreenBuf;
    appCnt = ledDisp->act[ledDisp->actCnt].effect.appearCnt;

    for (i = 0; i < 48; i++) {
        if (i < appCnt + 1) {
            fmBuf->buf[i] = lstScBuf->buf[i + (47 - appCnt)];
        } else {
            fmBuf->buf[i] = curScBuf->buf[i - (appCnt + 1)];
        }
    }
}

/*
*********************************************************************************************************
*                                          Effect_RightAppear
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

void Effect_RightAppear(void *arg)
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
        if (i < appCnt + 1) {
            fmBuf->buf[i] = scBuf->buf[i + (47 - appCnt)];
        } else {
            fmBuf->buf[i] = 0;
        }
    }
}

/*
*********************************************************************************************************
*                                       End of file EffectRight.c
*********************************************************************************************************
*/
