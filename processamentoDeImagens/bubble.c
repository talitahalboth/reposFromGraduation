#include <stdio.h>

void ordena (int v[9])
{
	int aux;
	for (int i = 0; i < 9; ++i)
	{
		for (int j = i+1; j < 9; ++j)
		{
			if (v[i]>v[j])
			{
				aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}

		}
	}

}
int main(int argc, char const *argv[])
{
	int vetor[9];
	for (int i = 0; i < 9; ++i)
	{
		scanf("%d", &vetor[i]);
	}
	ordena(vetor);
	for (int i = 0; i < 9; ++i)
	{
		printf("%d ", vetor[i]);
	}
	printf("\n");
	return 0;
}