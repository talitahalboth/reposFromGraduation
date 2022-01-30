
CFLAGS = -Wall -g

all: pgmlimiar pgmnega pgmmedia pgmmediana

pgmlimiar: pgmlimiar.o imgInOut.o limiar.o
	gcc pgmlimiar.o imgInOut.o limiar.o -o pgmlimiar $(CFLAGS)

pgmnega: pgmnega.o imgInOut.o
	gcc pgmnega.o imgInOut.o -o pgmnega $(CFLAGS)

pgmmedia: pgmmedia.o imgInOut.o
	gcc pgmmedia.o imgInOut.o -o pgmmedia $(CFLAGS)

pgmmediana: pgmmediana.o imgInOut.o
	gcc pgmmediana.o imgInOut.o -o pgmmediana $(CFLAGS)

 
# regras de compilação
pgmnega.o: pgmnega.c imgInOut.h
	gcc -c pgmnega.c $(CFLAGS)

pgmlimiar.o: pgmlimiar.c imgInOut.h limiar.h
	gcc -c pgmlimiar.c $(CFLAGS)

pgmmedia.o: pgmmedia.c imgInOut.h
	gcc -c pgmmedia.c $(CFLAGS)
 
pgmmediana.o: pgmmediana.c imgInOut.h
	gcc -c pgmmediana.c $(CFLAGS)
 
imgInOut.o: imgInOut.c imgInOut.h
	gcc -c imgInOut.c $(CFLAGS)
 
limiar.o: limiar.c limiar.h imgInOut.h
	gcc -c limiar.c $(CFLAGS)

clean:
	-rm *.o

purge: clean
	-rm pgmnega