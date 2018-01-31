/**********************************
 *f3d_user_btn.c 
 *contains the init and read functions for the User Button
 *********************************/
#include <stm32f30x.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>

/*
 * Author: Dylan Wright
 * Partner: EJ Seong
 *
 * functions to activate and use the "user button" on the board
 * f3d_user_btn_init basically does the same thing as the corresponding function in f3d_led.c
 * user_btn_read is basically a getter and returns a 0 if the button isn't being pressed, 1 if it is
 *
 * use this to check whether the user wants to pause the LED sequence or not
 */

/*Initialization of the UserButton*/
void f3d_user_btn_init(void){

  //always initialize the clock first
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

}

/*reads the User Button*/
int user_btn_read(void){
 
  return (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0));

}
