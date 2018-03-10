/*
 * Author: Dylan Wright
 * HW3
 */

  #include <stdio.h>

  //because of how the bits are read in, start from the "right" side of the diagram and move left
  //macros to extract various bit fields
  //
  //Op extracts the 7th to 10th digits, which reveal the operation
  #define Rd(x) ((x) & 0x7) 
  #define Rm(x) (((x) >> 3) & 0x7)
  #define Op(x) (((x) >> 6) & 0xF)

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
  //right now I have it so that, because the number returned by the macros should be equal to the number register, I'm just indexing this array based on what is returned
  //but I don't know how I'm going to get sp, lr, and pc registers or if I even need those
  //luckily, the opname opcodes match up to their respective index numbers. Convenient
  char *regnames[11] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "sp", "lr", "pc"};
  char *opname[]   = {"ands", "eors", "lsls", "lsrs", "asrs"};

  FILE *out;
  out = fopen("test.out", "w");

  if (out == NULL){
    printf("Error opening output file");
    return;
  } //end if

  //format type stuff necessary for thumb
  fprintf(out, ".text\n.syntax unified\n.thumb\n");

  int inst;
  //used for reading hex codes using scanf
  while (scanf("%x", &inst) == 1){ 

    //extracting these digits from the hex to binary input will give you the "identity" of the hex
    int regOne = Rd(inst), regTwo = Rm(inst), op = Op(inst);

    fprintf(out, "    %s %s,%s\n", opname[op], regnames[regOne], regnames[regTwo]);
  } //end while

  fclose(out);

  return 0;
} //end main
