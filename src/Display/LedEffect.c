/******************************************************************************
 * LedEffect.c
 *
 * Copyright (C) 2017  WANG YIFU
 *
 * Auther: Wang Yifu
 * E-mail: 340064514@qq.com
 *
 * Note:
 *
 ******************************************************************************/

#define __LED_EFFECT_C

#include "../App/Includes.h"


void LED_EffectSet(LED_EFFECT *effectStruct, UINT8 effectName, UINT32 scrMax)
{
    switch (effectName) {
        case LED_EFFECT_LEFT:
            effectStruct->mode = LED_EFFECT_MODE_3;
            effectStruct->stat = LED_EFFECT_STAT_NONE;
            effectStruct->appearMax = 47;
            effectStruct->screenMax = scrMax;
            effectStruct->appearHdl = Effect_LeftAppear;
            effectStruct->rollHdl = Effect_LeftRoll;
            break;
        case LED_EFFECT_RIGHT:
            effectStruct->mode = LED_EFFECT_MODE_4;
            effectStruct->stat = LED_EFFECT_STAT_NONE;
            effectStruct->appearMax = 47;
            effectStruct->screenMax = scrMax;
            effectStruct->appearHdl = Effect_RightAppear;
            effectStruct->rollHdl = Effect_RightRoll;
            break;
        case LED_EFFECT_UP:
            effectStruct->mode = LED_EFFECT_MODE_2;
            effectStruct->stat = LED_EFFECT_STAT_NONE;
            effectStruct->appearMax = 11;
            effectStruct->holdTms = 0;
            effectStruct->disappearMax = 11;
            effectStruct->screenMax = scrMax;
            effectStruct->appearHdl = Effect_UpAppear;
            effectStruct->disappearHdl = Effect_UpDisappear;
            break;
        case LED_EFFECT_DOWN:
            effectStruct->mode = LED_EFFECT_MODE_2;
            effectStruct->stat = LED_EFFECT_STAT_NONE;
            effectStruct->appearMax = 11;
            effectStruct->holdTms = 0;
            effectStruct->disappearMax = 11;
            effectStruct->screenMax = scrMax;
            effectStruct->appearHdl = Effect_DownAppear;
            effectStruct->disappearHdl = Effect_DownDisappear;
            break;
        case LED_EFFECT_CARTOON:
        case LED_EFFECT_FIXED:
            effectStruct->mode = LED_EFFECT_MODE_1;
            effectStruct->stat = LED_EFFECT_STAT_NONE;
            effectStruct->appearMax = 0;
            effectStruct->holdTms = 12;
            effectStruct->disappearMax = 0;
            effectStruct->screenMax = scrMax;
            effectStruct->appearHdl = Effect_FixedAppear;
            effectStruct->disappearHdl = Effect_FixedDisappear;
            break;
        case LED_EFFECT_SNOW:
            effectStruct->mode = LED_EFFECT_MODE_1;
            effectStruct->stat = LED_EFFECT_STAT_NONE;
            effectStruct->appearMax = 22;
            effectStruct->holdTms = 23;
            effectStruct->disappearMax = 22;
            effectStruct->screenMax = scrMax;
            effectStruct->appearHdl = Effect_SnowAppear;
            effectStruct->disappearHdl = Effect_SnowDisappear;
            break;
        case LED_EFFECT_SCROLL:
            effectStruct->mode = LED_EFFECT_MODE_1;
            effectStruct->stat = LED_EFFECT_STAT_NONE;
            effectStruct->appearMax = 24;
            effectStruct->holdTms = 25;
            effectStruct->disappearMax = 24;
            effectStruct->screenMax = scrMax;
            effectStruct->appearHdl = Effect_ScrollAppear;
            effectStruct->disappearHdl = Effect_ScrollDisappear;
            break;
        case LED_EFFECT_LASER:
            effectStruct->mode = LED_EFFECT_MODE_1;
            effectStruct->stat = LED_EFFECT_STAT_NONE;
            effectStruct->appearMax = 47;
            effectStruct->holdTms = 48;
            effectStruct->disappearMax = 47;
            effectStruct->screenMax = scrMax;
            effectStruct->appearHdl = Effect_LaserAppear;
            effectStruct->disappearHdl = Effect_LaserDisappear;
            break;
        default:
            break;
    }
}

void LED_EffectInitMode4(void *arg)
{
    LED_DISPLAY *ledDisp;
    LED_EFFECT *effect;
    ledDisp = (LED_DISPLAY *)arg;
    effect = &(ledDisp->act[ledDisp->actCnt].effect);
    
    effect->appearCnt = 0;
    effect->screenCnt = effect->screenMax;
    effect->stat = LED_EFFECT_STAT_APPEAR;

    LED_DisplayCurScrUpd(ledDisp);
    LED_DisplayLstScrUpd(ledDisp);
}

void LED_EffectHandleMode4(void *arg)
{
    LED_DISPLAY *ledDisp;
    LED_EFFECT *effect;
    UINT8 i;
    ledDisp = (LED_DISPLAY *)arg;
    effect = &(ledDisp->act[ledDisp->actCnt].effect);

    switch (effect->stat) {
        case LED_EFFECT_STAT_NONE:
            LED_EffectInitMode4(arg);
            for (i = 0; i < LED_SCREEN_MAX_WORDS; i++) {
                ledDisp->nxtFrameBuf->buf[i] = 0;
            }
            break;
        case LED_EFFECT_STAT_APPEAR:
            if (effect->appearCnt <= effect->appearMax) {
                ledDisp->act[ledDisp->actCnt].effect.appearHdl((void *)ledDisp);
            }
            effect->appearCnt++;
            if (effect->appearCnt > effect->appearMax) {
                effect->appearCnt = 0;
                effect->stat = LED_EFFECT_STAT_ROLL;
            }
            break;
        case LED_EFFECT_STAT_ROLL:
            if (effect->appearCnt <= effect->appearMax) {
                ledDisp->act[ledDisp->actCnt].effect.rollHdl((void *)ledDisp);
            }
            effect->appearCnt++;
            if (effect->appearCnt > effect->appearMax) {
                effect->appearCnt = 0;
                if (effect->screenCnt == 0) {
                    effect->stat = LED_EFFECT_STAT_NONE;
                    LED_ActSwitch(arg);
                } else {
                    effect->screenCnt--;
                    LED_DisplayCurScrUpd(ledDisp);
                    LED_DisplayLstScrUpd(ledDisp);
                }
            }
            break;
        default:
            break;
    }
}

void LED_EffectInitMode3(void *arg)
{
    LED_DISPLAY *ledDisp;
    LED_EFFECT *effect;
    ledDisp = (LED_DISPLAY *)arg;
    effect = &(ledDisp->act[ledDisp->actCnt].effect);
    
    effect->appearCnt = 0;
    effect->screenCnt = 0;
    effect->stat = LED_EFFECT_STAT_APPEAR;

    LED_DisplayCurScrUpd(ledDisp);
    LED_DisplayNxtScrUpd(ledDisp);
}

void LED_EffectHandleMode3(void *arg)
{
    LED_DISPLAY *ledDisp;
    LED_EFFECT *effect;
    UINT8 i;
    ledDisp = (LED_DISPLAY *)arg;
    effect = &(ledDisp->act[ledDisp->actCnt].effect);

    switch (effect->stat) {
        case LED_EFFECT_STAT_NONE:
            LED_EffectInitMode3(arg);
            for (i = 0; i < LED_SCREEN_MAX_WORDS; i++) {
                ledDisp->nxtFrameBuf->buf[i] = 0;
            }
            break;
        case LED_EFFECT_STAT_APPEAR:
            if (effect->appearCnt <= effect->appearMax) {
                ledDisp->act[ledDisp->actCnt].effect.appearHdl((void *)ledDisp);
            }
            effect->appearCnt++;
            if (effect->appearCnt > effect->appearMax) {
                effect->appearCnt = 0;
                effect->stat = LED_EFFECT_STAT_ROLL;
            }
            break;
        case LED_EFFECT_STAT_ROLL:
            if (effect->appearCnt <= effect->appearMax) {
                ledDisp->act[ledDisp->actCnt].effect.rollHdl((void *)ledDisp);
            }
            effect->appearCnt++;
            if (effect->appearCnt > effect->appearMax) {
                effect->appearCnt = 0;
                if (effect->screenCnt >= effect->screenMax) {
                    effect->stat = LED_EFFECT_STAT_NONE;
                    LED_ActSwitch(arg);
                } else {
                    effect->screenCnt++;
                    LED_DisplayCurScrUpd(ledDisp);
                    LED_DisplayNxtScrUpd(ledDisp);
                }
            }
            break;
        default:
            break;
    }
}

void LED_EffectInitMode2(void *arg)
{
    LED_DISPLAY *ledDisp;
    LED_EFFECT *effect;
    ledDisp = (LED_DISPLAY *)arg;
    effect = &(ledDisp->act[ledDisp->actCnt].effect);
    
    effect->appearCnt = 0;
    effect->holdCnt = 0;
    effect->disappearCnt = 0;
    effect->screenCnt = 0;
    effect->stat = LED_EFFECT_STAT_APPEAR;

    LED_DisplayCurScrUpd(ledDisp);
}

void LED_EffectHandleMode2(void *arg)
{
    LED_DISPLAY *ledDisp;
    LED_EFFECT *effect;
    UINT8 i;
    ledDisp = (LED_DISPLAY *)arg;
    effect = &(ledDisp->act[ledDisp->actCnt].effect);

    switch (effect->stat) {
        case LED_EFFECT_STAT_NONE:
            LED_EffectInitMode2(arg);
            for (i = 0; i < LED_SCREEN_MAX_WORDS; i++) {
                ledDisp->nxtFrameBuf->buf[i] = 0;
            }
            break;
        case LED_EFFECT_STAT_APPEAR:
            if (effect->appearCnt <= effect->appearMax) {
                ledDisp->act[ledDisp->actCnt].effect.appearHdl((void *)ledDisp);
            }
            effect->appearCnt++;
            if (effect->appearCnt > effect->appearMax) {
                effect->appearCnt = 0;
                if (effect->holdTms != 0) {
                    effect->stat = LED_EFFECT_STAT_HOLD;
                } else {
                    effect->stat = LED_EFFECT_STAT_DISAPPEAR;
                }
            }
            break;
        case LED_EFFECT_STAT_HOLD:
            if (effect->holdCnt < effect->holdTms) {
                for (i = 0; i < LED_SCREEN_MAX_WORDS; i++) {
                    ledDisp->nxtFrameBuf->buf[i] = ledDisp->curFrameBuf->buf[i];
                }
            }
            effect->holdCnt++;
            if (effect->holdCnt >= effect->holdTms) {
                effect->holdCnt = 0;
                effect->stat = LED_EFFECT_STAT_DISAPPEAR;
            }
            break;
        case LED_EFFECT_STAT_DISAPPEAR:
            if (effect->disappearCnt <= effect->disappearMax) {
                ledDisp->act[ledDisp->actCnt].effect.disappearHdl((void *)ledDisp);
            }
            effect->disappearCnt++;
            if (effect->disappearCnt > effect->disappearMax) {
                effect->disappearCnt = 0;
                if (effect->screenCnt >= effect->screenMax) {
                    effect->stat = LED_EFFECT_STAT_NONE;
                    LED_ActSwitch(arg);
                } else {
                    effect->screenCnt++;
                    LED_DisplayCurScrUpd(ledDisp);
                    effect->stat = LED_EFFECT_STAT_APPEAR;
                }
            }
            break;
        default:
            break;
    }
}

void LED_EffectInitMode1(void *arg)
{
    LED_DISPLAY *ledDisp;
    LED_EFFECT *effect;
    ledDisp = (LED_DISPLAY *)arg;
    effect = &(ledDisp->act[ledDisp->actCnt].effect);
    
    effect->appearCnt = 0;
    effect->holdCnt = 0;
    effect->disappearCnt = 0;
    effect->screenCnt = 0;
    effect->stat = LED_EFFECT_STAT_APPEAR;

    LED_DisplayCurScrUpd(ledDisp);
}

void LED_EffectHandleMode1(void *arg)
{
    LED_DISPLAY *ledDisp;
    LED_EFFECT *effect;
    UINT8 i;
    ledDisp = (LED_DISPLAY *)arg;
    effect = &(ledDisp->act[ledDisp->actCnt].effect);

    switch (effect->stat) {
        case LED_EFFECT_STAT_NONE:
            LED_EffectInitMode1(arg);
            for (i = 0; i < LED_SCREEN_MAX_WORDS; i++) {
                ledDisp->nxtFrameBuf->buf[i] = 0;
            }
            break;
        case LED_EFFECT_STAT_APPEAR:
            if (effect->appearCnt <= effect->appearMax) {
                ledDisp->act[ledDisp->actCnt].effect.appearHdl((void *)ledDisp);
            }
            effect->appearCnt++;
            if (effect->appearCnt > effect->appearMax) {
                effect->appearCnt = 0;
                if (effect->holdTms != 0) {
                    effect->stat = LED_EFFECT_STAT_HOLD;
                } else {
                    effect->stat = LED_EFFECT_STAT_DISAPPEAR;
                }
            }
            break;
        case LED_EFFECT_STAT_HOLD:
            if (effect->holdCnt < effect->holdTms) {
                for (i = 0; i < LED_SCREEN_MAX_WORDS; i++) {
                    ledDisp->nxtFrameBuf->buf[i] = ledDisp->curFrameBuf->buf[i];
                }
            }
            effect->holdCnt++;
            if (effect->holdCnt >= effect->holdTms) {
                effect->holdCnt = 0;
                if (effect->screenCnt >= effect->screenMax) {
                    effect->stat = LED_EFFECT_STAT_DISAPPEAR;
                } else {
                    effect->screenCnt++;
                    LED_DisplayCurScrUpd(ledDisp);
                    effect->stat = LED_EFFECT_STAT_APPEAR;
                }
            }
            break;
        case LED_EFFECT_STAT_DISAPPEAR:
            if (effect->disappearCnt <= effect->disappearMax) {
                ledDisp->act[ledDisp->actCnt].effect.disappearHdl((void *)ledDisp);
            }
            effect->disappearCnt++;
            if (effect->disappearCnt > effect->disappearMax) {
                effect->disappearCnt = 0;
                effect->stat = LED_EFFECT_STAT_NONE;
                LED_ActSwitch(arg);
            }
            break;
        default:
            break;
    }
}

void LED_EffectHandle(void *arg)
{
    LED_DISPLAY *ledDisp;
    ledDisp = (LED_DISPLAY *)arg;

    switch (ledDisp->act[ledDisp->actCnt].effect.mode) {
        case LED_EFFECT_MODE_1:
            LED_EffectHandleMode1(arg);
            break;
        case LED_EFFECT_MODE_2:
            LED_EffectHandleMode2(arg);
            break;
        case LED_EFFECT_MODE_3:
            LED_EffectHandleMode3(arg);
            break;
        case LED_EFFECT_MODE_4:
            LED_EffectHandleMode4(arg);
            break;
        default:
            break;
    }
}
