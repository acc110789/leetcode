CXX			= g++
CXXFLAGS	= -g -O2 -Wall -fPIC -std=c++11 -Werror
INCPATH		=
LIBPATH		=
LIBS		=

all: idiom

idiom:
	$(CXX) -o main.o -c $(CXXFLAGS) $(INCPATH) main.cpp
	$(CXX) -o idiom main.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o idiom
