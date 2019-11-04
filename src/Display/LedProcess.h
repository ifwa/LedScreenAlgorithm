/******************************************************************************
 * LedProcess.h
 *
 * Copyright (C) 2017  WANG YIFU
 *
 * Auther: Wang Yifu
 * E-mail: 340064514@qq.com
 *
 * Note:
 *
 ******************************************************************************/

#ifndef __LED_PROCESS_H
#define __LED_PROCESS_H

#include "../App/Includes.h"

#ifdef __LED_PROCESS_C
#define LED_PROCESS_EXT
#else
#define LED_PROCESS_EXT extern
#endif


/* LED显示 - 模式 (LED Display - Mode) */
#define LED_DISPLAY_MODE_OFF                0           // 关屏模式 (Screen-off Mode)
#define LED_DISPLAY_MODE_BAT                1           // 电池模式 (Battery Mode)
#define LED_DISPLAY_MODE_NOR                2           // 正常模式 (Normal Mode)

/* LED显示 - 亮度 (LED Display - Brightness Level: 0 ~ 3) */
#define LED_DISPLAY_BRIGHT_25               0
#define LED_DISPLAY_BRIGHT_50               1
#define LED_DISPLAY_BRIGHT_75               2
#define LED_DISPLAY_BRIGHT_100              3
#define LED_DISPLAY_BRIGHT_LEVEL_MAX        3           // 最大亮度等级(共四级，0-3)

/* LED屏幕 - 列数(实际显示的两列在程序中算一列，为一个最小显示单位) */
/* LED Screen - Number of Columns */
/* (The actual two columns are considered to be one column in the code. It is the minimum display unit.) */
#define LED_SCREEN_MAX_COL                  23

/* LED屏幕 - 字数(一个字中，只用到16位，所以可用16位整型定义) */
/* LED Screen - Number of Words */
#define LED_SCREEN_MAX_WORDS                48


typedef struct led_screen_buf {
    UINT16          buf[LED_SCREEN_MAX_WORDS];
} LED_SCREEN_BUF;

typedef struct led_display {
    UINT8           mode;                   // 显示模式

    UINT8           refresh;                // 刷新下一帧标志

    UINT8           brightCnt;              // 亮度计数器
    UINT8           brightness;             // 亮度 (计数器小于等于该值时，需要刷新文字)

    UINT8           actCnt;                 // 幕计数器
    UINT8           actMax;                 // 幕计数器最大值
    LED_ACT         act[CONFIG_LED_SCREEN_ACTS];

    UINT8           colCnt;                 // 列计数器 (实际硬件环境为两列)

    LED_SCREEN_BUF *curFrameBuf;            // 当前正在扫描的帧缓存
    LED_SCREEN_BUF *nxtFrameBuf;            // 下一帧的帧缓存
    LED_SCREEN_BUF *curScreenBuf;           // 当前无特效状态的显示缓存
    LED_SCREEN_BUF *nxtScreenBuf;           // 下一无特效状态的显示缓存
    LED_SCREEN_BUF *lstScreenBuf;           // 上一无特效状态的显示缓存 (与nxtScreenBuf不会同一特效用到，所以可共享buf)
} LED_DISPLAY;


LED_PROCESS_EXT LED_DISPLAY     LedDisplay;
LED_PROCESS_EXT LED_SCREEN_BUF  LedFrameBuf1;
LED_PROCESS_EXT LED_SCREEN_BUF  LedFrameBuf2;
LED_PROCESS_EXT LED_SCREEN_BUF  LedScreenBuf1;
LED_PROCESS_EXT LED_SCREEN_BUF  LedScreenBuf2;


void LED_DisplayCurScrUpd(LED_DISPLAY *ledDisp);
void LED_DisplayNxtScrUpd(LED_DISPLAY *ledDisp);
void LED_DisplayLstScrUpd(LED_DISPLAY *ledDisp);
void LED_DisplayInit(void);
void LED_Process(void);
void LED_TimerIsrHdl(void);


#endif
