CXX		 	= g++
CXXFLAGS	= -g -O2 -Wall -Werror -fPIC -std=c++0x
CXXPATH		=
LIBPATH		=
LIBS		=

all: clonegraph

clonegraph:
	$(CXX) -o clonegraph.o -c $(CXXFLAGS) $(CXXPATH) clonegraph.cpp
	$(CXX) -o clonegraph clonegraph.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o clonegraph
