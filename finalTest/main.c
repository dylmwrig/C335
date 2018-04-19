/*
 * testing space for my final project
 * so I can work on the actual game part at home
 * and transfer it to the display later
 */

#include <stdio.h>
#include <stdlib.h> //random number generation
#include <stdbool.h>

#define OBSTACLE_COUNT 2
#define PLAYER_X_LOC 5 //Player struct only keeps track of y location
                       //x location can be predefined to always be at a specific x location

//the obstacle is a rectangle
//store the location of the upper and lower edge of the rectangle
//the width
//and the x location of the leftmost edge of the rectangle, as this will always be changing
typedef struct Obstacle{
  int topY;
  int lowY;
  int leftX;
  int rightX;
} Obstacle;

//return whether the player hit an obstacle in this frame
//pass in the player and the left most obstacle
//only pass in the left most obstacle. The player will only ever hit the left most obstacle.
bool hitDetect(struct Obstacle player, struct Obstacle obs){
  int i;
  bool hit = false;

  //check whether any of the player's bounding x values is within range
  //if one is, check y values. If one of those is, a hit has occured so return true.
  bool leftHit = false;

  if ((obs.leftX <= player.leftX) && (player.leftX <= obs.rightX)){
    leftHit = true;
  } //end if

  else if ((obs.leftX <= player.rightX) && (player.rightX <= obs.rightX)){
    leftHit = true;
  } //end else if

  if (leftHit){
    if ((obs.lowY <= player.lowY) && (player.lowY <= obs.lowY)){
      hit = true;
    } //end if

    if ((obs.topY <= player.topY) && (player.topY <= obs.topY)){
      hit = true;
    } //end if
  } //end if

  return hit;
} //end hitDetect

//function to move the player aka update their y coordinates
//draw the screen after this
//moveUp = true if the player is moving upwards
void movePlayer(struct Obstacle player, bool moveUp){
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

int main(){
  int screen[80][65] = {0}; //SCALE THE SCREEN BY 1/2 FOR TESTING
  int i, j;

  //set seed
  time_t t;
  srand((unsigned) time(&t));

  Obstacle p;
  p.topY = 15;

  Obstacle o;
  o.lowY = rand() % 45;
  o.topY = o.lowY + 20; //temporary obstacle height
  o.leftX = 80;
  o.rightX = o.leftX + (rand() % 20) + 15; //define the width of the rectangle to be 30 pixels minimum

  for (i = 15; i < (15 + (o.rightX - o.leftX)); i++){
    for (j = o.lowY ; j < o.topY; j++){
      screen[i][j] = 1;
      //printf("%d %d", i, j);
    } //end for
  } //end for

  for (i = 0; i < 80; i++){
    for (j = 0; j < 65; j++){
      if(screen[i][j] == 1){
        printf("%d", screen[i][j]);
      } //end if

      else{
        printf(" ");
      } //end else


        printf("%d", screen[i][j]);
    } //end for
    //printf("\n");
  } //end for

} //end main
