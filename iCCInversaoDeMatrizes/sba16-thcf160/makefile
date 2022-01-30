SRC = src
OBJ = obj
INCLUDE = include

CC = gcc
CFLAGS = -Wall -g -lm -I $(INCLUDE) -O3  -DLIKWID_PERFMON -I/home/soft/likwid/include -L/home/soft/likwid/lib -llikwid -ftree-vectorizer-verbose=0 -fstrict-aliasing -mavx -march=native 
#-DDEBUG

.PHONY: dir

all: dir invmat

doc: $(SRC)/* $(INCLUDE)/*
	doxygen Doxyfile 

clean:
	-rm invmat
	-rm -r $(OBJ)

# ----

invmat: $(OBJ)/encontraMatrizInversa.o $(OBJ)/matriz.o $(OBJ)/inOut.o
		$(CC) -o invmat $(OBJ)/*.o $(CFLAGS) 
# ----

$(OBJ)/encontraMatrizInversa.o: $(SRC)/encontraMatrizInversa.c $(INCLUDE)/matriz.h $(INCLUDE)/inOut.h
		$(CC) -c $(SRC)/encontraMatrizInversa.c -o $(OBJ)/encontraMatrizInversa.o $(CFLAGS)

$(OBJ)/matriz.o: $(SRC)/matriz.c
		$(CC) -c $(SRC)/matriz.c -o $(OBJ)/matriz.o $(CFLAGS)

$(OBJ)/inOut.o: $(SRC)/inOut.c
		$(CC) -c $(SRC)/inOut.c -o $(OBJ)/inOut.o $(CFLAGS)

dir:
	mkdir -p $(OBJ)
		
