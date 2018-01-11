#include <stdio.h>
#include <unistd.h>
#include <string.h>

/*
 * the original idea was to have multiple files saying "HI" on a loop at the same time
 * while new ones were created and executed
 * I didn't consider how control was transferred and that only one would run at a time
 */
int main()
{
  char fileName[50];
  char origName[50];
  char fileModStr[10];
  char outName[50];
  char cmd[50];
  int fileMod = 1;
  origName[0] = 'h'; //both the output file and the new source files will start with "hi"
  origName[1] = 'i';
  FILE * fptr;
    
  while(1)
  {
    strcpy(fileName, origName);
    printf("Hello World!\n");
    sprintf(fileModStr, "%d", fileMod);
    strcat(fileName, fileModStr);
    strcat(fileName, ".c");
    fptr = fopen(fileName, "w"); //create a new source file
    fprintf(fptr, "#include <stdio.h>\n"
                  "int main(){"
                  "printf(\"HI\");\n"
                  "return 0;}");
    fclose(fptr);
                
    strcpy(outName, origName);
    strcat(outName, fileModStr);
    strcat(outName, ".out ");                     
    strcpy(cmd, "gcc -o");
    strcat(cmd, outName);
    strcat(cmd, fileName);
    system(cmd);       //create the output file using the newly created source
    strcpy(cmd, "./"); //run the output file
    strcat(cmd, outName);
    system(cmd);

    sleep(3);
    fileMod++;
  } //end while
  return 0;
} //end main
