CC=gcc
CFLAGS=-g -O2 -Wall -fPIC
CPPPATH=
LIBPATH=
LIBS=-lm

all: test_matrix test_cm test_lspa

test_matrix:
	$(CC) -o test_matrix.o -c $(CFLAGS) $(CPPPATH) test_matrix.c
	$(CC) -o matrix.o -c $(CFLAGS) $(CPPPATH) matrix.c
	$(CC) -o test_matrix test_matrix.o matrix.o $(LIBPATH) $(LIBS)

test_cm:
	$(CC) -o test_cm.o -c $(CFLAGS) $(CPPPATH) test_cm.c
	$(CC) -o cm.o -c $(CFLAGS) $(CPPPATH) cm.c
	$(CC) -o matrix.o -c $(CFLAGS) $(CPPPATH) matrix.c
	$(CC) -o test_cm test_cm.o cm.o matrix.o $(LIBPATH) $(LIBS)

test_lspa:
	$(CC) -o test_lspa.o -c $(CFLAGS) $(CPPPATH) test_lspa.c
	$(CC) -o lspa.o -c $(CFLAGS) $(CPPPATH) lspa.c
	$(CC) -o cm.o -c $(CFLAGS) $(CPPPATH) cm.c
	$(CC) -o matrix.o -c $(CFLAGS) $(CPPPATH) matrix.c
	$(CC) -o test_lspa test_lspa.o lspa.o cm.o matrix.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o test_matrix test_cm test_lspa
