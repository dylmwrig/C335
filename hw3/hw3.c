/*
 * Author: Dylan Wright
 * HW3
 */

  #include <stdio.h>

  //because of how the bits are read in, start from the "right" side of the diagram and move left
  //macros to extract various bit fields
  #define Rd(x) ((x) & 0x7) 
  #define Rm(x) (((x) >> 3) & 0x7)
  //I don't think I need imm5
  //#define imm5(x) ((x >> 6) & 0x1F)
  #define imm8(x) (x & 0xFF)
  #define last3(x) (((x) >> 13) & 0x7)

/*
 * translate hex values to thumb instructions
 * instructions to translate
 * add/subtract register
 * add/subtract immediate
 * add/subtract/compare/move immediate
 * data-processing register
 *
 * format is ADDS <Rd>,<Rn>,<Rm>
 * where rd is destination register
 * rn is register containing the first operand
 * rm is the register optionally shifted and used as the second operand
 */
int main(){
  //char *regnames[] = {"r0", "r1", ... "pc"};
  //char *opname[]   = {"ands", "eors", ... };

  int t=0x4008;

  int test = last3(t);
  if (test == 1){
    //out of the 5 instructions we're supposed to handle, only one of them has 0 0 1 as its 13-15 binary digits
    //and this is also the instruction which uses imm8
    //so you should check this in the beginning
  } //end if

  char *inst = "4008";
  //used for reading hex codes using scanf
  while (scanf("%x", &inst) == 1){
    
  } //end while
  return 0;
} //end main