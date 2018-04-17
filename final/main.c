/*i
 * C335 Final Project
 * Author: Dylan Wright, solo dolo
 * 
 * I will try to replicate the chrome browser minigame for my final project
 * game must incorporate the following:
 * 	*LCD
 * 	*Audio
 * 	*User Input (1 or more device)
 * 	*Nunchuk
 * 	*Accel, Gyro, or Mag
 * 	*SD Card
 */

#include <stm32f30x.h>  // Pull in include files for F30x standard drivers  
//#include <f3d_uart.h>
#include <f3d_lcd_sd.h>
//#include <f3d_i2c.h>
#include <stdio.h> 

//obstacle struct
//the obstacles are just rectangles
//store the top left corner, bottom left corner, and width of the obstacle
typedef struct Obstacle{
  int topLeft;
  int lowLeft;
  int width;
} Obstacle;

//handle any necessary screen initialization 
void screenInit(){
  f3d_lcd_fillScreen(WHITE);

int i = 20;
  //I tried doing this in a for loop and got a bug for some reason
  while(i < 100){
    f3d_lcd_drawPixel(i, 20, BLACK);
    f3d_lcd_drawPixel(i, 60, BLACK);
    f3d_lcd_drawPixel(i, 100, BLACK);
    f3d_lcd_drawPixel(i, 140, BLACK);
    i++;
} //end while
} //end screenInit

/*
// copied over from the lab 7
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
*/

//draw the obstacle (rectangle) passed in
void drawObst(struct Obstacle o){
  int i;
  for (i = o.lowLeft; i < o.topLeft; i++){
    f3d_lcd_drawPixel(20, i, BLACK);
    f3d_lcd_drawPixel((20 + o.width), i, BLACK);
  }

  for (i = 20; i < (20 + o.width); i++){
    f3d_lcd_drawPixel(i, o.lowLeft, BLACK);
    f3d_lcd_drawPixel(i, o.topLeft, BLACK);
  }
} //end drawObst

void updateScreen(struct Obstacle o){

} //end updateScreen

int main(){
  f3d_uart_init();
  delay(10);
  f3d_i2c1_init();
  delay(10);
  //f3d_nunchuk_init();
  delay(10);
  f3d_lcd_init();
  delay(10);

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

/*
  int i = 20;
  while(i < 100){
    f3d_lcd_drawPixel(i, 20, BLACK);
    f3d_lcd_drawPixel(i, 60, BLACK);

    f3d_lcd_drawPixel(i, 100, BLACK);
    f3d_lcd_drawPixel(i, 140, BLACK);
  }
*/

    //screenInit();

    f3d_lcd_fillScreen(BLACK);
    f3d_lcd_fillScreen(WHITE);

    delay(10);

    Obstacle o = { .topLeft = 100, .lowLeft = 70, .width = 40 };

    updateScreen(o);
  //break loop when the player has lost
  while(1){
    
/*
int i = 0;
  //I tried doing this in a for loop and got a bug for some reason
  while(i < 159){
    f3d_lcd_drawPixel(20, i, BLACK);
    f3d_lcd_drawPixel(80, i, RED);
    //f3d_lcd_drawPixel(80, i, BLACK);
    f3d_lcd_drawPixel(130, i, RED);
    i++;
} //end while
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
