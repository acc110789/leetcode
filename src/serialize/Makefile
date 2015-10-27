CXX		 	= g++
CXXFLAGS	= -g -O2 -Wall -Werror -fPIC -std=c++0x
CXXPATH		=
LIBPATH		=
LIBS		=

all: btree

btree:
	$(CXX) -o btree.o -c $(CXXFLAGS) $(CXXPATH) btree.cpp
	$(CXX) -o btree btree.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o btree
