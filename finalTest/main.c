/*
 * testing space for my final project
 * so I can work on the actual game part at home
 * and transfer it to the display later
 */

#include <stdio.h>
#include <stdlib.h> //random number generation
#include <stdbool.h>
#include <unistd.h> //to use c sleep() function while testing

#define OBSTACLE_COUNT 2
#define PLAYER_X_LOC 5 //Player struct only keeps track of y location
                       //x location can be predefined to always be at a specific x location

//globals
int SCORE = 0;

//the obstacle is a rectangle
//store the location of the upper and lower edge of the rectangle
//the width
//and the x location of the leftmost edge of the rectangle, as this will always be changing
typedef struct Object{
  int topY;
  int lowY;
  int leftX;
  int rightX;
} Object;

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
    if ((obs.lowY <= player.lowY) && (player.lowY <= obs.topY)){
      hit = true;
    } //end if

    if ((obs.lowY <= player.topY) && (player.topY <= obs.topY)){
      hit = true;
    } //end if
  } //end if

  return hit;
} //end hitDetect

//need to edit this when transferring it to the final directory
//(I guess this is true for everything I do here
void printScreen(int screen[80][65]){
  int x, y;

  for (y = 0; y < 65; y++){
    for (x = 0; x < 80; x++){
      if(screen[x][y] != 0){
        printf("%d", screen[x][y]);
      } //end if

      else{
        printf(" ");
      } //end else
    } //end for
    printf("\n");
  } //end for
} //end printScreen

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

//update the screen with new location values
//val represents the number to replace with ie 1 for obstacles, 2 for player
//xReplace is the x column to replace
//xReplace will be -1 if there is no column to replace
void updateScreen(int screen[80][65], Object o, int val){
  int i, j;

  for (i = o.leftX; i < o.rightX; i++){
    for (j = o.lowY ; j < o.topY; j++){
      //obstacles will always start off screen
      if ((i < 80) && (j < 65)){
        screen[i][j] = val;
      } //end if
    } //end for
  } //end for
} //end updateScreen

struct Object genOb(){
  Object o;
  o.lowY = rand() % 45;
  o.topY = o.lowY + 20; //temporary obstacle height
  o.leftX = 80;
  o.rightX = o.leftX + (rand() % 20) + 15; //define the width of the rectangle to be 30 pixels minimum

  return o;
} //end genOb

int main(){
  int screen[80][65] = {0}; //SCALE THE SCREEN BY 1/2 FOR TESTING
  int i, j;

  FILE * scores;
  scores = fopen("scores.txt", "w+");

  //set seed
  time_t t;
  srand((unsigned) time(&t));

  Object p;
  p.topY = 20;
  p.lowY = 0;
  p.leftX = 5;
  p.rightX = 10; 

  Object o = genOb();

  //initialize to one for testing
  Object obs[1] = {o};

  bool gg = true;
  while(gg){

    for (i = 0; i < 1; i++){
      obs[i].leftX--;
      obs[i].rightX--;
      int repX = obs[i].rightX + 1;
      for (j = obs[i].lowY; j < obs[i].topY; j++){
        screen[repX][j] = 0;
      } //end for
      
      updateScreen(screen, obs[i], 1);
      printScreen(screen);

      if (hitDetect(p, obs[i])){
        gg = false;
      } //end if

      if (obs[i].rightX < 0){
        obs[i] = genOb();
        SCORE++;
      } //end if
    } //end for

    updateScreen(screen, p, 2);

    usleep(90000);
  } //end while

  

  fprintf(scores, "Your score: %d\n", SCORE);
  fclose(scores);
} //end main
