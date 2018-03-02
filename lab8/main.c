/* main.c ---
*
* Filename: main.c
* Description:
* * Author:
* * Maintainer:
* * Created: 
* * Code: */

/*
 * Author: Dylan Wright
 * Partner: EJ Seong
 */

#include <stm32f30x.h> // Pull in include files for F30x standard drivers
#include <f3d_uart.h>
#include <f3d_user_btn.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_nunchuk.h>
#include <f3d_mag.h>
#include <stdio.h>

#define TIMER 20000

int main(void) {
  f3d_uart_init();
  //f3d_nunchuk_init();
  //delay(10); //just in case
  
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  //nunchuk_t n;

  while(1){
    //f3d_nunchuk_read(&n);

    printf("Nunchuk data: ");
    //printf("jx, c, and ax %u %u", n.jx, n.c);
  } //end while
} //end main
  
#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
  }
  #endif
