/* main.c ---
*
* Filename: main.c
* Description:
* * Author:
* * Maintainer:
* * Created: Thu Jan 10 11:23:43 2013
* * Code: */

#include <stm32f30x.h> // Pull in include files for F30x standard drivers
#include <f3d_uart.h>
#include <f3d_user_btn.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <stdio.h>

#define TIMER 20000

int main(void) {
  // Set up your inits before you go ahead  
  f3d_uart_init();
  delay(10);
  f3d_i2c1_init();
  delay(10);
  //f3d_mag_init();
  delay(10);
  f3d_lcd_init();
  delay(10);
  f3d_user_btn_init();
  delay(10);
  f3d_accel_init();
  delay(10);
  f3d_lcd_fillScreen(RED); 

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  while(1){

  } //end while
} //end main
  
#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
  }
  #endif

  /* main.c ends here */


