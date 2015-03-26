CC		= gcc
CFLAGS	= -g -O2 -Wall -fPIC -std=gnu99
CPATH	=
LIBPATH	=
LIBS	=

all: malloc

malloc:
	$(CC) -o malloc.o -c $(CFLAGS) $(CPATH) malloc.c
	$(CC) -o malloc malloc.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o malloc
