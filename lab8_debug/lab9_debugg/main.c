/* main.c --- 
 * 
 * Filename: main.c
 * Description: For the STM board, this file runs basic xor encryption.
 * Author: Max Hollingsworth
 * Maintainer:  Max Hollingsworth
 * Created: Oct 29, 2014
 * Last-Updated: Oct 30, 2014
 *           By: Max Hollingsworth
 *     Update #: 1
 * Keywords: GDB, xor
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
/* Code: */

#include <stm32f30x.h>  // Pull in include files for F30x standard drivers
#include <f3d_uart.h>   //Pull in include file for the local drivers
#include <string.h>  //included for strlen()
#include <stdio.h>    //Pull in include file for the library

void encryptStr(char*, char*, char*);

int main(void) { 
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  //init uart
  f3d_uart_init();
  //reset button
  printf("Reset\n");

  char* xPhrase = "cow";  
  char* xKey = "PIG";
  char xNcrypt[strlen(xPhrase)+1]; 
  char xDecrypt[strlen(xPhrase)+1]; 
  encryptStr(xPhrase, xKey, xNcrypt); //encrypt the phrase
  printf(xNcrypt);
  printf("\n");
  encryptStr(xNcrypt, xKey, xDecrypt); //decrypt the phrase
  printf(xDecrypt);
  printf("\n");
  return 0;

}

void encryptStr(char* phrase, char* key, char* ncrypt) {
  int keylen = strlen(key);
  int phraseLen = strlen(phrase);
  int i;
  for (i = 0; i < 1000; i++) { //for loop should be (i = 0; i < phrase; i++)
    ncrypt[i] = *key ^ *phrase;
    key++;
    phrase++;
    if ( (i+1) % keylen == 0) {
      key = key - keylen;
    }
  }
  ncrypt[i+1] = '\0';
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're herey */
  while (1);
}
#endif

/* main.c ends here */
