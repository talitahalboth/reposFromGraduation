#include "perspectiva.h"
#include <math.h>

int aaa;

void inita ()
{
	aaa = 0;
}

void alocatmp ()
{
	objEmpErspectiva = malloc (object.vsize*2*sizeof(vertice));
	objtmp = malloc (object.vsize*2*sizeof(vertice));
		for (int i = 0; i < object.vsize; ++i)
	{
		objtmp[i].x = object.v[i].x;
		objtmp[i].y = object.v[i].y;
		objtmp[i].z = object.v[i].z;
	}
}

void freetmp ()
{
	free (objEmpErspectiva);
	free (objtmp);
}

void perspectivaFraca (double xc, double yc,double  zc)
{
	
	for (int i = 0; i < object.vsize; ++i)
	{
		/*Considerando que as coordenadas da câmera são [xc yc zc] 
		e que a câmera está olhando para a origem [0 0 0], 
		a conversão das coordenadas 3D de cada vértice v = [xv yv zv] 
		em sua projeção 2D p = [xp yp] no plano z = 0 pode ser calculada desta forma:*/
		/*xp = xc + zc × ( (xv - xc) ÷ (zv + zc) )
		yp = yc + zc × ( (yv - yc) ÷ (zv + zc) )*/
		//tentando com [xc yc zc] = [1 1 1]

		objEmpErspectiva[i].x = xc + ((objtmp[i].x - xc)/(objtmp[i].z + zc));
		objEmpErspectiva[i].y = yc + ((objtmp[i].y - yc)/(objtmp[i].z + zc));
	}
}

void rotacionaX (double a)
{
	for (int i = 0; i < object.vsize; ++i)
	{

		objtmp[i].x =objtmp[i].x; 
		objtmp[i].y = cos(a)*object.v[i].y - sin(a)*object.v[i].z;
		objtmp[i].z = sin(a)*object.v[i].y + cos(a)*object.v[i].z;
	}

}

void rotacionaY (double a)
{
	for (int i = 0; i < object.vsize; ++i)
	{

		objtmp[i].x = cos(a)*object.v[i].x + sin(a)*object.v[i].z;
		objtmp[i].y = objtmp[i].y;
		objtmp[i].z = -sin(a)*object.v[i].x + cos(a)*object.v[i].z;
	}

}
void rotacionaZ (double a)
{
	for (int i = 0; i < object.vsize; ++i)
	{

		object.v[i].x = cos(a)*object.v[i].x + sin(a)*object.v[i].z;
		object.v[i].y = sin(a)*object.v[i].x + cos(a)*object.v[i].y;
		object.v[i].z = object.v[i].z;
	}

}
void convertePonto ()
{

	long double xmin = objEmpErspectiva[0].x,	xmax = objEmpErspectiva[0].x, ymin = objEmpErspectiva[0].y, ymax = objEmpErspectiva[0].y;
	for (int i = 0; i < object.vsize; ++i)
	{
		xmin = objEmpErspectiva[i].x < xmin ? objEmpErspectiva[i].x : xmin;
		xmax = objEmpErspectiva[i].x > xmax ? objEmpErspectiva[i].x : xmax;
		ymin = objEmpErspectiva[i].y < ymin ? objEmpErspectiva[i].y : ymin;
		ymax = objEmpErspectiva[i].y > ymax ? objEmpErspectiva[i].y : ymax;
	}
	if (!aaa)
	{
		aaa = 1;
		max = xmax > ymax ? xmax : ymax;
	}
	long double xcen = (xmax + xmin) / 2, xdif = (xmax - xmin), ycen = (ymax + ymin) / 2, ydif = (ymax - ymin);
	int w = 640, h = 480;
	long double escx = w/xdif, escy = h/ydif;

	long double escala = escx < escy ? escx : escy;
	for (int i = 0; i < object.vsize; ++i)
	{
		objEmpErspectiva[i].x =( (objEmpErspectiva[i].x - xcen) * escala) + w/2;

		
		objEmpErspectiva[i].y =( (objEmpErspectiva[i].y - ycen) * escala) + h/2;
		//printf("x = %lf, i = %d\n",objEmpErspectiva[i].x,i );
		//printf("y = %lf, i = %d\n",objEmpErspectiva[i].y, i );
		
	}

	/*Passo 1: calcular mínimos, máximos, centros e diferenças das coordenadas em X e Y
	xmin = min (xp)
	xmax = max (xp)
	xcen = (xmax + xmin) / 2
	xdif = xmax - xmin
	ymin = min (yp)
	ymax = max (yp)
	ycen = (ymax + ymin) / 2
	ydif = ymax - ymin
	Passo 2: calcular fator de escala para o desenho na tela

	W: largura da janela de desenho (em pixels)
	H: altura da janela de desenho (em pixels)
	escx = W / xdif
	escy = H / ydif
	escala = min (escx, escy)
	Passo 3: centrar pontos da projeção em [0 0]

	∀ (x y)
	x'p = xp - xcen
	y'p = yp - ycen
	Passo 4: ajustar escala dos pontos da projeção para a tela

	∀ (x y)
	x“p = x'p * escala
	y”p = y'p * escala
	Passo 5: ajustar pontos do desenho em relação ao centro da tela

	∀ (x y)
	xd = x“p + W / 2
	yd = y”p + H / 2
	Os passos 3 a 5 podem ser condensados em um único passo:

	∀ (x y)
	xd = ( (xp - xcen) * escala) + W / 2
	yd = ( (yp - ycen) * escala) + H / 2 */
}