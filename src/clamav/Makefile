CC		= gcc
CFLAGS	= -g -O2 -Wall -fPIC -std=gnu11
CPATH	=
LIBPATH	=
LIBS	= -lclamav

all: ex1

ex1:
	$(CC) -o ex1.o -c $(CFLAGS) $(CPATH) ex1.c
	$(CC) -o ex1 ex1.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o ex1
