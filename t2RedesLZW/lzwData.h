#ifndef __LZWDATA_H__
#define __LZWDATA_H__

#define DEFAULTENTRYSIZE 5
#define DEFAULTCOLLISION 4
//a partir de alguns valores nao precisa mais aumentar
#define LARGERENTRY 4096

#define MAXINPUT 1000000
#define DICTYPE 256

typedef struct lzw_t
{
    char* entry;
    int position;
}lzw_t;

#endif