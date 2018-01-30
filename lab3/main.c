#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>     // Pull in include file for the local drivers
#include <f3d_user_btn.h>
#include <stdbool.h>

// Simple looping delay function
void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

int main(void) {

  f3d_led_init(); //ready every LED before attempting anything
  f3d_user_btn_init();

  bool paused = false; //pause the cycle while the user is holding the button
  int curLED = 0; //keeps track of the current LED to light

  while(1){

    //begin the loop by checking whether the cycle is paused or not
    if(user_btn_read() == 0){
      paused = false;
    }
   
    else{
      paused = true;
    }

    if(!paused){
     
      //we are at the end of the cycle, so turn everything on
      if(curLED == 8){
        f3d_led_all_on();
        curLED++;     
      }

      //the only time that curLED will be 9 is if all leds are on
      else if(curLED == 9){
        f3d_led_all_off();
        curLED = 0;
        f3d_led_on(curLED);
      }

      //otherwise just light each LED sequentially
      else{
        f3d_led_off(curLED); 
        curLED++;
        f3d_led_on(curLED);
      }

      delay();
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

/* main.c ends here */
