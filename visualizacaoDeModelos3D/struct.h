#ifndef __STRUCT__
#define __STRUCT__

typedef struct v
{
	double x;
	double y;
	double z;
	
}vertice;


//na estrutura face estão listados os vértices que compõem a face
typedef struct f
{
	int vertices[100];
}face;

//cada aresta é uma ligação entre dois vértices


//o modelo em si é composto por vértices, faces e arestas
typedef struct strut {
	vertice *v;
	unsigned int vsize; //# de vértices
	unsigned int vAlloc;


	face *f;
	unsigned int fsize; // # de faces
	unsigned int fAlloc;


	unsigned int **a; //V – A + F = 2 
	int asize; // # de arestas
	unsigned int aAlloc;


} modelo3d;


modelo3d object;

#endif