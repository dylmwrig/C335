/************************** 
 *f3d_uart.c 
 *contains the initialization basic i/o functions for UART
****************************/ 

/*
 * Author: Dylan Wright
 * Partners: Daniel, EJ 
 *
 * Initialize UART, and then include functions for writing and receiving characters
 * putstring simply calls putchar repeatedly
 * ALWAYS initialize every clock, this bug was an absolute headache
 */

#include <stm32f30x.h>
#include <f3d_uart.h>
//the initialization function to call
void f3d_uart_init(void) {

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  USART_InitTypeDef USART_InitStructure;
  USART_StructInit(&USART_InitStructure);
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART1 ,&USART_InitStructure);
  USART_Cmd(USART1 , ENABLE);

  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC,&GPIO_InitStructure);

  GPIO_PinAFConfig(GPIOC,4,GPIO_AF_7);
  GPIO_PinAFConfig(GPIOC,5,GPIO_AF_7);

 }

//sends a character after checking that the transmitter is not busy
int putchar(int c) {

  while (USART_GetFlagStatus(USART1,USART_FLAG_TXE) == (uint16_t)RESET);
  USART_SendData(USART1, c);
  return 0; //for now
  
} 
//gets a character
int getchar(void) {

  while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == (uint16_t)RESET);
  int c = USART_ReceiveData(USART1);
  return c;

}
//sends a string
void putstring(char *s) {
  while (*s != '\0'){
    putchar(*s);
    s++;
  }
}



/* f3d_uart.c ends here */
