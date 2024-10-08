/* 
 * HELPERS.H: Tic-Tac-Toe AI helpers
 * ----------
 * Coded by Trinh D.D. Nguyen
 * Last updates: May, 2024
 */
#ifndef _TICTACTOE_MINIMAX_HELPERS_H_
#define _TICTACTOE_MINIMAX_HELPERS_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "defs.h"

/* =============== PROTOTYPES ==================== */

void clear();

void mssleep(long ms);

void progress_interval(int interval);

void progress_show();

/* =============================================== */

#define PROGRESS_TOTAL  12
char progress[PROGRESS_TOTAL][128] = {
    C_MEDIUM"["C_THINKING"o"C_DARK"----------"C_MEDIUM"]\r",
    C_MEDIUM"["C_THINKING"oo"C_DARK"---------"C_MEDIUM"]\r",
    C_MEDIUM"["C_DARK"-"C_THINKING"oo"C_DARK"--------"C_MEDIUM"]\r",
    C_MEDIUM"["C_DARK"--"C_THINKING"oo"C_DARK"-------"C_MEDIUM"]\r",
    C_MEDIUM"["C_DARK"---"C_THINKING"oo"C_DARK"------"C_MEDIUM"]\r",
    C_MEDIUM"["C_DARK"----"C_THINKING"oo"C_DARK"-----"C_MEDIUM"]\r",
    C_MEDIUM"["C_DARK"-----"C_THINKING"oo"C_DARK"----"C_MEDIUM"]\r",
    C_MEDIUM"["C_DARK"------"C_THINKING"oo"C_DARK"---"C_MEDIUM"]\r",
    C_MEDIUM"["C_DARK"-------"C_THINKING"oo"C_DARK"--"C_MEDIUM"]\r",
    C_MEDIUM"["C_DARK"--------"C_THINKING"oo"C_DARK"-"C_MEDIUM"]\r",
    C_MEDIUM"["C_DARK"---------"C_THINKING"oo"C_MEDIUM"]\r",
    C_MEDIUM"["C_DARK"----------"C_THINKING"o"C_MEDIUM"]\r",
};
int progress_current = 0;
int progress_dir = +1;
int progress_pacifier = 0;
int progress_update = 1;

void clear() {
    puts("\x1b[2J\x1b[H");
}

void mssleep(long ms) {
#ifndef _WIN32
	#ifndef __DJGPP__
		struct timespec rem;
		struct timespec req = { (int)(ms / 1000U), (ms % 1000U) * 1000000UL };
		nanosleep(&req , &rem);
	#else
		clock_t start = clock();
		while (clock() < start + ms/1000) ;
	#endif
#else
	Sleep(ms);
#endif
}

void progress_interval(int interval) {
    progress_update = interval * BOARD_SIZE;
}

void progress_show() {
    progress_pacifier++;
    if (progress_pacifier % progress_update == 0) {
        fputs(C_X"Thinking"C_NORMAL": ", stdout);
        fputs(progress[progress_current], stdout);
        fflush(stdout);
#ifdef _USE_ALPHA_BETA_PRUNE_
        mssleep(5);
#else
        mssleep(1);
#endif
        progress_current+=progress_dir;
        if (progress_current <= 0 || progress_current >= PROGRESS_TOTAL-1)
            progress_dir *= -1;
    }
}

#endif