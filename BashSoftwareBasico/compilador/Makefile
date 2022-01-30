CC = gcc
CFLAGS = -Wall -O2

INCLUDEDIR = ./include

INCL = -I$(INCLUDEDIR)

DEPS = $(INCLUDEDIR)/strings.h

OBJ = main.o strings.o

strings: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< $(INCL)

clean:
	rm -f $(OBJ) 