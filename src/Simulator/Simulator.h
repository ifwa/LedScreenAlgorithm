/******************************************************************************
 * Simulator.c
 *
 * Copyright (C) 2017  WANG YIFU
 *
 * Auther: Wang Yifu
 * E-mail: 340064514@qq.com
 *
 * Note:
 *
 ******************************************************************************/

#ifndef __SIMULATOR_H
#define __SIMULATOR_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#ifdef __SIMULATOR_C
#define SIMULATOR_EXT
#else
#define SIMULATOR_EXT extern
#endif


#define NCURSES_COLOR_BK_WHITE  1
#define NCURSES_COLOR_BK_BLACK  2


typedef struct led_sim_dat {
    WINDOW *ledScreenWin;
    volatile unsigned char simRunFlag;
} LED_SIM_DAT;


SIMULATOR_EXT LED_SIM_DAT LedSimDat;


void Sim_Init(void);
void Sim_DrawDotsStart(void);
void Sim_DrawDot(int ledCoordX, int ledCoordY);
void Sim_DrawDotsEnd(void);
void Sim_ClearDot(int ledCoordX, int ledCoordY);
void Sim_LedScreenRefresh(void);


#endif
