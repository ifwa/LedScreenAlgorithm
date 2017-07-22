/*
*********************************************************************************************************
*                                    (c) Copyright 2016, Ive Wang
*                                        All Rights Reserved
*
*
* File  : EffectFixed.c
* By    : Ive Wang
* Date  : 2016-05-07
*********************************************************************************************************
*/

#define __EFFECT_FIXED_C

/*
********************************************************************************************************* 
*                                           INCLUDE HEADER FILES
********************************************************************************************************* 
*/

#include "../App/Includes.h"

/*
*********************************************************************************************************
*                                          Effect_FixedDisappear
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

void Effect_FixedDisappear(void *arg)
{
    LED_DISPLAY *ledDisp;
    LED_SCREEN_BUF *fmBuf;
    UINT8 i;

    ledDisp = (LED_DISPLAY *)arg;
    fmBuf = ledDisp->nxtFrameBuf;

    for (i = 0; i < 48; i++) {
        fmBuf->buf[i] = 0;
    }
}

/*
*********************************************************************************************************
*                                          Effect_FixedAppear
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

void Effect_FixedAppear(void *arg)
{
    LED_DISPLAY *ledDisp;
    LED_SCREEN_BUF *fmBuf;
    LED_SCREEN_BUF *scBuf;
    UINT8 i;
    
    ledDisp = (LED_DISPLAY *)arg;
    fmBuf = ledDisp->nxtFrameBuf;
    scBuf = ledDisp->curScreenBuf;

    for (i = 0; i < 48; i++) {
        fmBuf->buf[i] = scBuf->buf[i];
    }
}

/*
*********************************************************************************************************
*                                       End of file EffectFixed.c
*********************************************************************************************************
*/
