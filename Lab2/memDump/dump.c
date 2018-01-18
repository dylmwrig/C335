void dump_memory(void *p, int len)
{
  int i;

  for (i = 0; i < len; i++) {
    printf("%8p: %02x\n", p + i, *(unsigned char *)(p + i));
  }
}
