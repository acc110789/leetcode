CC			= gcc
CXX		 	= g++
CFLAGS		= -g -O2 -Wall -fPIC -fopenmp -std=gnu99 
CXXFLAGS	= -g -O2 -Wall -fPIC -fopenmp -std=c++14
CPATH		=
CXXPATH		=
LIBPATH		=
LIBS		= -lgomp

all: hello

hello:
	$(CC) -o hello.o -c $(CFLAGS) $(CPATH) hello.c
	$(CC) $(LIBPATH) -o hello hello.o $(LIBS)

clean: 
	rm -rf *.o hello
