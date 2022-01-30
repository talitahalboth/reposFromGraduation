#== Stephanie Briere Americo GRR20165313 ==
#== Talita Halboth Cunha Fernandes GRR20165399 ==
CFLAGS = -Wall -g

all: busca

busca: main.o AVL_Tree.o
	gcc -o busca *.o $(CFLAGS) 

main.o: main.c 
	gcc -c main.c $(CFLAGS) 

AVL_tree.o: AVL_Tree.h AVL_Tree.c
	gcc -c AVL_Tree.c $(CFLAGS) 

purge: clean
	-rm -f busca

clean:
	-rm -f *.o
