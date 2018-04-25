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
#include <f3d_uart.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_i2c2.h>
#include <f3d_nunchuk.h>
#include <f3d_rtc.h>
#include <ff.h>
#include <diskio.h>
#include <stdio.h> 
#include <stdbool.h>
#include <stdlib.h> //RNG
#include <ctype.h> //isdigit()
#define OBSTACLE_COUNT 2 //amount of obstacles to be generated at any time
#define FAIL_MAX 2 //amount of failures before game over
#define X_BOUND 160
#define Y_BOUND 130

//obstacle struct
//store the locations of the top edge, bottom edge, left, and right edge
typedef struct Object{
  int topY;
  int lowY;
  int leftX;
  int rightX;
} Object;

struct Object genOb(){
  Object o;
  o.lowY = rand() % 65;
  o.topY = o.lowY + 40; //arbitrary size for the obstacle
  o.leftX = X_BOUND;
  o.rightX = o.leftX + (rand() % 40) + 15; //define the width of the rectangle to be 30 pixels minimum

  return o;
} //end genOb

void die (FRESULT rc) {
  printf("Failed with rc=%u.\n", rc);
  while(1);
}

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

  if ((obs.leftX <= player.rightX) && (player.rightX <= obs.rightX)){
    xHit = true;
  } //end if

  if (xHit){
    if ((obs.lowY <= player.lowY) && (player.lowY <= obs.topY)){
      hit = true;
    } //end if

    if ((obs.lowY <= player.topY) && (player.topY <= obs.topY)){
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
void movePlayer(struct Object * p, bool moveUp){
  int i;

  //prevent the player from moving downwards if they are already on the floor
  if(!moveUp){
    if (p->lowY == 0){
      return;
    } //end if

    for (i = p->leftX; i <= p->rightX; i++){
      f3d_lcd_drawPixel(p->lowY, i, WHITE);
      f3d_lcd_drawPixel(p->topY, i, WHITE);
    } //end for

    p->topY--;
    p->lowY--;
  } //end if

  else {
    if (p->topY == Y_BOUND){
      return;
    } //end if

    for (i = p->leftX; i <= p->rightX; i++){
      f3d_lcd_drawPixel(p->lowY, i, WHITE);
      f3d_lcd_drawPixel(p->topY, i, WHITE);
    } //end for

    p->topY++;
    p->lowY++;
  } //end else
} //end movePlayer

//press c to jump
//call movePlayer up a number of times, call it downwards
void jump(struct Object * p){
  int i;
  for (i = 0; i < 30; i++){
    movePlayer(p, true);
    drawObst(*p);
  } //end for

  for (i = 0; i < 30; i++){
    movePlayer(p, false);
    drawObst(*p);
  } //end for
} //end jump

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
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  f3d_uart_init();
  delay(10);

  /*
  f3d_i2c1_init();
  delay(10);
  f3d_i2c2_init();
  delay(10);
  f3d_nunchuk_init();
  delay(10);
  */
  f3d_rtc_init();
  delay(10);
  f3d_lcd_init();
  delay(10);

  //copied from lab 9
  //might not need all of these
  FATFS Fatfs;
  FIL Fil;
  BYTE Buff[128]; 
 
  FRESULT rc;
  DIR dir;
  FILINFO fno;
  UINT bw, br;
  unsigned int retval;

  f_mount(0, &Fatfs); //register volume work area (never fails)
  delay(10);

/*
  printf("\nOpen an existing file (message.txt).\n");
    rc = f_open(&Fil, "MESSAGE.TXT", FA_READ);
  if (rc) die(rc);
 
  printf("\nType the file content.\n");
  for (;;) {
    rc = f_read(&Fil, Buff, sizeof Buff, &br);	
    if (rc || !br) break;			
    for (i = 0; i < br; i++)		       
      putchar(Buff[i]);
  }
  if (rc) die(rc);

  printf("\nClose the file.\n");
  rc = f_close(&Fil);
  if (rc) die(rc);
 
  printf("\nCreate a new file (hello.txt).\n");
  rc = f_open(&Fil, "HELLO.TXT", FA_WRITE | FA_CREATE_ALWAYS);
  if (rc) die(rc);
  
  printf("\nWrite a text data. (Hello world!)\n");
  rc = f_write(&Fil, "Hello world!\r\n", 14, &bw);
  if (rc) die(rc);
  printf("%u bytes written.\n", bw);
  
  printf("\nClose the file.\n");
  rc = f_close(&Fil);
  if (rc) die(rc);
  
  printf("\nOpen root directory.\n");
  rc = f_opendir(&dir, "");
  if (rc) die(rc);
  
  printf("\nDirectory listing...\n");
  for (;;) {
    rc = f_readdir(&dir, &fno);		
    if (rc || !fno.fname[0]) break;	
    if (fno.fattrib & AM_DIR)
      printf("   <dir>  %s\n", fno.fname);
    else
      printf("%8lu  %s\n", fno.fsize, fno.fname);
  }
  if (rc) die(rc);
  
  printf("\nTest completed.\n");

  rc = disk_ioctl(0,GET_SECTOR_COUNT,&retval);
  printf("%d %d\n",rc,retval);
*/

/*
  //screenInit();
  f3d_lcd_fillScreen(BLACK);
  f3d_lcd_fillScreen(WHITE);
  delay(10);
  struct Object obs[OBSTACLE_COUNT];
  nunchuk_t nun;
  nunchuk_t * nun_point = &nun;
  //random test values
  int i;
  for (i = 0; i < OBSTACLE_COUNT; i++){
    obs[i].topY = 0;
    obs[i].lowY = 0;
    obs[i].leftX = 0;
    obs[i].rightX = 0;
  } //end for
  obs[0] = genOb();  
  Object p = {.topY = 40, .lowY = 0, .leftX = 5, .rightX = 10};
  Object o = obs[0]; //used for testing
  drawObst(p); 
  drawObst(o);
  
  //jumping keeps track of if the player is currently in a jump animation
  //playerUp keeps track of the trajectory of the jump: moving up or down
  //jumpFrame keeps track of which frame of the jump animation we are on
  bool jumping = false, playerUp = false;
  int jumpFrame = 0;
 
  int score = 0, failures = 0;
  printf("Before while loop\n");
  //updateScreen(obs);
  while(1){
    f3d_nunchuk_read(nun_point);
    if (nun_point->jy == 255){
      //only jump if a jump isn't currently happening
      if (!jumping){
        jumping = true;
        playerUp = true;
        jumpFrame = 0;
      } //end if
    } //end if
    if (jumping){
      if (playerUp){
        //start a downwards trajectory if the player as at the top of the arc
        if (jumpFrame == 30){
          playerUp = false;
        } //end if 
        else{
          movePlayer(&p, true);
          drawObst(p);
        } //end else
      } //end if
      //otherwise, the player is falling
      else{
        if (jumpFrame == 0){
          jumping = false;
        } //end if
        else{
          movePlayer(&p, false);
          drawObst(p);
        } //end else
      } //end else 
    } //end if
    if (o.rightX < 0){
      score++;
      o = genOb();      
    } //end if
    //delete the pixels outside of the current range of the box after movement
    for (i = o.lowY; i <= o.topY; i++){
      if (o.rightX <= X_BOUND){
        f3d_lcd_drawPixel(i, o.rightX, WHITE); 
      } //end if
      if (o.leftX >= 0){
        f3d_lcd_drawPixel(i, o.leftX, WHITE);
      } //end if
    } //end for
    o.leftX--;
    o.rightX--;
    drawObst(o);
    if (hitDetect(p, o)){
      failures++;
      //copied from drawObst
      //TODO
      //see if you can make color a parameter later on
      int x, y;
      for (x = o.leftX; x <= o.rightX; x++){
        f3d_lcd_drawPixel(o.lowY, x, WHITE);
        f3d_lcd_drawPixel(o.topY, x, WHITE);
      } //end for
 
      for (y = o.lowY; y <= o.topY; y++){
        f3d_lcd_drawPixel(y, o.leftX, WHITE);
        f3d_lcd_drawPixel(y, o.rightX, WHITE);
      } //end for
      o = genOb();
      if (failures == FAIL_MAX){
        break;
      } //end if
    } //end if
    if (jumping){
      if (playerUp){
        jumpFrame++;
      } //end if
      else{
        jumpFrame--;
      } //end else
    } //end if
  } //end while
  printf("Final Score: %d", score);
*/

/*
  printf("\nCreate a new file (hello.txt).\n");
  rc = f_open(&Fil, "HELLO.TXT", FA_WRITE | FA_CREATE_ALWAYS);
  if (rc) die(rc);
  
  printf("\nWrite a text data. (Hello world!)\n");
  rc = f_write(&Fil, "Your score: xd\r\n", 14, &bw);
  if (rc) die(rc);
  printf("%u bytes written.\n", bw);
  
  printf("\nClose the file.\n");
  rc = f_close(&Fil);
  if (rc) die(rc);
*/
/*
  printf("\nOpen an existing file (message.txt).\n");
    rc = f_open(&Fil, "MESSAGE.TXT", FA_READ);
  if (rc) die(rc);
 
  printf("\nType the file content.\n");
  for (;;) {
    rc = f_read(&Fil, Buff, sizeof Buff, &br);	
    if (rc || !br) break;			
    for (i = 0; i < br; i++)		       
      putchar(Buff[i]);
  }
  if (rc) die(rc);
  
  printf("\nClose the file.\n");
  rc = f_close(&Fil);
  if (rc) die(rc);
  
  printf("\nCreate a new file (hello.txt).\n");
  rc = f_open(&Fil, "HELLO.TXT", FA_WRITE | FA_CREATE_ALWAYS);
  if (rc) die(rc);
  
  printf("\nWrite a text data. (Hello world!)\n");
  rc = f_write(&Fil, "Hello world!\r\n", 14, &bw);
  if (rc) die(rc);
  printf("%u bytes written.\n", bw);
  
  printf("\nClose the file.\n");
  rc = f_close(&Fil);
  if (rc) die(rc);
*/
/*
  printf("\nOpen root directory.\n");
  rc = f_opendir(&dir, "");
  if (rc) die(rc);
  
  printf("\nDirectory listing...\n");
  for (;;) {
    rc = f_readdir(&dir, &fno);	9	
    if (rc || !fno.fname[0]) break;	
    if (fno.fattrib & AM_DIR)
      printf("   <dir>  %s\n", fno.fname);
    else
      printf("%8lu  %s\n", fno.fsize, fno.fname);
  }
  if (rc) die(rc);
  
  printf("\nTest completed.\n");

  rc = disk_ioctl(0,GET_SECTOR_COUNT,&retval);
  printf("%d %d\n",rc,retval);
*/

  char strBuf[100];

  rc = f_open(&Fil, "SCORES.TXT", FA_READ | FA_OPEN_ALWAYS);
  if (rc) die(rc);

  int prevScores[3] = {-1, -1, -1};
  int scoreInd = 0; 
  int i, score = 15;
 
  printf("After scores open\n");
 
  //read in each digit found in the high scores file
  //nobody will score more than two digits
  //so I can just hard code this around 1 and 2 digit numbers
  //store each score so we can compare the current player's score and store it if necessary
  int resNum = -1;
  for (;;) {
    rc = f_read(&Fil, strBuf, sizeof(strBuf), &br);
    if (rc || !br) break;
    for (i = 0; i < br; i++){
      //if there is a newline, clear the number var
      //to allow for the one on the next line
      if (strBuf[i] == 10){
        resNum = -1;
      } //end if

      if (isdigit(strBuf[i])){
        if (resNum == -1){
          resNum = atoi(&strBuf[i]);
          prevScores[scoreInd] = resNum;
          scoreInd++;
        } //end if
      } //end if 
    } //end for
  } //end for

  if (rc) die(rc);
  rc = f_close(&Fil);
  if (rc) die(rc);

  if (scoreInd > 2){
    scoreInd--;
  } 

  printf("Before logic\n");

  char bufDest[60];
  char buf2[20];
  //when you find the first high score that is less than the player's current score
  //shift every element of the high score array to the right and fill in the player's score
  int bufSize = 0;
  int baseSize = 13; //"High score: %d\n" is 13 digits long without the digit modifier
  for (i = 0; i < 3; i++){
    if (score > prevScores[i]){
      int j;
      for (j = 2; j > i; j--){
        prevScores[j] = prevScores[j - 1];
      } //end for
      prevScores[i] = score;
      i = 4;
    } //end if
  } //end for

  for (i = 0; i < 3; i++){
  printf("i then value: %d %d\n", i, prevScores[i]);
    if (prevScores[i] >= 0){
      int digitSize;

      if (prevScores[i] < 10){
        digitSize = 1; //size modifier based on if the number is 2 or 1 digit long
      } //end if

      else {
        digitSize = 2;
      } //end else

      bufSize += baseSize;
      bufSize += digitSize;

      if (i == 0){
        sprintf(bufDest, "High score: %d\n", prevScores[i]);
      }

      else{
        sprintf(buf2, "High score: %d\n", prevScores[i]);
        strcat(bufDest, buf2);
      } //end if
    } //end if
  } //end for

  rc = f_open(&Fil, "SCORES.TXT", FA_WRITE | FA_READ | FA_CREATE_ALWAYS);
  if (rc) die(rc);
  
  rc = f_write(&Fil, bufDest, bufSize, &bw);
  if (rc) die(rc);
  printf("%u bytes written.\n", bw);
  rc = f_close(&Fil);
  if (rc) die(rc);

  printf("At the end\n");
} //end main

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif
