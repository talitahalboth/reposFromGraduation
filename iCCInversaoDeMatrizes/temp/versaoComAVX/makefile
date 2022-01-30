SRC = src
OBJ = obj
INCLUDE = include

CC = g++
CFLAGS = -Wall -g -lm -I $(INCLUDE) -O3 -ftree-vectorizer-verbose=2 -fstrict-aliasing -mavx -march=native
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

$(OBJ)/encontraMatrizInversa.o: $(SRC)/encontraMatrizInversa.C $(INCLUDE)/matriz.h $(INCLUDE)/inOut.h
		$(CC) -c $(SRC)/encontraMatrizInversa.C -o $(OBJ)/encontraMatrizInversa.o $(CFLAGS)

$(OBJ)/matriz.o: $(SRC)/matriz.C
		$(CC) -c $(SRC)/matriz.C -o $(OBJ)/matriz.o $(CFLAGS)

$(OBJ)/inOut.o: $(SRC)/inOut.C
		$(CC) -c $(SRC)/inOut.C -o $(OBJ)/inOut.o $(CFLAGS)

dir:
	mkdir -p $(OBJ)
		
