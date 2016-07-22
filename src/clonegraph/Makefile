CC			= gcc
CXX		 	= g++
CFLAGS		= -g -O2 -Wall -fPIC -std=gnu99 
CXXFLAGS	= -g -O2 -Wall -fPIC -std=c++14
CPATH		=
CXXPATH		=
LIBPATH		=
LIBS		=

all: clonegraph designator designator-cpp

clonegraph:
	$(CXX) -o clonegraph.o -c $(CXXFLAGS) $(CXXPATH) clonegraph.cpp
	$(CXX) -o clonegraph clonegraph.o $(LIBPATH) $(LIBS)

designator:
	$(CC) -o designator.o -c $(CFLAGS) $(CPATH) designator.c
	$(CC) -o designator designator.o $(LIBPATH) $(LIBS)
	
designator-cpp:
	$(CXX) -o designator-cpp.o -c $(CXXFLAGS) $(CXXPATH) designator.cpp
	$(CXX) -o designator-cpp designator-cpp.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o clonegraph designator designator-cpp
