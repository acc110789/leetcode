CXX			= clang++
CXXFLAGS	= -g -O2 -Wall -fPIC -std=c++11
CXXPATH		=
LIBPATH		=
LIBS		=

all: pinyin-init

pinyin-init:
	$(CXX) -o pinyin-init.o -c $(CXXFLAGS) $(CXXPATH) pinyin-init.cpp
	$(CXX) -o pinyin-init pinyin-init.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o pinyin-init
