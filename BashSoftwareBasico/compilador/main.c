#include <stdio.h>
#include <strings.h>

#define myprintfnum(n) printf("%d\n",(n));
#define myprintfstr(s) printf("%s\n",(s));

char f16[16]="abcd.efgh_ijkl-";
char d16[16];

char f8[] = "abcdefg";
char d8[] = "ABCDEFG";

char s64[64];

int main (void)
{
  int num=0;

  num = strrev(f16,d16);
  myprintfstr(d16);

  num = strcopy(f16,s64);
  myprintfnum(num);
  myprintfstr(s64);

  num = strconcat(s64,f8);
  myprintfnum(num);
  myprintfstr(s64);

  num = strlength(s64);
  myprintfnum(num);

  return(0);
}