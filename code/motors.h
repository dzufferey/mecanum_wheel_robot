#pragma once

#define MOTOR_1_DIR  0
#define MOTOR_1_STP  1
#define MOTOR_2_DIR  2
#define MOTOR_2_STP  3
#define MOTOR_3_DIR  4
#define MOTOR_3_STP  5
#define MOTOR_4_DIR  6
#define MOTOR_4_STP  7
#define NEN  8
#define MS1  9
#define MS2  10
#define MS3  11

#define MAX_VALUE 40
#define COEFF_STRAIGHT 1
#define COEFF_SIDE 2
#define COEFF_ROTATE 1

#define MICROSTEP 16
#define LOOP_USEC 250

/*
The thread that deals with making pulse to the stepper is base on https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm.

Sychronization between the thread. In c99 and gcc we can use:
- __thread for threadlocal variables
- __sync_synchronize() for memory barrier
        
motion  | front left | front right | back left | back right |
--------|------------|-------------|-----------|------------|
straight|       1    |          1  |        1  |        1   |
side    |       2    |         -2  |       -2  |        2   |
rotate  |      -1    |          1  |       -1  |        1   |
--------|------------|-------------|-----------|------------|
the factor 2 for the side comes from the 30° angle of the rollers

*/

void motors_setup();
void motors_shutdown();
void motors_start(int straight, int side, int rotate);
void motors_update(int straight, int side, int rotate);
void motors_stepping(int microsteps);
