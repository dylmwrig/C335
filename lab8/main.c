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
#include <f3d_i2c2.h>
#include <f3d_accel.h>
#include <f3d_nunchuk.h>
#include <f3d_mag.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <f3d_led.h>
#include <f3d_gyro.h>

#define TIMER 20000

//helper functions for the gyro display stuff
//display block
void displayBlock(uint8_t x1, uint8_t y1,uint8_t x2,uint8_t y2,uint16_t color){
  uint8_t h = y2-y1+1;
  uint8_t w = x2-x1+1;
  uint16_t widthBar[w];
  int i;
  int j;
    for(i=0; i <w; i++) widthBar[i]=color;
      f3d_lcd_setAddrWindow (x1, y1, x2, y2, MADCTLGRAPHICS);
   for (j=y1; j<y2; j++){
       f3d_lcd_pushColor(widthBar,w);
         }

         }

         void moveBlock(uint8_t x, uint8_t y, uint8_t x2, uint8_t y2, float num){
           //positive gyro value
            if(num>5 && num <=20){
                 displayBlock(x,y-num,x2, y, BLACK);
                      delay(200);
                           displayBlock(x,y-num,x2, y, RED);
                              }
            if(num>0 && num <=5){
               displayBlock(x,y-num,x2, y, BLACK);
               delay(200);
               displayBlock(x,y-num,x2, y, RED);
            }
            if(num>20){
               displayBlock(x,40,x2, y, BLACK);
               delay(200);
               displayBlock(x,40,x2, y, RED);
            }
            //negative gyro value
             if(num<0 && num >=-5){
                displayBlock(x,y2,x2, y2+num, BLACK);
                   delay(200);
                      displayBlock(x,y2,x2, y2+num, RED);
                       }
                        if(num<-5 && num >=-20){
                           displayBlock(x,y2,x2, y2+num, BLACK);
                           delay(200);
                              displayBlock(x,y2,x2, y2+num, RED);
                               }
                                if(num <-20 ){
                                   displayBlock(x,y2,x2, y2+40, BLACK);
                                   delay(200);
                                   displayBlock(x,y2,x2, y2+40, RED);
                                } }


//copied from lab 6
void displayGyro(){
  f3d_lcd_fillScreen(RED);

  float val[3];
  float gyroVal=0;
  int count =0;

  unsigned char c[3] = {'x', 'y', 'z'};
  char number[30];
  int v;
  bool stayGyro = true;

  while(stayGyro){
    f3d_gyro_getdata(val);
                            
    gyroVal=val[count%3];
    //display gyro axis
    f3d_lcd_drawChar(40,20, c[count%3], BLACK, RED);
             
    //display gyro value  
    v=snprintf(number, sizeof(number),"%.2f", val[count%3]);
    displayBlock(76,20,91,28,RED);
    f3d_lcd_drawString(46,20, number, BLACK, RED);

    //display block   
    displayBlock(15,80,45,90, BLACK); //block x
    displayBlock(50,80,85,90,BLACK); //block y
    displayBlock(90,80,120,90,BLACK); //block z

    //move block
    if(count%3==0){moveBlock(15,80,45,90,val[0]);} // move x
    if(count%3==1){moveBlock(50,80,85,90,val[1]);} //move y
    if(count%3==2){moveBlock(90,80,120,90,val[2]);}//move z
                   
    //change x,y,z
    if(user_btn_read()){
      stayGyro = false;
      break;
/*    this is what should be happening with user button
 *    right now I'm going to have user button change between displays because I can't get nunchuk to work
      count++;
       while(user_btn_read());
*/
    } //end if
  } //end while
} //end gyroDisplay

//lab7 stuff
//
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

  f3d_lcd_drawChar(10, 40, '0', BLACK, WHITE);
  f3d_lcd_drawChar(10, 120, '0', BLACK, WHITE);
  f3d_lcd_drawString(60, 10, "PITCH", BLACK, WHITE);
  f3d_lcd_drawString(60, 90, "ROLL", BLACK, WHITE);
} //end graphInit

void swapVals(float pitch[80], float roll[80]){
  int x;
  for (x = 79; x > 0; x--){
    pitch[x] = pitch[x-1];
    roll[x] = roll[x-1];
  } //end for
} //end swapVals

void updateGraphs(float oldPitch[80], float oldRoll[80], float newPitch, float newRoll){
  int i, pitchY, rollY;

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

void displayCompass(){
  f3d_lcd_fillScreen(WHITE);
  f3d_lcd_drawString(40, 10, "COMPASS MODE", BLACK, WHITE);
  f3d_lcd_drawString(10, 20, "SERIALT FOR HEADING", BLACK, WHITE);
  bool keepCompass = true;
  float pitchVals[80], rollVals[80];
  bool keepTilt = true;

  float accelVal[3], magVal[3]; //x, y, and z readings from accelerometer and magnetometer
  
  while (keepCompass){
    if (user_btn_read()){
      keepCompass = false;
      break;
    } //end if

    float pitch = atan2(accelVal[0], pow(accelVal[1], 2) + pow(accelVal[2], 2));
    float roll = atan2(accelVal[1], pow(accelVal[0], 2) + pow(accelVal[2], 2));
    float heading = atan2(magVal[1], magVal[0]); 

    showNorth(heading);
  } //end while
} //end displayCompass

void displayTilt(){
  graphInit();
  float pitchVals[80], rollVals[80];
  bool keepTilt = true;

  float accelVal[3], magVal[3]; //x, y, and z readings from accelerometer and magnetometer
  while(keepTilt){
    if (user_btn_read()){
      keepTilt = false;
      break;
    } //end if

    f3d_accel_read(accelVal);
    f3d_mag_read(magVal);
 
    float pitch = atan2(accelVal[0], pow(accelVal[1], 2) + pow(accelVal[2], 2));
    float roll = atan2(accelVal[1], pow(accelVal[0], 2) + pow(accelVal[2], 2));
    float heading = atan2(magVal[1], magVal[0]); 

    updateGraphs(pitchVals, rollVals, pitch, roll);
  } //end while
} //end displayTilt

int displayNunchuk(){

  return 0;
} //end displayNunchuk

int main(void) {
  f3d_uart_init(); 
  delay(10);
  f3d_i2c1_init();
  delay(10);
  f3d_i2c2_init();
  delay(10);
  f3d_gyro_init();
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
  f3d_nunchuk_init();
  delay(10);  

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  printf("Ready!");

  int next = 0;
  //each display function returns an int representing which display function to move to
  //gyro display = 0
  //board tilt = 1
  //compass = 2
  //nunchuk = 3
  while(1){
    nunchuk_t n, n2;
    f3d_nunchuk_read(&n);
    f3d_nunchuk_read2(&n2);
    delay(20);
    printf("%d %d\n", n.jx, n.jy); 
/*
    if (n.c == 1){
      next++;
      f3d_lcd_fillScreen(BLACK);
    } //end if

    else if (n.z == 1){
      next--;
      f3d_lcd_fillScreen(BLACK);
    } //end else if
  
    if(n.jx>200){
       next++;
       f3d_lcd_fillScreen(BLACK);
     }
     else if (n.jx<30){
       next--;
       f3d_lcd_fillScreen(BLACK);
     }

    if (next > 3){
      next = 0;
    } //end if
 
    if (next < 0){
      next = 3;      
    } //end if

    if (next == 0){
      displayGyro();
    } //end if

    else if (next == 1){
      displayTilt();
    } //end else if
 
    else if (next == 2){
      displayCompass();
    } //end else if  
 
    else if (next == 3){
      displayNunchuk();
    } //end else if

    printf("%d", next);
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
