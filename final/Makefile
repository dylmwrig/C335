TEMPLATEROOT = ../fall2017-lab

# compilation flags for gdb

CFLAGS  = -O1 -g
ASFLAGS = -g

# object files

OBJS=  $(STARTUP) 	main.o \
			f3d_uart.o \
			f3d_nunchuk.o \
			f3d_i2c.o \
			f3d_rtc.o \
			f3d_lcd_sd.o \
			f3d_delay.o \
			stm32f30x_i2c.o \
			stm32f30x_rtc.o \
			stm32f30x_rcc.o \
			stm32f30x_tim.o \
			stm32f30x_gpio.o \
			stm32f30x_usart.o \
			stm32f30x_spi.o \
			stm32f30x_pwr.o \
			stm32f30x_dma.o \
			stm32f30x_dac.o \
			stm32f30x_misc.o \
			glcdfont.o \
			ff.o \
			mmcbb.o \
			newlib_stubs.o

# include common make file

include $(TEMPLATEROOT)/c335.mk
