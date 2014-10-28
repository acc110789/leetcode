CC=g++
CXXFLAGS=-g -O2 -Wall -fPIC -std=c++11
CXXPATH=
LIBPATH=
LIBS=-lpthread

all: lock_fee

lock_fee:
	$(CC) -o lock_fee.o -c $(CXXFLAGS) $(CXXPATH) lock_fee.cpp
	$(CC) -o lock_fee lock_fee.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o lock_fee
