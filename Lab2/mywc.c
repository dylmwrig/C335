/*
 * wc program
 * take a plain text file as input using <
 * return 3 numbers: the amount of lines, words, then characters
 */

#include <stdio.h>

int main()
{
  int c; //check end of file
  int words = 0, chars = 0, lines = 0;

  while ((c = getchar()) != EOF)
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
} //end main
