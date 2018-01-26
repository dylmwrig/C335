/**********************************
 *f3d_user_btn.c 
 *contains the init and read functions for the User Button
 *********************************/
#include <stm32f30x.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>


/*Initialization of the UserButton*/
void f3d_user_btn_init(void){

  CC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  GPIO_Init(GPIOA, &GPIO_InitStructure);

}

/*reads the User Button*/
int user_btn_read(void){
  
}
