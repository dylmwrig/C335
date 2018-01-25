TEMPLATEROOT = ../fall2017-lab

# compilation flags for gdb

CC = gcc #this wasn't in the file originally
CFLAGS  = -O1 -g
ASFLAGS = -g

# object files

OBJS=  $(STARTUP) main.o f3d_led.o f3d_user_btn.o stm32f30x_rcc.o stm32f30x_gpio.o

main.o: main.c ../driver/src/f3d_led.c ../driver/src/f3d_user_btn.c
	$(CC) $(CFLAGS) -c main.c ../driver/src/f3d_led.c ../driver/src/f3d_user_btn.c

f3d_led.o: ../driver/src/f3d_led.c
	$(CC) $(CFLAGS) -c ../driver/src/f3d_led.c

f3d_user_btn.o: ../driver/src/f3d_user_btn.c
	$(CC) $(CFLAGS) -c ../driver/src/f3d_user_btn.c

# include common make file

vpath %.c .
include $(TEMPLATEROOT)/c335.mk
