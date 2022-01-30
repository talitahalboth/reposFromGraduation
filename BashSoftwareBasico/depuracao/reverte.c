#include <stdio.h>
#include <stdlib.h>
char slocal[256];

int main(int argc, char const *argv[])
{
  unsigned int x = 1;
  scanf ("%d", &x);
  printf("%d\n",~x );
  return 0;
}