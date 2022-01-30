// cMIPS.h define o símbolo cMIPS
// #include "cMIPS.h"

#ifndef cMIPS
  #include <stdio.h>
#endif

void main(void) {

  while( x != y ) {
        
    if( x > y ) {
      x -= y;
#ifdef cMIPS
      print(x);           // impressão sem função de biblioteca
#else
      printf("%08x ",x);
#endif
    } else {
      y -= x;
#ifdef cMIPS
      print(y);           // impressão sem função de biblioteca
#else
      printf("%08x ",y);
#endif
    }
  }
}