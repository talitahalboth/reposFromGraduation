#include "limiar.h"

char* limiar (int argc,char **argv)
{
	for (int i = 0; i < argc; ++i)
	{
		if ((argv[i][0]=='-')&&(argv[i][1]=='l'))
		{
			return (argv[i+1]);
		}
	}
	return "50";
}