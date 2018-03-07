/*
 * Author: Dylan Wright
 * HW3
 */

  #include <stdio.h>

  //macros to extract various bit fields
  #define Rm(x) (((x) >> 3) & 0x3)

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

  int test = Rm(16);
  printf("%d", test);
  //used for reading hex codes using scanf
  //while (scanf("%x", &inst) == 1){ ... }
  return 0;
} //end main
