//test space for my test space lol
#include <stdio.h>
#include <curses.h>

int main(){
  while (1){
    if (kbhit()){
      int c = getchar();
      printf("%c", c);
      break;
    }
  } //end while
}
