#include <stm32f30x.h> // Pull in include files for F30x standard drivers
#include <f3d_led.h> // Pull in include file for the local drivers
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <stdio.h>

#define TIMER 20000

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
                                }

                                       }
                                                                       
   int main(void) {
     // If you have your inits set up, this should turn your LCD screen red
     f3d_lcd_init();
     delay(100);
     f3d_lcd_fillScreen(RED);

     f3d_gyro_init();
     f3d_uart_init();
     f3d_user_btn_init();
            
     setvbuf(stdin, NULL, _IONBF,0);
     setvbuf(stdout, NULL, _IONBF,0);
     setvbuf(stderr, NULL, _IONBF,0);

     float val[3];
     float gyroVal=0;
     int count =0;

     unsigned char c[3] = {'x', 'y', 'z'};
     char number[30];
     int v;
     while(1){
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
                              count++;
                                    while(user_btn_read());
                                      }
                                                      }
                                                                     }

  #ifdef USE_FULL_ASSERT
  void assert_failed(uint8_t* file, uint32_t line) {
                                                                     /* Infinite loop */
                                                                     /* Use GDB to find out why we're here */
                                                                       while (1);
                                                                       }                                                                                                                                          
#endif     
