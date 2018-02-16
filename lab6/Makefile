TEMPLATEROOT = ../fall2017-lab

# compilation flags for gdb

CFLAGS  = -O1 -g
ASFLAGS = -g

# object files

OBJS=  $(STARTUP) main.o f3d_lcd_sd.o f3d_delay.o f3d_user_btn.o f3d_led.o f3d_uart.o newlib_stubs.o stm32f30x_rcc.o stm32f30x_gpio.o stm32f30x_usart.o stm32f30x_tim.o glcdfont.o stm32f30x_spi.o

#main.o: main.c 
#	$(CC) $(CFLAGS) -c main.c 

#f3d_lcd_sd.o: ../driver/src/f3d_lcd_sd.c
#	$(CC) $(CFLAGS) -c ../driver/src/f3d_lcd_sd.c

#f3d_delay.o: ../driver/src/f3d_delay.c
#	$(CC) $(CFLAGS) -c ../driver/src/f3d_delay.c


# include common make file

include $(TEMPLATEROOT)/c335.mk
