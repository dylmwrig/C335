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

#define OBSTACLE_COUNT 2 //amount of obstacles to be generated at any time
#define FAIL_MAX 3 //amount of failures before game over
#define X_BOUND 160
#define Y_BOUND 130

int failCount = 0;
int succCount = 0;

//obstacle struct
//the obstacles are just rectangles
//store the locations of the top edge, bottom edge, left, and right edge
typedef struct Object{
  int topY;
  int lowY;
  int leftX;
  int rightX;
} Object;

struct Object genOb(){
  Object o;
  o.lowY = rand() % 45;
  o.topY = o.lowY + 20; //temporary obstacle height
  o.leftX = 80;
  o.rightX = o.leftX + (rand() % 20) + 15; //define the width of the rectangle to be 30 pixels minimum

  return o;
} //end genOb

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

//return whether the player hit an obstacle in this frame
//pass in the player and the left most obstacle
//only pass in the left most obstacle. The player will only ever hit the left most obstacle.
bool hitDetect(struct Object player, struct Object obs){
  int i;
  bool hit = false;

  printf("%d %d %d %d\n", player.leftX, player.rightX, player.topY, player.lowY);
  printf("%d %d %d %d\n", obs.leftX, obs.rightX, obs.topY, obs.lowY);

  //check whether any of the player's bounding x values is within range
  //if one is, check y values. If one of those is, a hit has occured so return true.
  bool xHit = false;

  if ((obs.leftX <= player.leftX) && (player.leftX <= obs.rightX)){
    xHit = true;
  } //end if

  else if ((obs.leftX <= player.rightX) && (player.rightX <= obs.rightX)){
    xHit = true;
  } //end else if

  //TODO
  //change the signs when transferring this to the main final directory 
  if (xHit){
    if ((obs.lowY <= player.lowY) && (player.lowY >= obs.lowY)){
      hit = true;
    } //end if

    if ((obs.topY <= player.topY) && (player.topY >= obs.topY)){
      hit = true;
    } //end if
  } //end if

  return hit;
} //end hitDetect

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

//function to move the player aka update their y coordinates
//draw the screen after this
//moveUp = true if the player is moving upwards
void movePlayer(struct Object player, bool moveUp){
  //prevent the player from moving downwards if they are already on the floor
  if(!moveUp){
    if (player.lowY == 0){
      return;
    } //end if
    player.topY--;
  } //end if

  else {
    if (player.topY == 65){
      return;
    } //end if
    player.topY++;
  } //end else
} //end movePlayer

//draw the obstacle (rectangle) passed in
//TODO
//this may be inefficient
//you may want to explore other ways to do this that may be more efficient
void drawObst(struct Object o){
  int x, y;
  for (x = o.leftX; x <= o.rightX; x++){
    f3d_lcd_drawPixel(o.lowY, x, BLACK);
    f3d_lcd_drawPixel(o.topY, x, BLACK);
  } //end for

  for (y = o.lowY; y <= o.topY; y++){
    f3d_lcd_drawPixel(y, o.leftX, BLACK);
    f3d_lcd_drawPixel(y, o.rightX, BLACK);
  } //end for
/*  
  for (x = o.leftX; x < o.rightX; x++){
    for (y = o.lowY; y < o.topY; y++){
      if ((y < Y_BOUND) && (x < X_BOUND)
       && (y > 0) && (x > 0)){
        //because I'm using the screen in horizontal mode, reverse the x and y values when drawing
        f3d_lcd_drawPixel(y, x, BLACK); 
      } //end if
    } //end for
  } //end for
*/
} //end drawObst

//pass the obstacles by reference for updating the points
void updateScreen(struct Object obs[OBSTACLE_COUNT]){
  int i;
  for (i = 0; i < OBSTACLE_COUNT; i++){
    drawObst(obs[i]);
    obs[i].topY--;
    obs[i].lowY--;

    //when the object is off screen, generate a new one in its place
    if (obs[i].rightX == 0){
      obs[i] = genOb();
    } //end if
  } //end for
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

    struct Object obs[OBSTACLE_COUNT];

    //random test values
    int i;
    for (i = 0; i < OBSTACLE_COUNT; i++){
      obs[i].topY = 0;
      obs[i].lowY = 0;
      obs[i].leftX = 0;
      obs[i].rightX = 0;
    } //end for

    //using the first obstacle for testing
    Object o = {.topY = 60, .lowY = 10, .leftX = 160, .rightX = 210};
    obs[0] = o;

    Object p = {.topY = 

    drawObst(o);
    //updateScreen(obs);
  while(1){
    o.leftX--;
    o.rightX--;

    //delete the pixels outside of the current range of the box after movement
    if (o.rightX < 160){
      int repX = o.rightX + 1;
      for (i = o.lowY; i <= o.topY; i++){
        f3d_lcd_drawPixel(i, repX, WHITE); 
      } //end for
    } //end if
    drawObst(o); 
  } //end while	
} //end main

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif
