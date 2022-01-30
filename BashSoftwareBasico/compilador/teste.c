#include <stdio.h>
#include <math.h>
#define MAX(p,q)   ( (p) > (q) ? (p) : (q) )
#define EQUAL(a,b) ( (a) == (b) ? (1) : (0))
#define MIN(p,q)  ( (p) < (q) ? (p) : (q) )
#define MAX3(a,b,c) ((a) > (b) ? ((a) > (c) ? (a) : (c)) : ((b) > (c) ? (b) : (c)))
#define MIN3(a,b,c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))
#define BHASKARA(a,b,c)    \
({                         \
	float (x) = (a);                                \
	(a) = ((-b + sqrt(b*b - 4*a*c))/2) ; \
	(b) = ((-b - sqrt(b*b - 4*x*c))/2) ; \
})
//#define BASKARA(a,b,c) ((a) = (float)((-b + sqrt(b*b - 4*a*c))/2) (b) = (float)())

int main(int argc, char const *argv[])
{
	float a = 1, b = 4, c = 1;
	BHASKARA(a,b,c);
	printf("%f %f\n",a,b );
	return 0;
}