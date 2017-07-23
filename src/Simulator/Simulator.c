/******************************************************************************
 * Simulator.c
 *
 * Copyright (C) 2017  WANG YIFU
 *
 * Auther: Wang Yifu
 * E-mail: 340064514@qq.com
 *
 * Note: This is a simulator run in UNIX terminal through ncurses library.
 *
 ******************************************************************************/

#define __SIMULATOR_C

#include "../App/Includes.h"


void Sim_TimerISR(void)
{
    while (LedSimDat.simRunFlag) {
        usleep(417);
        LED_TimerIsrHdl();
    }
}

void Sim_KeyDetect(void){
    getch();
    LedSimDat.simRunFlag = 0;
}

/*
 * Macro "LINES" means the vertical characters in the terminal sreen.
 * Macro "COLS" means the horizontal characters in the terminal sreen.
 * Coordinate Y in the ncurses function means the vertical position.
 * Coordinate X in the ncurses function means the horizontal position.
 */
void Sim_Init(void)
{
    unsigned int i;

    // Init the ncurses
    initscr();
    raw();
    noecho();
    curs_set(0);
    if (has_colors() == FALSE) {
        endwin();
        printf("You need a terminal that supports color to run this simulator.\n");
        exit(1);
    }
    if (COLS < 48 * 2 + 2 || LINES < 12 + 2) {
        endwin();
        printf("Please drag the terminal window bigger or set the font size smaller.\n");
        exit(1);
    }
    start_color();
    init_pair(NCURSES_COLOR_BK_WHITE, COLOR_BLACK, COLOR_WHITE);
    init_pair(NCURSES_COLOR_BK_BLACK, COLOR_WHITE, COLOR_BLACK);
    bkgd(COLOR_PAIR(NCURSES_COLOR_BK_WHITE));
    // Create the LED screen window
    int ledWinStartX = (COLS - 48 * 2) / 2;
    int ledWinStartY = (LINES - 8) / 2;
    int ledWinWidth = 48 * 2;
    int ledWinHight = 12;
    LedSimDat.ledScreenWin = newwin(ledWinHight, ledWinWidth, ledWinStartY, ledWinStartX);
    wbkgd(LedSimDat.ledScreenWin, COLOR_PAIR(NCURSES_COLOR_BK_WHITE));
    attron(COLOR_PAIR(NCURSES_COLOR_BK_WHITE));
    mvprintw(ledWinStartY - 1, ledWinStartX - 1, "%s%s",
             "---------LED Screen Simulator (48 pixels x 8 pixe",
             "ls)----------------------------------------------");
    mvprintw(ledWinStartY + ledWinHight, ledWinStartX - 1, "%s%s",
             "-------------------------------------------------",
             "------------------Press any key to exit.---------");
    for (i = 0; i < ledWinHight; i++) {
        mvaddch(ledWinStartY + i, ledWinStartX - 1, '|');
        mvaddch(ledWinStartY + i, ledWinStartX + ledWinWidth, '|');
    }
    attroff(COLOR_PAIR(NCURSES_COLOR_BK_WHITE));
    refresh();
    wrefresh(LedSimDat.ledScreenWin);
    // Init timer ISR thread and key detect thread
    LedSimDat.simRunFlag = 1;
    pthread_t timerPid, keyPid;
    if (pthread_create(&timerPid, NULL, (void *)Sim_TimerISR, NULL) != 0) {
        printf("Create thread error.\n");
        endwin();
        exit(1);
    }
    pthread_detach(timerPid);
    if (pthread_create(&keyPid, NULL, (void *)Sim_KeyDetect, NULL) != 0) {
        printf("Create thread error.\n");
        endwin();
        exit(1);
    }
    pthread_detach(keyPid);
}

//void Sim_DrawDotsStart(void)
//{
//    wattron(LedSimDat.ledScreenWin, COLOR_PAIR(NCURSES_COLOR_BK_BLACK));
//}
//
//void Sim_DrawDot(int ledCoordX, int ledCoordY)
//{
//    mvwprintw(LedSimDat.ledScreenWin, ledCoordY, ledCoordX * 2, "  ");
//}
//
//void Sim_DrawDotsEnd(void)
//{
//    wattroff(LedSimDat.ledScreenWin, COLOR_PAIR(NCURSES_COLOR_BK_BLACK));
//    wrefresh(LedSimDat.ledScreenWin);
//}
//
//void Sim_ClearDotsStart(void)
//{
//    wattron(LedSimDat.ledScreenWin, COLOR_PAIR(NCURSES_COLOR_BK_BLACK));
//}
//
//void Sim_ClearDot(int ledCoordX, int ledCoordY)
//{
//    mvwprintw(LedSimDat.ledScreenWin, ledCoordY, ledCoordX * 2, "  ");
//}
//
//void Sim_ClearDotsEnd(void)
//{
//    wattroff(LedSimDat.ledScreenWin, COLOR_PAIR(NCURSES_COLOR_BK_BLACK));
//    wrefresh(LedSimDat.ledScreenWin);
//}

void Sim_DrawDot(int ledCoordX, int ledCoordY)
{
    wattron(LedSimDat.ledScreenWin, COLOR_PAIR(NCURSES_COLOR_BK_BLACK));
    mvwprintw(LedSimDat.ledScreenWin, ledCoordY, ledCoordX * 2, "  ");
    wattroff(LedSimDat.ledScreenWin, COLOR_PAIR(NCURSES_COLOR_BK_BLACK));
}

void Sim_ClearDot(int ledCoordX, int ledCoordY)
{
    wattron(LedSimDat.ledScreenWin, COLOR_PAIR(NCURSES_COLOR_BK_WHITE));
    mvwprintw(LedSimDat.ledScreenWin, ledCoordY, ledCoordX * 2, "  ");
    wattroff(LedSimDat.ledScreenWin, COLOR_PAIR(NCURSES_COLOR_BK_WHITE));
}

void Sim_LedScreenRefresh(void)
{
    wrefresh(LedSimDat.ledScreenWin);
}
