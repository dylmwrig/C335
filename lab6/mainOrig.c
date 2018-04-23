/* main.c 
* Filename: main.c
* Description:
* * Author:
* * Maintainer:
* * Created: Thu Jan 10 11:23:43 2013
* * Code: */

#include <stm32f30x.h> // Pull in include files for F30x standard drivers
#include <f3d_led.h> // Pull in include file for the local drivers
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <stdio.h>

#define TIMER 20000

int main(void) {
  // If you have your inits set up, this should turn your LCD screen red
     f3d_lcd_init();
     f3d_uart_init();
  
     f3d_gyro_init();
     f3d_user_btn_init();

     setvbuf(stdin, NULL, _IONBF,0);
     setvbuf(stdout, NULL, _IONBF,0);
     setvbuf(stderr, NULL, _IONBF,0);



     delay(100);
     //f3d_lcd_fillScreen(RED);
     //f3d_lcd_drawString(0, 0, "hello", RED, BLACK);

     float gyroVal[3];
     char gyroStr[3];
     int v;

     while(1){
       f3d_gyro_getdata(gyroVal);
       
       f3d_lcd_drawString(0, 0, gyroStr, RED, BLACK);
     }
}
  
#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
  }
  #endif

  /* main.c ends here */
