//Talita Halboth Cunha Fernandes GRR20165399
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TamPalavras 50

//Protótipos
char **Entrada (FILE *dic, int *tam);
void Libera (char **palavras, int linhas);
int letra (unsigned char c);
int busca (char * word, char **base,int ini,int fim);
int lower (char a);

int main(int argc, char const *argv[])
{
	char **Palavras;
	FILE* dic;
	//contador de palavras no dicionário
	int cont=0;
	//variável usada para encontrar uma palavra no dicionário
	int compara = 0;

	//abre o dicionário
	dic = fopen("/usr/share/dict/brazilian", "r");
	//testa se conseguiu abrir
	if (!dic) 
	{
		printf("Nop. Sem dicionário aqui.\n");
		exit (0);
	}
	//Le as palavras do dicionário apenas uma vez e guarda em RAM
   Palavras = Entrada(dic,&cont);
   //fecha o dicionario
	fclose (dic);
   //char que ele lê um a um da entrada
   char c;
   // vetor de char (string), para quando encontrar palavras
   char word[50];
   //palavra minúscula
   char lowerCase[50];
   //lê o primeiro caracter da entrada
   c =  getchar();
   //enquanto não for fim do arquivo
   while (feof(stdin)==0)
   {
		//confere se é letra
		if (!letra(c))
				//se não é, só imprime o char
				printf("%c",c );
		else
		{
			/*se é letra, coloca o ponteiro da entrada uma posição anterior à atual, 
			para pegar na leitura da string o char que já leu e comparou no if (!letra (c))*/
			fseek (stdin, -1, SEEK_CUR);
			int count = 0;
			//enquanto c é uma letra, coloca no vetor e incrementa o contador
			while ((letra(c))&&(feof(stdin)==0))
			{   				
				c =  getchar();
				word[count]=c;
				count++;
			}
			//coloca sentinela de fim de string
			word[count-1]='\0';
			//transforma a palavra em minúscula
			for (int i = 0; i < count; ++i)
			{
				lowerCase[i] = tolower(word[i]);
				//fazer para o caso de letras com acento, que o tolower não pega
			if (lowerCase[i]==word[i])
			{
				lowerCase[i]=lower(word[i]);
			}
			
			}
			//compara a palavra na pos. dada pela busca binária e a palavra minúscula da entrada
			//(ver especificações da minha busca binária) 
			compara = strcmp ((Palavras[busca(lowerCase, Palavras, 0, cont-1)]), lowerCase);
			if (compara == 0)
				printf("%s",word );
			else
			{
				//faz a comparação de novo, agora com a palavra original : pode ser um nome
				compara = strcmp ((Palavras[busca(word, Palavras, 0, cont-1)]), word);
				if (compara == 0)
					printf("%s",word );
				else
					printf("[%s]",word );
			}
			
			/*se a entrada no for fim do arquivo, coloca o ponteiro da entrada na posição anterior,
			porque já leu uma letra no while que não entrou no while*/
			//se for o fim do arquivo, deixa a entrada onde está para não levar a um loop infinito
			if (feof(stdin)==0)
				fseek (stdin, -1, SEEK_CUR);
   		}
   		//Lê o próximo char

   		c =  getchar();
   }
    
   
	//libera a memória alocada
	Libera (Palavras, cont);

	return 0;
}

int lower (char a) 
{
	//se for uma letra maiúscula com acento, transforma em minúscula
    if ((a >=-64)&&(a < -32))
    {
        a = (a + 32); 
    }
    return a;  

}

//busca que retorna a posição em que o elemento DEVERIA ESTAR, pode ou não estar lá
int busca (char * word, char **base,int ini,int fim)
{
	//se a posição inicial é maior que a final, o vetor está vazio, retorna a posição anteior ao início.
	if (ini > fim)
	{
		return (ini - 1);
	}
	//divide o vetor em 2 e faz a busca recursiva nas duas partes
	int m = (ini+fim)/2;
	// x retorna 0 se as strings forem iguais, >0 se a>b, e <0 se a < b
	int x = strcmp (word, base[m]);
	if (x < 0)
		//se a string que estamos buscando é maior que a string do meio, vamos para a direita
		return (busca (word, base, ini, m-1));
	//vamos para esquera em qualquer outro caso, sendo a string menor ou igual, e não testamos se a string é igual.
	return (busca (word, base, m+1, fim));
}



char **Entrada (FILE *dic, int *tam)
{
    //inicializa a o ponteiro de palavras (uma palavra pode ser um ponteiro de chars)
    char **palavras = NULL;  
    //inicializa o vetor de entrada
    char entrada[TamPalavras+1] = {0};
    //tamanho máximo de uma palavra em ptbr = 44
    int MaxTam = 50;
    //testa se dá para alocar a memoria necessária
    if (!(palavras = calloc (MaxTam, sizeof *palavras))) {
        printf ("Não coseguiu alocar a memória necessária");
        return NULL;
    }

    //enquanto ainda há palavras no vetor
    while(fgets(entrada, TamPalavras, dic))
    {
    	//o tamanho da entrada é encontrado com a função pronta que vê tamanho de strings
        int tamEntrada = strlen (entrada);
        //tira quebra de linha
        if (entrada[tamEntrada - 1] == '\n') 
            entrada[--tamEntrada] = '\0';
        //duplica a string e coloca na posição tam
        palavras[(*tam)++] = strdup (entrada);

        //aloca mais memória (se precisar)

        if (*tam == MaxTam)
        {
            void *aux = realloc (palavras, MaxTam*2*sizeof (*palavras));
            //testa se conseguiu alocar a memória
            if (!aux) 
            {
                printf("Não conseguiu mais memória\n");
                return palavras; 
            }
            //passa o realloc do ponteiro auxiliar para palavras
            palavras = aux;
            //coloca o caractere 0 em todas as posições que acabaram de ser alocadas
            memset (palavras+MaxTam,0,MaxTam*sizeof(*palavras));
            //duplica o tamanho máximo
            MaxTam = MaxTam * 2;

        }

    }
    //retorna o ponteiro
    return palavras;
}


void Libera (char **palavras, int linhas)
{

    int i;
    for (i = 0; i < linhas; i++){
    	//libera cada ponteiro de chars
        free (palavras[i]);
    }
    //libera o ponteiro pra pronteiro
    free(palavras);
}

int letra (unsigned char c)
{
	//testa um tanto de coisa pra ver se é letra. muita. coisa. mesmo. (caso do acento...)
	//também funciona pra signed chars! :)
	if (((c>='A')&&(c<='Z'))
		||((c>='a')&&(c<='z'))
		||((c>=192)&&(c<= 195))
		||((c>=199)&&(c<= 202))
		||((c>=204)&&(c<= 206))
		||((c>=210)&&(c<= 213))
		||((c>=210)&&(c<= 213))
		||((c>=217)&&(c<= 220))
		||((c>=224)&&(c<= 227))
		||((c>=231)&&(c<= 234))
		||((c>=236)&&(c<= 238))
		||((c>=242)&&(c<= 245))
		||((c>=249)&&(c<= 252)))
	{
		return 1;
	}
	else
		return 0;

}

