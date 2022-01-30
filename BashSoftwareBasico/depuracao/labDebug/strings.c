#include <stdio.h>

static int strconcat(char *, char *);
static int strrev(char *, char *);
static int strcopy(char *, char *);
static int strlength(char *);

// escrever as equivalentes destas em assembly usando as syscalls do MARS
//void myprintfnum(int n);
#define myprintfnum(n) printf("%d\n",(n));
//void myprintfstr(char *s);
#define myprintfstr(s) printf("%s\n",(s));

static char f16[16]="abcd.efgh_ijkl-";
static char d16[16];

static char f8[] = "abcdefg";

static char s64[64];

int main () {

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


static char slocal[256];

int strrev(char *si, char *so)
{
  int n = 0; int m;
  char *l = slocal;

  while ((*l = *si) != '\0') {
    l++; 
    si++;
    n++;
  } 
  l--;
  for (m = n; m > 0; m--)
  {
    *so++ = *l--;
  }
  *so = '\0' ;

  return(n);
}



int strcopy(char *y, char *x)
{
  int i=0;
  while ( (*x++ = *y++) != '\0' ) // copia e testa final
    i = i+1;
  *x = '\0';
  return(i);
}



int strconcat(char *si, char *sf)
{
  char *p = si;
  int n=0;
  while (*p != '\0') {
    ++p;
    n++;
  }
  while ( (*p++ = *sf++) != '\0')
    n++;
  return(n);
}



int strlength(char *s)
{
  int n=0;

  do {
    ++n; ++s;
  } while (*s != '\0');
    
  return(n);
}
