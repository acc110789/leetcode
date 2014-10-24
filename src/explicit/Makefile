CC=g++
CFLAGS=-g -O2 -Wall -fPIC
CPPPATH=
LIBPATH=
LIBS=

all: test_explicit 

test_explicit:
	$(CC) -o test_explicit.o -c $(CFLAGS) $(CPPPATH) test_explicit.cpp
	$(CC) -o test_explicit test_explicit.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o test_explicit

