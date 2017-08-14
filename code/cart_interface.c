
#include "gui.h"
#include "motors.h"

int main(int argc, char *argv[]) {
    
    int side = 0;
    int straight = 0;
    int rotate = 0;

    motors_setup();
    motors_start(straight, side, rotate);

    WINDOW *my_win = window_setup();
    show_values(my_win, straight, side, rotate);

    bool again = true;
    while(again) {
        int result = gui_loop(my_win, &straight, &side, &rotate);
        switch (result) {
            case LOOP_TERMINATE:
                again = false;
                break;
            case LOOP_NOTHING:
                break;
            case LOOP_CHANGED:
                motors_update(straight, side, rotate);
                break;
        }
    }

    motors_shutdown();
    window_shutdown();

    exit(0);
}
