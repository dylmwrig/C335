/* main.c --- 
 * 
 * Filename: main.c
 * Description: 
 * Author: 
 * Maintainer: 
 * Created: Thu Jan 10 11:23:43 2013
 * Last-Updated: 
 *           By: 
 *     Update #: 0
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change log:
 * 
 * 
 */

/*
 * Lab 4
 * Author: Dylan Wright
 * Partners: EJ Seong, Daniel
 *
 * I commented out the original getchar, printchar, and printf stuff
 * right now my main just executes the wordcount program using UART
 */
/* Code: */

#include <f3d_uart.h>
#include <stdio.h>
#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>     // Pull in include file for the local drivers

// Simple looping delay function
void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

int main(void) {
  f3d_uart_init();

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  while(1){
    //was told to just comment out the original stuff from this assignment
    putchar('a');
    putchar(getchar());
    printf("Hello world");
 
    //the following is copied from wc.c in lab 2
    int c; //check end of file
    int words = 0, chars = 0, lines = 0;
  
    while ((c = getchar()) != 0x1b)
    {
      if (c == ' ' || c == '\t' || c == '\r' || c == '\f' || c == '\v') //ASCII for space
      {
        words++;
      } //end if
  
      else if (c == '\n')
      {
        words++;
        lines++;
      } //end else if
  
      chars++;
    } //end while
  
    printf("%d %d %d", lines, words, chars);
  } //end while
} //end main

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */
