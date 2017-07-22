/*
*********************************************************************************************************
*                                    (c) Copyright 2016, Ive Wang
*                                        All Rights Reserved
*
*
* File  : EffectSnow.c
* By    : Ive Wang
* Date  : 2016-05-02
*********************************************************************************************************
*/

#define __EFFECT_SNOW_C

/*
********************************************************************************************************* 
*                                           INCLUDE HEADER FILES
********************************************************************************************************* 
*/

#include "../App/Includes.h"

/*
*********************************************************************************************************
*                                          Effect_SnowDisappear
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

void Effect_SnowDisappear(void *arg)
{
    LED_DISPLAY *ledDisp;
    LED_SCREEN_BUF *fmBuf;
    LED_SCREEN_BUF *scBuf;
    UINT32 disCnt;
    UINT8 i, j;
    UINT16 tmp;

    ledDisp = (LED_DISPLAY *)arg;
    fmBuf = ledDisp->nxtFrameBuf;
    scBuf = ledDisp->curScreenBuf;
    disCnt = ledDisp->act[ledDisp->actCnt].effect.disappearCnt;

    if (disCnt < 11) {              // 文字至少有一行还在顶部
        for (i = 0; i < 48; i++) {
            tmp = 0;
            for (j = 0; j < 11 - disCnt; j++) {
                tmp |= scBuf->buf[i] & (0x0001 << j);
            }
            fmBuf->buf[i] = tmp;
            tmp = 0;
            for (j = 0; j < 12 - (11 - disCnt); j++) {
                if ((j + 1) % 2 == 0) {
                    tmp |= ((scBuf->buf[i] >> (11 - disCnt  + (j - 1) / 2)) % 2) << (11 - disCnt + j);
                }
            }
            fmBuf->buf[i] |= tmp;
        }
    } else {                        // 文字已全部离开
        for (i = 0; i < 48; i++) {
            tmp = 0;
            for (j = 0; j < 22 - disCnt; j++) {
                if (j % 2 == 0) {
                    tmp |= ((scBuf->buf[i] >> (j / 2)) % 2) << (disCnt - 10 + j);
                }
            }
            fmBuf->buf[i] = tmp;
        }
    }
}

/*
*********************************************************************************************************
*                                          Effect_SnowAppear
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

void Effect_SnowAppear(void *arg)
{
    LED_DISPLAY *ledDisp;
    LED_SCREEN_BUF *fmBuf;
    LED_SCREEN_BUF *scBuf;
    UINT32 appCnt;
    UINT8 i, j;
    UINT16 tmp;
    
    ledDisp = (LED_DISPLAY *)arg;
    fmBuf = ledDisp->nxtFrameBuf;
    scBuf = ledDisp->curScreenBuf;
    appCnt = ledDisp->act[ledDisp->actCnt].effect.appearCnt;

    if (appCnt < 11) {              // 文字全在空中
        for (i = 0; i < 48; i++) {
            tmp = 0;
            for (j = 0; j < appCnt + 1; j++) {
                if (j % 2 == 0) {
                    tmp |= (scBuf->buf[i] >> (11 - j / 2)) % 2;
                }
                tmp = tmp << 1;
            }
            tmp = tmp >> 1;
            fmBuf->buf[i] = tmp;
        }
    } else {                        // 文字至少有一行已经落地
        for (i = 0; i < 48; i++) {
            tmp = 0;
            for (j = 0; j < appCnt - 11 + 1; j++) {
                tmp |= scBuf->buf[i] & (0x0001 << (11 - j));
            }
            fmBuf->buf[i] = tmp;
            tmp = 0;
            for (j = 0; j < 12 - (appCnt - 11 + 1); j++) {
                if ((j + 1) % 2 == 0) {
                    tmp |= (scBuf->buf[i] >> (11 - (appCnt - 11 + 1) - j / 2)) % 2;
                }
                tmp = tmp << 1;
            }
            tmp = tmp >> 1;
            fmBuf->buf[i] |= tmp;
        }
    }
}

/*
*********************************************************************************************************
*                                       End of file EffectSnow.c
*********************************************************************************************************
*/
