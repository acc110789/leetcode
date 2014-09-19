CC=gcc
CFLAGS=-g -O2 -Wall -fPIC
CPPPATH=
LIBPATH=
LIBS=

all: test_matrix

test_matrix:
	$(CC) -o test_matrix.o -c $(CFLAGS) $(CPPPATH) test_matrix.c
	$(CC) -o matrix.o -c -c $(CFLAGS) $(CPPPATH) matrix.c
	$(CC) -o test_matrix test_matrix.o matrix.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o test_matrix
