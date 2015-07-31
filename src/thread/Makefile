CXX			= g++
CXXFLAGS	= -g -O2 -Wall -fPIC -std=c++11
CXXPATH		=
LIBPATH		=
LIBS		= -lpthread

all: test-thread

test-thread:
	$(CXX) -o mythread.o -c $(CXXFLAGS) $(CXXPATH) mythread.cpp
	$(CXX) -o test-thread.o -c $(CXXFLAGS) $(CXXPATH) main.cpp
	$(CXX) -o test-thread test-thread.o mythread.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o test-thread
