#CC			= gcc
CC			= clang
#CXX     	= g++
CXX			= clang++
CFLAGS		= -g -pedantic -Wall -Wunused -Wunreachable-code
CXXFLAGS 	= -g -pedantic -Wall -Wunused -Wunreachable-code
CPATH		=
CXXPATH		=
LIBPATH		=
LIBS		=

all: switch sonald-switch uninit-struct

switch:
	$(CC) -o switch.o -c $(CFLAGS) $(CPATH) switch.c
	$(CC) -o switch switch.o $(LIBPATH) $(LIBS)

sonald-switch:                                                                            
	$(CC) -o sonald-switch.o -c $(CFLAGS) $(CPATH) sonald-switch.c
	$(CC) -o sonald-switch sonald-switch.o $(LIBPATH) $(LIBS)

uninit-struct:
	$(CXX) -o uninit-struct.o -c $(CXXFLAGS) $(CXXPATH) uninit-struct.cpp
	$(CXX) -o uninit-struct uninit-struct.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o switch sonald-switch uninit-struct
