/*
 *  Author: Dylan Wright
 *  Partner: ya boi, Dylan Wright
 */

#include <stm32f30x.h>  // Pull in include files for F30x standard drivers  
#include <f3d_led.h> 
#include <f3d_uart.h> 
#include <f3d_gyro.h> 
#include <f3d_lcd_sd.h> 
#include <f3d_i2c.h> 
#include <f3d_accel.h> 
#include <f3d_mag.h> 
#include <f3d_nunchuk.h> 
#include <f3d_rtc.h> 
#include <stdio.h> 
#include <string.h> //strlen 
#include <queue.h>

int main(){

  f3d_uart_init();
  delay(10);
 
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

queue_t q;

  return 0;
} //end main
