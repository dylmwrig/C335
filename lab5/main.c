#include <f3d_uart.h>
#include <stdio.h>
#include <f3d_gyro.h>
#include <f3d_led.h>
#include <f3d_user_btn.h>

//main.c lab 5
//Author: Dylan Wright

void delay(void){
int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

//change led light based on gyro data
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
//almost identical to the function in f3d_uart
//with the only difference being that this function uses an if rather than a while statement
int getcharGyro(void) {
  if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == (uint16_t)RESET);
  return USART_ReceiveData(USART1);
}

int main(void){
 
 //initialization
  f3d_uart_init();
  f3d_led_init();
  f3d_user_btn_init();
  f3d_gyro_init();
 
  setvbuf(stdin, NULL, _IONBF,0);
  setvbuf(stdout, NULL, _IONBF,0);
  setvbuf(stderr, NULL, _IONBF,0);

  //assign char list
  char axis[3]={'X', 'Y', 'Z'};
  float val[3];
 
  int c, count=0, ledNum=0;
  float gyroVal=0;
 
  while(1){
 
    //get gyro data     
    f3d_gyro_getdata(val);
  
    gyroVal=val[count%3];
    ledNum=ledDisplay(gyroVal);
    f3d_led_on(ledNum);
 
    delay();
    f3d_led_off(ledNum);
  
    //similar to what we were doing in lab 4
    //change the axis depending on what the user inputs 
    c = getcharGyro();
    if(c=='x'){
      putchar('x'); 
      printf("\n"); 
      count=0;
    }

    if(c=='y'){
      putchar('y'); 
      printf("\n");
      count=1;
    }

    if(c=='z'){
      putchar('z'); 
      printf("\n");
      count=2;
    }

   
    //user input
    while(user_btn_read()){
     count++;
    }
   
    printf("current: %c  %f\n", axis[count%3], val[count%3]);
  }
  
  return 0;
}

void assert_failed(uint8_t* file, uint32_t line){
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}

