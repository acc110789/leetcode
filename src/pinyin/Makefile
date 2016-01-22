CXX			= g++
CXXFLAGS	= -g -pg -O3 -Wall -fPIC -std=c++14
CXXPATH		=
LIBPATH		=
LIBS		=

all: pinyin-init

pinyin-init:
	$(CXX) -o pinyin-init.o -c $(CXXFLAGS) $(CXXPATH) pinyin-init.cpp
	$(CXX) -pg -o pinyin-init pinyin-init.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o pinyin-init
