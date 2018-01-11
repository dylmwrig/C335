#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
  char fileName[50];
  char origName[50];
  char fileModStr[10];
  int fileMod = 1;
  origName[0] = 'h';
  origName[1] = 'i';
  FILE * fptr;
    
  while(1)
  {
    strcpy(fileName, origName);
    printf("Hello World!\n");
    sprintf(fileModStr, "%d", fileMod);
    strcat(fileName, fileModStr);
    strcat(fileName, ".c");
    fptr = fopen(fileName, "w");
    sleep(3);
    fclose(fptr);
    fileMod++;
  } //end while
  return 0;
} //end main
