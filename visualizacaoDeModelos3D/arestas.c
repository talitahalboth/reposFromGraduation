#include "arestas.h"

int encontraPos (int i, int obj)
{
	int j = 0;
	while (object.a[i][j]!= 0 && object.a[i][j]!= obj)
	{
		j++;

	}
	return j;
}

void plotaArestas ()
{
	//int a = 0;
	for (int k = 0; k < object.fsize; ++k)
	{
		int i = 1;
		while (object.f[k].vertices[i] != 0)
		{
			/*if (object.f[k].vertices[i] > object.f[k].vertices[i-1])
			{
				object.a[object.f[k].vertices[i-1]][object.f[k].vertices[i]] =1 ;
			}
			else
			{
				object.a[object.f[k].vertices[i]][object.f[k].vertices[i-1]] =1 ;
			}
			i++;*/
			if (object.f[k].vertices[i] > object.f[k].vertices[i-1])
			{
				int pos = encontraPos (object.f[k].vertices[i-1],object.f[k].vertices[i]);
				object.a[object.f[k].vertices[i-1]][pos] = object.f[k].vertices[i];
			}
			else
			{
				int pos = encontraPos (object.f[k].vertices[i],object.f[k].vertices[i-1]);
				object.a[object.f[k].vertices[i]][pos]= object.f[k].vertices[i-1];
			}

			i++;	
			
		}
		/*if (object.f[k].vertices[0] > object.f[k].vertices[i-1])
			object.a[object.f[k].vertices[i-1]][object.f[k].vertices[0]] =1 ;
		else if (object.f[k].vertices[0] < object.f[k].vertices[i-1])
			object.a[object.f[k].vertices[0]][object.f[k].vertices[i-1]] =1 ;*/
	}
	

}

