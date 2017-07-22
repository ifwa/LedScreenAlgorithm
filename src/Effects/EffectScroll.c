/*
*********************************************************************************************************
*                                    (c) Copyright 2016, Ive Wang
*                                        All Rights Reserved
*
*
* File  : EffectScroll.c
* By    : Ive Wang
* Date  : 2016-05-02
*********************************************************************************************************
*/

#define __EFFECT_SCROLL_C

/*
********************************************************************************************************* 
*                                           INCLUDE HEADER FILES
********************************************************************************************************* 
*/

#include "../App/Includes.h"

/*
*********************************************************************************************************
*                                          Effect_ScrollDisappear
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

void Effect_ScrollDisappear(void *arg)
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
        if (i > 0 + disCnt && i < 48 - disCnt) {
            fmBuf->buf[i] = scBuf->buf[i];
        } else if (i == 0 + disCnt || i == 48 - disCnt) {
            fmBuf->buf[i] = 0x0FFF;
        } else {
            fmBuf->buf[i] = 0;
        }
    }
}

/*
*********************************************************************************************************
*                                          Effect_ScrollAppear
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

void Effect_ScrollAppear(void *arg)
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
        if (appCnt == 24) {
            fmBuf->buf[i] = scBuf->buf[i];
        } else {
            if (i > 23 - appCnt && i < 24 + appCnt) {
                fmBuf->buf[i] = scBuf->buf[i];
            } else if (i == 23 - appCnt || i == 24 + appCnt) {
                fmBuf->buf[i] = 0x0FFF;
            } else {
                fmBuf->buf[i] = 0;
            }
        }
    }
}

/*
*********************************************************************************************************
*                                       End of file EffectScroll.c
*********************************************************************************************************
*/
