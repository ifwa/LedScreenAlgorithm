/******************************************************************************
 * LedAct.h
 *
 * Copyright (C) 2017  WANG YIFU
 *
 * Auther: Wang Yifu
 * E-mail: 340064514@qq.com
 *
 * Note:
 *
 ******************************************************************************/

#ifndef __LED_ACT__H
#define __LED_ACT__H

#include "../App/Includes.h"

#ifdef __LED_ACT_C
#define LED_ACT_EXT
#else
#define LED_ACT_EXT extern
#endif


/* Speed */
#define LED_ACT_SPEED_LEVEL_MAX         7   // The max level of speed (Eight levels，0-7)


typedef struct led_act {
    UINT8           enable;                 // 是否使能
    
    UINT8          *contAdd;                // 内容起始地址
    UINT32          contLen;                // 内容长度
    
    LED_EFFECT      effect;                 // 特效
    
    UINT8           speedCnt;               // 速度计数器
    UINT8           speedMax;               // 速度计数器最大值
    UINT8           speedSuper;             // 超快速模式，代表一帧刷几次特效，若该值不为0，忽略速度计数器

    UINT8           twinkCnt;               // 闪烁计数器
    UINT8           twinkTms;               // 闪烁一个周期最大次数 (计数器最大值 + 1)
    
    UINT8           horseCnt;               // 跑马灯计数器
    UINT8           horseTms;               // 跑马灯一个周期最大次数 (计数器最大值 + 1)
} LED_ACT;


void LED_ActSwitch(void *arg);
void LED_ActSwitch(void *arg);
void LED_ActHandle(void *arg);


#endif
