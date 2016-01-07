CXX		 	= g++
CXXFLAGS	= -g -O2 -Wall -Werror -fPIC -std=c++0x
CXXPATH		=
LIBPATH		=
LIBS		=

all: clonegraph progress

clonegraph:
	$(CXX) -o clonegraph.o -c $(CXXFLAGS) $(CXXPATH) clonegraph.cpp
	$(CXX) -o clonegraph clonegraph.o $(LIBPATH) $(LIBS)

progress:
	$(CXX) -o progress.o -c $(CXXFLAGS) $(CXXPATH) progress.cpp
	$(CXX) -o progress progress.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o clonegraph progress
