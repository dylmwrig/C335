void dump_memory(void *p, int len)
{
  int i;
  printf("address\t\tchar\thexCh\tshort\tinteger\t\tfloat\t\tdoubleFloat\n");

  for (i = 0; i < len; i++) {
    printf("%8p: ", p + i);
    
    //if ((isascii(*(unsigned char *) (p + i)) == 0) && *(char *)(p + i) < 126)
    char c = *(unsigned char *)(p + i);
    int ci = (int)c;
    if ((ci >= 127) || (ci < 32))
    {
      printf("?");
    }   
   
    else
    {
      printf("%c", c);//*(unsigned char *)(p + i));
    } 
    printf("\t0x%0x", *(unsigned char *)(p + i));
    
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
