/*
 * wc program
 * take a plain text file as input using <
 * return 3 numbers: the amount of lines, words, then characters
 */

#include <stdio.h>

int main()
{
  int c; //check end of file

  while ((c == getchar()) != EOF)
  {
    if (c == 32) //ASCII for space
    {
      printf("You pressed space\n");
    } //end if
  } //end while
} //end main
