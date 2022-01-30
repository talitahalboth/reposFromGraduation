/***************************************************************
 * check randomness of rand() [after Kelley & Phol pp 81]
 ***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
  int i, above, below, maxdif, newv;
  int median;

  above = below = maxdif = 0;
  median = 0x3fffffff; /* 0xffffffff / 2;  median ===> (2^32 - 1) */
  printf("\n median value= %d \n", median);
  srand((unsigned int)time(NULL));
  for( i=1; i<=600000; i++ ){
    if( rand() <= median ) below++;
    else above++;
    if( (newv = abs(above - below)) > maxdif ) maxdif = newv;
    if( (i % 30000) == 0 ) 
      printf("\n i= %5d above= %5d  below= %5d maxdif= %5d",
	     i, above, below, maxdif);
  }
  printf("\n");
  return 0;
}

