/******************************************************************************
 * LedEffect.h
 *
 * Copyright (C) 2017  WANG YIFU
 *
 * Auther: Wang Yifu
 * E-mail: 340064514@qq.com
 *
 * Note:
 *
 ******************************************************************************/

#ifndef __LED_EFFECT__H
#define __LED_EFFECT__H

#include "../App/Includes.h"

#ifdef __LED_EFFECT_C
#define LED_EFFECT_EXT
#else
#define LED_EFFECT_EXT extern
#endif


// 特效种类 (Effect Types)
#define LED_EFFECT_LEFT                 0       // 特效: 左移 (Effect: Left Moving)
#define LED_EFFECT_RIGHT                1       // 特效: 右移 (Effect: Right Moving)
#define LED_EFFECT_UP                   2       // 特效: 上移 (Effect: Up Moving)
#define LED_EFFECT_DOWN                 3       // 特效: 下移 (Effect: Down Moving)
#define LED_EFFECT_FIXED                4       // 特效: 固定 (Effect: Fixed) (Undefined for now)
#define LED_EFFECT_CARTOON              5       // 特效: 动画 (Effect: Cartoon) (Undefined for now)
#define LED_EFFECT_SNOW                 6       // 特效: 雪花 (Effect: Snow)
#define LED_EFFECT_SCROLL               7       // 特效: 画卷 (Effect: Scroll)
#define LED_EFFECT_LASER                8       // 特效: 激光 (Effect: Laser)

// 特效模式 (Effect Modes)
// Different type of effects have similarities. So these effects can be divided into four modes.
#define LED_EFFECT_MODE_1               0       // 特效模式1: 出现->停留->出现->停留->消失 (雪花,激光,画卷,固定)
                                                // Effect Mode 1: Appear->Stay->Appear->Stay->Disappear (Snow, Laser, Scroll, Fixed)
#define LED_EFFECT_MODE_2               1       // 特效模式2: 出现->停留->消失->出现->停留->消失 (上移,下移)
                                                // Effect Mode 2: Appear->Stay->Disappear->Appear->Stay->Disappear (Up moving, Down moving)
#define LED_EFFECT_MODE_3               2       // 特效模式3: 无限左滚动 (左移)
                                                // Effect Mode 3: Keep rolling to the left (Left moving)
#define LED_EFFECT_MODE_4               3       // 特效模式4: 无限右滚动 (右移)
                                                // Effect Mode 4: Keep rolling to the right (Right moving)

// 特效状态 (Effect Stats)
#define LED_EFFECT_STAT_NONE            0       // 无状态，待初始化 (To be initialized)
#define LED_EFFECT_STAT_APPEAR          1       // 显示出现状态 (Appearing Stat)
#define LED_EFFECT_STAT_HOLD            2       // 显示停留状态 (模式1与模式2) (Staying Stat) (Mode1 & Mode2)
#define LED_EFFECT_STAT_DISAPPEAR       3       // 显示消失状态 (模式1与模式2) (Disappearing Stat) (Mode2 % Mode2)
#define LED_EFFECT_STAT_ROLL            4       // 滚动显示状态 (模式3与模式4) (Rolling Stat) (Mode3 & Mode4)


typedef struct led_effect {
    UINT8   mode;                               // 特效模式
    UINT8   stat;                               // 特效状态

    UINT32  appearCnt;                          // 出现计数器
    UINT32  appearMax;                          // 出现计数器最大值

    UINT32  holdCnt;                            // 停留计数器
    UINT32  holdTms;                            // 停留计数器次数(最大值+1)，可为0

    UINT32  disappearCnt;                       // 消失计数器
    UINT32  disappearMax;                       // 消失计数器最大值

    UINT32  screenCnt;                          // 多屏画面计数器
    UINT32  screenMax;                          // 多屏画面计数器最大值

    void  (*appearHdl)(void *);                 // 出现处理 (用于特效模式1和特效模式2)
    void  (*disappearHdl)(void *);              // 消失处理 (用于特效模式1和特效模式2)

    void  (*rollHdl)(void *);                   // 无限滚动处理 (用于特效模式3和特效模式4)
} LED_EFFECT;


void LED_EffectSet(LED_EFFECT *effectStruct, UINT8 effectName, UINT32 scrMax);
void LED_EffectHandle(void *arg);


#endif
