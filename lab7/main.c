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
 * Unfortunately, I was unable to finish the compass section of this lab because I spent so much time on the visualization part.
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
#include <f3d_led.h>
#include <stdbool.h>

#define TIMER 20000

//initialize graphs for pitch and roll visualization
void graphInit(){
  f3d_lcd_fillScreen(WHITE);

  //first draw the horizontal lines
  int i = 20;
  //I tried doing this in a for loop and got a bug for some reason
  while(i < 100){
    f3d_lcd_drawPixel(i, 20, BLACK);
    f3d_lcd_drawPixel(i, 60, BLACK);
    f3d_lcd_drawPixel(i, 100, BLACK);
    f3d_lcd_drawPixel(i, 140, BLACK);
    i++;
  } //end while

  //don't really need vertical lines now that I'm thinking about it
  //so I'm just going to label the graphs
  
  f3d_lcd_drawChar(10, 40, '0', BLACK, WHITE);
  f3d_lcd_drawChar(10, 120, '0', BLACK, WHITE);
  f3d_lcd_drawString(60, 10, "PITCH", BLACK, WHITE);
  f3d_lcd_drawString(60, 90, "ROLL", BLACK, WHITE);
} //end graphInit

//move each value in the array one to the left
void swapVals(float pitch[80], float roll[80]){
  int x;
  for (x = 79; x > 0; x--){
    pitch[x] = pitch[x-1];
    roll[x] = roll[x-1];
  } //end for
} //end swapVals

//first, move each index in the array one to the right
//each previously used point will be passed in a two dimensional array
//to move them left, just subtract the x values by 1
//print values from the array in right to left
//
//if they reach the left border, swap indeces on the left end of the array
//
//final step is to
//add the new value to the rightmost part of the graph.
//
//sorry this function is so hacky lol
void updateGraphs(float oldPitch[80], float oldRoll[80], float newPitch, float newRoll){
  int i, pitchY, rollY;

  //unfortunately, this is the most efficient way I could come up with to clear the screen
  //it looks horrible but is fast so its ok I guess.
  for (i = 0; i < 79; i++){
    pitchY = (int)(oldPitch[i] * 10.0);
    if (oldPitch[i] < 0.0){
      pitchY *= -1;
      pitchY += 40;
    } //end if
 
    else{
      pitchY = 40 - pitchY;
    } //end else

    f3d_lcd_drawPixel(i+20, pitchY, WHITE);
  } //end for

  for (i = 0; i < 79; i++){
    rollY = (int)(oldRoll[i] * 10.0);
    if (oldRoll[i] >= 0.0){
      rollY = 120 - rollY;
    } //end if

    else{
      rollY *= -1;
      rollY += 120;
    } //end else

    f3d_lcd_drawPixel(i+20, rollY, WHITE);
  } //end for

  swapVals(oldPitch, oldRoll);
  oldPitch[0] = newPitch;
  oldRoll[0] = newRoll;

  //to scale the values to the graph, the upper and lower bounds will be 2.0 and -2.0
  //there are 40 pixels vertically on each graph so each 0.1 corresponds to one pixel
  for (i = 0; i < 79; i++){
    pitchY = (int)(oldPitch[i] * 10.0);
    if (oldPitch[i] < 0.0){
      pitchY *= -1;
      pitchY += 40;
    } //end if
 
    else{
      pitchY = 40 - pitchY;
    } //end else

    f3d_lcd_drawPixel(i+20, pitchY, BLACK);
  } //end for

  for (i = 0; i < 79; i++){
    rollY = (int)(oldRoll[i] * 10.0);
    if (oldRoll[i] >= 0.0){
      rollY = 120 - rollY;
    } //end if

    else{
      rollY *= -1;
      rollY += 120;
    } //end else

    f3d_lcd_drawPixel(i+20, rollY, BLACK);
  } //end for
} //end updateGraphs

//display north on the compass LEDs on the 
void showNorth(float heading){
  f3d_led_all_off();

  if (heading > 2.25){
    f3d_led_on(0);
  } //end if

  else if (heading > 1.5){
    f3d_led_on(1);
  } //end else if

  else if (heading > .75){
    f3d_led_on(2);
  } //end else if
 
  else if (heading > 0.0){
    f3d_led_on(3);
  } //end else if

  else if (heading > -.75){
    f3d_led_on(4);
  } //end else if

  else if (heading > -1.5){
    f3d_led_on(5);
  } //end else if

  else if (heading > -2.25){
    f3d_led_on(6);
  } //end else if

  else if (heading > -3.0){
    f3d_led_on(7);
  } //end else if
 
  printf("%f\n", heading);
} //end showNorth

int main(void) {
  // Set up your inits before you go ahead  
  f3d_uart_init();
  delay(10);
  f3d_i2c1_init();
  delay(10);
  f3d_mag_init();
  delay(10);
  f3d_led_init();
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
  float pitchVals[80], rollVals[80];
  bool accelMode = true;

  float accelVal[3], magVal[3]; //x, y, and z readings from accelerometer and magnetometer
  while(1){
    if (user_btn_read()){
      accelMode = !accelMode;
      if (accelMode){
        graphInit();
      } //end if

      else{
        f3d_lcd_fillScreen(WHITE);
        f3d_lcd_drawString(40, 10, "COMPASS MODE", BLACK, WHITE);
        f3d_lcd_drawString(10, 20, "SERIALT FOR HEADING", BLACK, WHITE);
      } //end else
    } //end if

    f3d_accel_read(accelVal);
    f3d_mag_read(magVal);
 
    float pitch = atan2(accelVal[0], pow(accelVal[1], 2) + pow(accelVal[2], 2));
    float roll = atan2(accelVal[1], pow(accelVal[0], 2) + pow(accelVal[2], 2));
    float heading = atan2(magVal[1], magVal[0]); 

    if (accelMode){
      updateGraphs(pitchVals, rollVals, pitch, roll);
    } //end if

    else{
      showNorth(heading);
    }
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
