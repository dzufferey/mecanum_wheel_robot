#include "gui.h"

int sum(int straight, int side, int rotate) {
    return COEFF_STRAIGHT * abs(straight) +
           COEFF_SIDE * abs(side) +
           COEFF_ROTATE * abs(rotate);
}

bool increment(int* target, int delta, int* straight, int* side, int* rotate) {
    int old_val = *target;
    *target += delta;
    if (sum(*straight, *side, *rotate) <= MAX_VALUE) {
        return true;
    } else {
        *target = old_val;
        return false;
    }
}

void show_values( WINDOW* win, int straight, int side, int rotate) {
    mvwprintw(win, 1, 1, "Forward - Backward : %3d", straight);
    mvwprintw(win, 2, 1, "Left - Right       : %3d", side);
    mvwprintw(win, 3, 1, "CCW - CW           : %3d", rotate);
    mvwprintw(win, 4, 1, "overall          : %2d/%2d", sum(straight, side, rotate), MAX_VALUE);
    wrefresh(win);
}

WINDOW* window_setup() {
    initscr();              /* start curses mode */
    (void) cbreak();        /* take input chars one at a time, no wait for \n */
    (void) noecho();        /* don't echo input */
    keypad(stdscr, TRUE);   /* keypad mode: up/down, etc. */
    curs_set(0);            /* hide the cursor */

    WINDOW *my_win;
    int startx, starty, width, height;
    height = 6;
    width = 26;
    starty = (LINES - height) / 2;  /* center the window in the screen */
    startx = (COLS - width) / 2;
    my_win = newwin(height, width, starty, startx);
    box(my_win, 0 , 0);
    refresh();
    return my_win;
}

int gui_loop(WINDOW* win, int* straight, int* side, int* rotate) {
    int ch;

    if ((ch = getch()) != ERR) {
        bool changed = false;
        switch (ch) {

            case KEY_LEFT:
                changed = increment(side, -1, straight, side, rotate);
                break;
            case KEY_RIGHT:
                changed = increment(side,  1, straight, side, rotate);
                break;

            case KEY_DOWN:
                changed = increment(straight, -1, straight, side, rotate);
                break;
            case KEY_UP:
                changed = increment(straight,  1, straight, side, rotate);
                break;

            case KEY_NPAGE:
                changed = increment(rotate, -1, straight, side, rotate);
                break;
            case KEY_PPAGE:
                changed = increment(rotate,  1, straight, side, rotate);
                break;

            case 32://space
            case 10://enter
                *side = 0;
                *straight = 0;
                *rotate = 0;
                changed = true;
                break;
            
            case 'q':
                return LOOP_TERMINATE;
                break;
        }
        show_values(win, *straight, *side, *rotate);
        if (changed) {
            return LOOP_CHANGED;
        } else {
            return LOOP_NOTHING;
        }
    }
    return LOOP_TERMINATE;
}

void window_shutdown() {
    endwin();
}
