#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lzwData.h"




char *dic[MAXINPUT+100];
int *input;

int main(int argc, char const *argv[])
{
    setvbuf (stdout, 0, _IONBF, 0) ;
    int old, new, tam = 0, len;
    char s[LARGERENTRY+3], aux[LARGERENTRY+3],c = '\0';

    for (int i = 0; i <= MAXINPUT; ++i)
    {
        //aloca a mem inicial
        dic[i] = malloc ((LARGERENTRY+2)*sizeof(unsigned char));
        dic[i][0] = '\0';
    }


    FILE *fp;
    int x;

    if (argc > 1) fp = fopen( argv[1] , "r" );
    else fp = fopen( "compressed" , "r" );
    fscanf(fp,"%d",&x );
    fseek(fp,11,SEEK_SET );
    input = malloc (x * sizeof (int));
    fread(input , x , sizeof(int) , fp );
    fclose(fp);
    
    aux[0]='\0';
    old = input[0];
    printf("%c",old);



    int in = 1;
    while (in < x)
    {
        new = input[in];
        in++;
        //new is not on the dictionary
        if (tam <= new - DICTYPE)
        {
            // s = old
            if (old >= DICTYPE)
                strcpy (s, dic[old - DICTYPE]);
            else
            {
                s[0] = (char)old;
                s[1] = '\0';
            }
            len = strlen(s);

            // s = s + c
            s[len] = c;
            s[len+1] = '\0';
        }
        else
        {
            // s = new
            if (new >= DICTYPE)
                strcpy (s, dic[new - DICTYPE]);
            else
            {
                s[0] = (char)new;
                s[1] = '\0';
            }
        }
        printf("%s", s);
        c = s[0];
        // aux = old
        if (old >= DICTYPE)
            strcpy (aux, dic[old - DICTYPE]);
        else
        {
            aux[0] = (char)old;
            aux[1] = '\0';
        }
        if (tam < MAXINPUT)
        {
            len = strlen(aux);
            aux[len] = c;
            aux[len+1] = '\0';
            strcpy(dic[tam], aux);
            tam++;
        }
        old = new;


    }
    //libera memória
    for (int i = 0; i <= MAXINPUT; ++i)
        free(dic[i]);

    return 0;
}

