#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lzwData.h"


lzw_t **dic[LARGERENTRY+2];
int collisions[LARGERENTRY+2];
int *output;

unsigned long hashstring(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash%LARGERENTRY;
}

int findPosition(char *a)
{
    
    unsigned long hash = 0;
    hash = hashstring (a);
    
    int i;
    for (i = 0; i < collisions[hash] && dic[hash][i]->entry[0] != '\0' && strcmp(dic[hash][i]->entry,a); ++i);
        
    if (i < collisions[hash] && !strcmp(dic[hash][i]->entry,a))
    {
        
        return dic[hash][i]->position;
    }
    return -1;
}

void updadeDic(char *a, int pos)
{
    
    unsigned long hash = 0;
    for (int i = 0; a[i] != '\0'; ++i)
        hash+=a[i];
    hash = hashstring (a);
    int i;
    for (i = 0; i < collisions[hash] && dic[hash][i]->entry[0] != '\0'; ++i);

    if (i == collisions[hash])
    {

        dic[hash] =  realloc (dic[hash],2*collisions[hash]*sizeof(lzw_t));
        for (int j = collisions[hash]; j < 2*collisions[hash]; ++j)
        {
            dic[hash][j] = malloc(sizeof(lzw_t));
            dic[hash][j]->entry = malloc (DEFAULTENTRYSIZE * sizeof (char));
            dic[hash][j]->entry[0] = '\0';
        }
        
        collisions[hash]=2*collisions[hash];
    }
    int len;
    if (len = strlen(a) > LARGERENTRY)
        dic[hash][collisions[hash]]->entry = realloc(dic[hash][collisions[hash]]->entry, len*sizeof(char));
    strcpy(dic[hash][i]->entry, a);

    dic[hash][i]->position = pos;

}

int main(int argc, char const *argv[])
{
    unsigned char p[LARGERENTRY + 1],aux[LARGERENTRY + 1], c;
    int tam = 0, pos;
    for (int i = 0; i <= LARGERENTRY; ++i)
    {
        //aloca a mem inicial
        dic[i] = malloc (DEFAULTCOLLISION*sizeof(lzw_t)*2);
        collisions[i] = DEFAULTCOLLISION;
        for (int j = 0; j < DEFAULTCOLLISION; ++j)
        {
            dic[i][j] = malloc(sizeof(lzw_t));
            dic[i][j]->entry = malloc (DEFAULTENTRYSIZE * sizeof (char));
            dic[i][j]->entry[0] = '\0';
        }
    }
    output = malloc (LARGERENTRY * sizeof (int));
    //tamanho do vetor outsize
    int outSize = LARGERENTRY;
    p[0]='\0';
    aux[0] = '\0';
    //posições ocupadas no vetor output
    int x = 0;
    //enquanto não é o fim da entrada  
    while (scanf ("%c", &c ) != EOF)
    {
    	//se não tem mais posições livre em outsize, realoca a memória
        if (x >= outSize-1)
        {
            outSize = outSize*2;
            output = realloc (output, outSize*sizeof(int));
        }
        //aux = p
        strcpy (aux,p);
        //se aux tem menos chars que LARGERENTRY
        if ((strlen(aux))<LARGERENTRY)
        {
            
            int isInDic = 0;

            //aux = p + c
            int len = (strlen(aux));
            aux[len+1] = '\0';
            aux[len] = c;
            if (strlen (aux) > 1)
            {
                
                if (findPosition(aux) != -1)
                    isInDic = 1;
            }

            else
                isInDic = 1;
            // p + c está no dicionátio
            if (isInDic)

                //p = p + c
                strcpy (p,aux);
            //p + c não está no dicionário
            else
            {
                if (strlen (p) > 1) 
                {
                    pos = findPosition(p);            
                    output[x] = pos + DICTYPE;
                    x++;
                }
                else 
                {                    
                    output[x] = (int)p[0];
                    x++;
                }
                //só atualiza o dicionário se ele tem menos de MAXINPUT entradas
                if (tam < MAXINPUT)
                {
                    updadeDic(aux, tam);
                    tam++;
                }
                p[0] = c;
                p[1] = '\0';
            }
        }
        //se aux tem chars >= LARGERENTRY, não coloca no dicionário
        else
        {
            if (strlen (p) > 1) 
            {
                pos = findPosition(p);            
                output[x] = pos + DICTYPE;
                x++;
            }
            else 
            {                    
                output[x] = (int)p[0];
                x++;
            }
            p[0] = c;
            p[1] = '\0';

        }

    }

    if (strlen (p) > 1) 
    {

        pos = findPosition(p);
        output[x] = pos + DICTYPE;
        x++;
    }
    else
    {        
        output[x] = (int)p[0];
        x++;
    }
      
    FILE *fp;
    if (argc > 1)   
        fp = fopen( argv[1] , "w" );
    else
        fp = fopen( "compressed" , "w" );
    fprintf(fp,"%10d\n",x );

    fwrite(output , x , sizeof(int) , fp );

    //libera memória
    fclose(fp);
    for (int i = 0; i <= LARGERENTRY; ++i)
    {
        for (int j = 0; j < DEFAULTCOLLISION; ++j)
        {
            free(dic[i][j]->entry);
            free(dic[i][j]);
        }
        free(dic[i]);
    }
    free (output);

    return 0;
}