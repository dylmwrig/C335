void dump_memory(void *p, int len)
{
  int i;
  printf("address\t\tchar\thexCh\tshort\tinteger\t\tfloat\t\tdoubleFloat\n");

  for (i = 0; i < len; i++) {
    printf("%8p: ", p + i);
    
    char c = *(unsigned char *)(p + i);
    int ci = (int)c; //cast c to int to see if the character is printable 
    if ((ci >= 127) || (ci < 32))
    {
      printf("?");
    }   
   
    else
    {
      printf("%c", c);
    } 
    printf("\t0x%0x", *(unsigned char *)(p + i));
    
    /*
     * for everything else, only print when the amount of bytes is correct
     * ie every 4, print the integer
     * without this, garbage would be printed
     * EJ and I collaborated on every part of this section
     * as far as logic, casting, printf semantics, etc.
     * the only real difference in our code otherwise only comes down to code style
     */
    //short
    if (i%2 == 0)
    {
      printf("\t%+hi", *(short *)(p + i));
    } //end if

    else
    {
      printf("\t");
    } //end else

    //integer and float
    if (i%4 == 0)
    {
      printf("\t%+d", *(int *)(p + i));
      printf("\t%e", *(float *)(p + i));
    } //end if

    else
    {
      printf("\t\t");
    } //end else

    if (i%8 == 0)
    {
      printf("\t%g", *(double *)(p + i));
    } //end if
   
    else
    {
      printf("\t");
    } //end else
    printf("\n");
  }
}
