TEMPLATEROOT = ../fall2017-lab

# compilation flags for gdb

CC = gcc
CFLAGS  = -O1 -g
ASFLAGS = -g

# object files

OBJS=  $(STARTUP) main.o f3d_led.o f3d_uart.o stm32f30x_rcc.o stm32f30x_gpio.o stm32f30x_usart.o newlib_stubs.o

main.o: main.c 
	$(CC) $(CFLAGS) -c main.c 

# include common make file

include $(TEMPLATEROOT)/c335.mk
