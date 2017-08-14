#pragma once

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>     /* include before curses.h to work around glibc bug */
#include <ctype.h>

#include <ncurses.h>

#include "motors.h"

#define LOOP_CHANGED 1
#define LOOP_NOTHING 0
#define LOOP_TERMINATE -1

void show_values( WINDOW* win, int straight, int side, int rotate);

WINDOW* window_setup();

int gui_loop(WINDOW* win, int* straight, int* side, int* rotate);

void window_shutdown();
