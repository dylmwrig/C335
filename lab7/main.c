/* main.c ---
*
* Filename: main.c
* Description:
* * Author:
* * Maintainer:
* * Created: Thu Jan 10 11:23:43 2013
* * Code: */

/*
 * Author: Dylan Wright
 * Partner: EJ Seong
 * EJ and I only really worked on the initialization driver stuff together as that's all we could get done in the first lab session. Afterwards, we completed the lab solo.
 */

#include <stm32f30x.h> // Pull in include files for F30x standard drivers
#include <f3d_uart.h>
#include <f3d_user_btn.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <stdio.h>
#include <math.h>

#define TIMER 20000

//initialize graphs for pitch and roll visualization
void graphInit(){
  f3d_lcd_fillScreen(WHITE);

  //first draw the horizontal lines
  int i = 20;
  //I tried doing this in a for loop and got a bug for some reason
  while(i < 100){
    f3d_lcd_drawPixel(i, 20, BLACK);
    f3d_lcd_drawPixel(i, 70, BLACK);
    f3d_lcd_drawPixel(i, 100, BLACK);
    f3d_lcd_drawPixel(i, 150, BLACK);
    i++;
  } //end while

  //don't really need vertical lines now that I'm thinking about it
  //so I'm just going to label the graphs
  
  f3d_lcd_drawChar(10, 40, '0', BLACK, WHITE);
  f3d_lcd_drawChar(10, 40, '0', BLACK, WHITE);
} //end graphInit

int main(void) {
  // Set up your inits before you go ahead  
  f3d_uart_init();
  delay(10);
  f3d_i2c1_init();
  delay(10);
  f3d_mag_init();
  delay(10);
  f3d_lcd_init();
  delay(10);
  f3d_user_btn_init();
  delay(10);
  f3d_accel_init();
  delay(10);

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  graphInit();

  float accelVal[3], magVal[3]; //x, y, and z readings from accelerometer and magnetometer
  while(1){
    /*
    f3d_accel_read(accelVal);
    f3d_mag_read(magVal);
 
    float pitch = atan2(accelVal[0], pow(accelVal[1], 2) + pow(accelVal[2], 2));
    float roll = atan2(accelVal[1], pow(accelVal[0], 2) + pow(accelVal[2], 2));
    float heading = atan2(magVal[1], magVal[0]);
*/
    //printf("Pitch and roll: %f %f\n", pitch, roll);
    //printf("Heading: %f\n", heading);

    //I would like to visualize pitch and roll in a way similar to heart rate ECG monitors
    //where it sort of shows the "history" of the pitch and roll values 
     
 
/*
 *  simple way to draw a line using lcd_drawPixel
    int x, y;
    for (x = 50; x < 150; x++){
      y = x;
      f3d_lcd_drawPixel(x, y, BLACK);
    }
*/
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
