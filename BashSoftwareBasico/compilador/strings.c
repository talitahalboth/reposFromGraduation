char slocal[256];

int strrev(const char *si, char *so)
{
  int n = 0; int m;
  char *l = slocal;

  while ((*l = *si)) {
    l++; si++ ;
    n++;
  } 
  l--;
  for (m = n; m > 0; m--)
    *so++ = *l--;
  *so = '\0' ;

  return(n);
}


int strcopy(const char *y, char *x)
{
  int i = 0;

  while ( (*x++ = *y++) != '\0' )
    i = i+1;
  *x = '\0';
  return(i+1);
}


int strconcat(char *si, const char *sf)
{
  char *p = si;
  int n = 0;

  while (*p != '\0') {
    ++p;
    n++;
  }
  while ( (*p++ = *sf++) )
    n++;
  return(n+1);
}


int strlength(const char *s)
{
  int n = 0;

  do {
    ++n;
  } while (*s++ != '\0');
    
  return(n);
}