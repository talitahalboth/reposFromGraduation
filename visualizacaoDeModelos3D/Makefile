#Talita Halboth Cunha Fernandes GRR20165399
CFLAGS = -Wall -g -lSDL -lSDL_gfx -lm

all: wireframe
wireframe: wireframe.o entrada.o arestas.o perspectiva.o imprimeJanela.o
	gcc wireframe.o entrada.o struct.h arestas.o perspectiva.o imprimeJanela.o -o wireframe $(CFLAGS)
 
# regras de compilação
wireframe.o: wireframe.c entrada.h struct.h perspectiva.h imprimeJanela.h
	gcc  -c wireframe.c entrada.c $(CFLAGS) 
entrada.o: entrada.c struct.h
	gcc -c entrada.c struct.h  $(CFLAGS)
arestas.o: arestas.c entrada.h struct.h
	gcc -c arestas.c  entrada.h struct.h $(CFLAGS)
perspectiva.o: perspectiva.c perspectiva.h entrada.h struct.h
	gcc -c perspectiva.c perspectiva.h struct.h entrada.h
imprimeJanela.o: imprimeJanela.c imprimeJanela.h perspectiva.h entrada.h struct.h
	gcc -c imprimeJanela.c imprimeJanela.h perspectiva.h entrada.h struct.h
clean:
	-rm *.o *.gch
purge: clean
	-rm wireframe