CC=g++
CFLAGS=-g -O2 -Wall -fPIC
CPPPATH=
LIBPATH=
LIBS=

all: fast_log

fast_log:
	$(CC) -o fast_log.o -c $(CFLAGS) $(CPPPATH) fast_log.cpp
	$(CC) -o fast_log fast_log.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o fast_log
