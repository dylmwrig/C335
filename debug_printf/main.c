/*
 * main from lab 5
 * I missed this lab due to the flu so this was copied from EJ
 */

#include <f3d_uart.h>
#include <stdio.h>
#include <stdbool.h>
#include <f3d_gyro.h>
#include <f3d_led.h>
#include <f3d_user_btn.h>

//dely function
void delay(void){
int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

//change led light
int ledDisplay(float num){
 if(num>5 && num <=40){return 0;}
 if(num>0 && num <=5){return 1;}
 if(num>40 && num <=80){return 2;}
 if(num>80 && num <=100){return 3;}
 if(num<0 && num >=-20){return 4;}
 if(num<-20 && num >=-40){return 5;}
 if(num <-40 && num >=-80){return 6;}
 else {return 7;}

}


//gets a character
int getcharTwo(void) {
  if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == (uint16_t)RESET);
  return USART_ReceiveData(USART1);
}

int main(void){
 
 //initialization
  f3d_led_init();
  f3d_user_btn_init();
  f3d_gyro_init();
  f3d_uart_init();
 
  setvbuf(stdin, NULL, _IONBF,0);
  setvbuf(stdout, NULL, _IONBF,0);
  setvbuf(stderr, NULL, _IONBF,0);

  bool printTrue = false;

  while(1){
    f3d_led_on(1);

    if (printTrue){
      printf("Big Old Print Boy\n");
    }
    
    delay();
    f3d_led_off(1);
    delay(); 

    if (user_btn_read() == 1){
      printTrue = !printTrue;
    }
  }
} 

void assert_failed(uint8_t* file, uint32_t line){
/* Infinite loop */
/* Use GDB to find out why we're here */
 while(1);
}
