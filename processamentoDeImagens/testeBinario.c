#include <stdio.h>
int imagem[1000][1000];

int main(int argc, char const *argv[])
{
	int colunas,linhas,celula, maxBranco;
	scanf ("P2");
	scanf (" %d %d", &colunas, &linhas);
	scanf("%d", &maxBranco);
	for (int i = 0; i < linhas; ++i)
	{
		for (int j = 0; j < colunas; ++j)
		{
			scanf ("%d", &imagem[i][j]);
		}
	}
	printf("P2\n");
	printf("%d %d\n",colunas, linhas);
	printf("%d\n",maxBranco);
	for (int i = 0; i < linhas; ++i)
	{
		for (int j = 0; j < colunas; ++j)
		{
			printf("%d ",imagem[i][j] );
		}
	}
	return 0;
}