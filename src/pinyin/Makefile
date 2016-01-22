CXX			= g++
CXXFLAGS	= -g -pg -O3 -Wall -fPIC -std=c++14
CXXPATH		=
LIBPATH		=
LIBS		=

all: pinyin-init pinyin

pinyin-init:
	$(CXX) -o pinyin-init.o -c $(CXXFLAGS) $(CXXPATH) pinyin-init.cpp
	$(CXX) -pg -o pinyin-init pinyin-init.o $(LIBPATH) $(LIBS)

pinyin:
	$(CXX) -o portability.o -c $(CXXFLAGS) $(CXXPATH) portability.cpp
	$(CXX) -o sim_dict.o -c $(CXXFLAGS) $(CXXPATH) sim_dict.cpp
	$(CXX) -o pinyin.o -c $(CXXFLAGS) $(CXXPATH) pinyin.cpp
	$(CXX) -pg -o pinyin portability.o sim_dict.o pinyin.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o pinyin-init pinyin
