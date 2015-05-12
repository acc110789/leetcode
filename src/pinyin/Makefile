CXX			= clang++
CXXFLAGS	= -g -O2 -Wall -fPIC -std=c++14
CXXPATH		=
LIBPATH		=
LIBS		=

all: pinyin-init test_hash

pinyin-init:
	$(CXX) -o pinyin-init.o -c $(CXXFLAGS) $(CXXPATH) pinyin-init.cpp
	$(CXX) -o pinyin-init pinyin-init.o $(LIBPATH) $(LIBS)

test_hash:
	$(CXX) -o test_hash.o -c $(CXXFLAGS) $(CXXPATH) test_hash.cpp
	$(CXX) -o test_hash test_hash.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o pinyin-init test_hash
