#include "motors.h"

#include <pthread.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>

#include <wiringPi.h>

// for looping

/*
motor ID:
0: front left
1: back left
2: front right
3: back right
*/

const int motors_pin_dir[4] = {
    MOTOR_1_DIR,
    MOTOR_2_DIR,
    MOTOR_3_DIR,
    MOTOR_4_DIR 
};

const int motors_pin_stp[4] = {
    MOTOR_1_STP,
    MOTOR_2_STP,
    MOTOR_3_STP,
    MOTOR_4_STP
};

// for inter thread communication

pthread_t motor_thread;

typedef struct {
    bool directions[4]; // 0/false means LOW
    int dt[4];
} motors_pulses;

motors_pulses* volatile pulses;



void motors_setup() {
    wiringPiSetup();

    pinMode(MOTOR_1_DIR, OUTPUT);
    pinMode(MOTOR_1_STP, OUTPUT);
    pinMode(MOTOR_2_DIR, OUTPUT);
    pinMode(MOTOR_2_STP, OUTPUT);
    pinMode(MOTOR_3_DIR, OUTPUT);
    pinMode(MOTOR_3_STP, OUTPUT);
    pinMode(MOTOR_4_DIR, OUTPUT);
    pinMode(MOTOR_4_STP, OUTPUT);

    pinMode(NEN, OUTPUT);
    pinMode(MS1, OUTPUT);
    pinMode(MS2, OUTPUT);
    pinMode(MS3, OUTPUT);

    digitalWrite(NEN, HIGH);
    motors_stepping(MICROSTEP);
}

/*  A4988 config pins
 *  MS1     MS2     MS3     Microstep Resolution
 *  Low     Low     Low     Full step
 *  High    Low     Low     Half step
 *  Low     High    Low     Quarter step
 *  High    High    Low     Eighth step
 *  High    High    High    Sixteenth step
 */
void motors_stepping(int microsteps) {
    switch (microsteps) {
        case 1:
            digitalWrite(MS1, LOW);
            digitalWrite(MS2, LOW);
            digitalWrite(MS3, LOW);
            break;
        case 2:
            digitalWrite(MS1, HIGH);
            digitalWrite(MS2, LOW);
            digitalWrite(MS3, LOW);
            break;
        case 4:
            digitalWrite(MS1, LOW);
            digitalWrite(MS2, HIGH);
            digitalWrite(MS3, LOW);
            break;
        case 8:
            digitalWrite(MS1, HIGH);
            digitalWrite(MS2, HIGH);
            digitalWrite(MS3, LOW);
            break;
        case 16:
            digitalWrite(MS1, HIGH);
            digitalWrite(MS2, HIGH);
            digitalWrite(MS3, HIGH);
            break;
    }
}

void* motors_loop(void* ptr) {
    //local variable to keep track of the pulses
    motors_pulses* old_pulses = NULL;
    bool directions[4] = {false, false, false, false};
    int delta[4] = {0, 0, 0, 0};
    
    //default direction
    digitalWrite(MOTOR_1_DIR, LOW);
    digitalWrite(MOTOR_2_DIR, LOW);
    digitalWrite(MOTOR_3_DIR, LOW);
    digitalWrite(MOTOR_4_DIR, LOW);

    //enable the steppers
    digitalWrite(NEN, LOW);

    unsigned int time = micros();
    while(pulses != NULL) {

        //pulses changed, need to check the directions
        if (pulses != old_pulses) {
            free(old_pulses);
            old_pulses = pulses;
            for (int i = 0; i < 4; ++i) {
                if (old_pulses->directions[i] != directions[i]) {
                    directions[i] = old_pulses->directions[i];
                    digitalWrite(motors_pin_dir[i], directions[i] ? HIGH : LOW);
                    delta[i] = 2 * old_pulses->dt[i] - LOOP_USEC; //can we do better ?
                }
            }
            //XXX
            time = micros();
        }

        //set HIGH the pins that needs to be pulsed
        for (int i = 0; i < 4; ++i) {
            if(delta[i] > 0) {
                digitalWrite(motors_pin_stp[i], HIGH);
                delta[i] -= 2*LOOP_USEC;
            }
        }

        //to make sure the drivers record the pulse
        //delayMicroseconds(1);
        for (int i = 0; i < 4; ++i) {
            delta[i] += 2 * old_pulses->dt[i];
        }

        // back to LOW state
        for (int i = 0; i < 4; ++i) {
            digitalWrite(motors_pin_stp[i], LOW);
        }

        // wait for the next iteration 
        unsigned int expected = time + LOOP_USEC;
        unsigned int new_time = micros();
        unsigned int how_long = expected - new_time;
        if (how_long > LOOP_USEC) {
            //fprintf(stderr, "time: %i, new_time: %i, how_long: %i\n", time, new_time, how_long);
            //exit(-3);
        } else {
            //delayMicroseconds(how_long);
            while (micros() < expected) {}
        }
        time = new_time;
    }

    //disable the steppers
    digitalWrite(NEN, HIGH);
    return NULL;
}

void motors_shutdown() {
    pulses = NULL;
    __sync_synchronize();
    pthread_join( motor_thread, NULL);
}

void compute_pulses(motors_pulses* pulses, int straight, int side, int rotate) {
    // the overal motion for each motor
    int motors[4] = { 0, 0, 0, 0};
    motors[0] = COEFF_STRAIGHT * straight + COEFF_SIDE * side - COEFF_ROTATE * rotate;
    motors[1] = COEFF_STRAIGHT * straight - COEFF_SIDE * side - COEFF_ROTATE * rotate;
    motors[2] = COEFF_STRAIGHT * straight - COEFF_SIDE * side + COEFF_ROTATE * rotate;
    motors[3] = COEFF_STRAIGHT * straight + COEFF_SIDE * side + COEFF_ROTATE * rotate;
    for (int i = 0; i < 4; ++i) {
        pulses->directions[i] = motors[i] <= 0;
        pulses->dt[i] = abs(motors[i]) * LOOP_USEC / MAX_VALUE;
    }
}

void motors_start(int straight, int side, int rotate) {
    if (pulses == NULL) {
        pulses = (motors_pulses*) malloc(sizeof(motors_pulses));
        compute_pulses(pulses, straight, side, rotate);
        __sync_synchronize();
        int err = pthread_create( &motor_thread, NULL, motors_loop, (void*) NULL);
        if(err) {
            exit(-1);
        }
    }
}

void motors_update(int straight, int side, int rotate) {
    motors_pulses* mp = (motors_pulses*) malloc(sizeof(motors_pulses));
    compute_pulses(mp, straight, side, rotate);
    __sync_synchronize();
    pulses = mp;
    __sync_synchronize();
}
