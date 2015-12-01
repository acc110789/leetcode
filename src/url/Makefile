CXX		 	= g++
CXXFLAGS	= -g -O2 -Wall -fPIC -std=c++0x
CXXPATH		=
LIBPATH		=
LIBS		= -luriparser

all: test-url

test-url:
	$(CXX) -o test-url.o -c $(CXXFLAGS) $(CXXPATH) test-url.cpp
	$(CXX) -o test-url test-url.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o test-url
