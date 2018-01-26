/************************
 *f3d_led.c - contains intializations/functions for the leds
 ************************/

#include <stm32f30x.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>
#include <f3d_led.h>


//intializes the port and pins for the leds on the board
void f3d_led_init(void) {

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);

  //useful macro to ready every LED pin
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
  GPIO_Init(GPIOE, &GPIO_InitStructure);

}
/*Turns on the appropriate led as specified by the parameter.*/
void f3d_led_on(int led) {
  switch (led){
    
    case 8:
     GPIOE->BSRR = GPIO_Pin_8;
     break;
 
    case 9:
     GPIOE->BSRR = GPIO_Pin_9;
     break;

    case 10:
     GPIOE->BSRR = GPIO_Pin_10;
     break;

    case 11:
     GPIOE->BSRR = GPIO_Pin_11;
     break;

    case 12:
     GPIOE->BSRR = GPIO_Pin_12;
     break;

    case 13:
     GPIOE->BSRR = GPIO_Pin_13;
     break;

    case 14:
     GPIOE->BSRR = GPIO_Pin_14;
     break;

    case 15:
     GPIOE->BSRR = GPIO_Pin_15;
     break;
  }
}

/*Turns off the approiate led as specified by the parameter*/ 
void f3d_led_off(int led) {
  switch (led){
    
    case 8:
     GPIOE->BRR = GPIO_Pin_8;
     break;
 
    case 9:
     GPIOE->BRR = GPIO_Pin_9;
     break;

    case 10:
     GPIOE->BRR = GPIO_Pin_10;
     break;

    case 11:
     GPIOE->BRR = GPIO_Pin_11;
     break;

    case 12:
     GPIOE->BRR = GPIO_Pin_12;
     break;

    case 13:
     GPIOE->BRR = GPIO_Pin_13;
     break;

    case 14:
     GPIOE->BRR = GPIO_Pin_14;
     break;

    case 15:
     GPIOE->BRR = GPIO_Pin_15;
     break;
  }
} 

/*Turns on all LEDs*/
void f3d_led_all_on(void) {

  GPIOE->BSRR = GPIO_Pin_8; 
  GPIOE->BSRR = GPIO_Pin_9; 
  GPIOE->BSRR = GPIO_Pin_10;
  GPIOE->BSRR = GPIO_Pin_11;
  GPIOE->BSRR = GPIO_Pin_12;
  GPIOE->BSRR = GPIO_Pin_13;
  GPIOE->BSRR = GPIO_Pin_14;
  GPIOE->BSRR = GPIO_Pin_15; 

} 

/*Turns off all LEDs*/
void f3d_led_all_off(void) {

  GPIOE->BRR = GPIO_Pin_8;
  GPIOE->BRR = GPIO_Pin_9; 
  GPIOE->BRR = GPIO_Pin_10;
  GPIOE->BRR = GPIO_Pin_11;
  GPIOE->BRR = GPIO_Pin_12;
  GPIOE->BRR = GPIO_Pin_13;
  GPIOE->BRR = GPIO_Pin_14;
  GPIOE->BRR = GPIO_Pin_15; 

 
} 

/* led.c ends here */
