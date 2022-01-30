#include <stdio.h>

#define MAX   8191
#define LOOP  1000
#define TRUE  1
#define FALSE 0

int main() {

int p[MAX];
int i, k, iter;
int num;

for (iter = 0; iter < LOOP; iter++) {
    for (i = 0; i < MAX; i++)
      p[i] = TRUE;
    i = 2;
    while (i*i <= MAX) {
      if (p[i] == TRUE) {
	k = i + i;
	while (k < MAX) {
	  p[k] = FALSE;
	  k += i;
	}
      }
      i++;
    }
    num = 0;
    for (i = 0; i < MAX; i++)
      if (p[i] == TRUE)
       ++num;
  }
  printf("Number of primes smaller than %d is %6d \n", MAX, num);

  return 0;
}
