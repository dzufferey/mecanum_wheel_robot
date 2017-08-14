CC = gcc
CFLAGS = -Wall -pthread --std=c99 -O3
LFLAGS = -lm -lncurses -lwiringPi -lwiringPiDev

interface: gui.h motors.h cart_interface.c gui.c motors.c
	$(CC) $(CFLAGS) $(LFLAGS) cart_interface.c gui.c motors.c -o interface

all: interface

clean:
	\rm interface
