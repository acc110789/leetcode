CC		= g++
CFLAGS	= -g -O2 -Wall -fPIC
CPPPATH	=
LIBPATH	=
LIBS	=

all: binary_search binary_tree hash_table boyer_moore similar

binary_search:
	$(CC) -o binary_search.o -c $(CFLAGS) $(CPPPATH) binary_search.cpp
	$(CC) -o binary_search binary_search.o $(LIBPATH) $(LIBS)

binary_tree:
	$(CC) -o binary_tree.o -c $(CFLAGS) $(CPPPATH) binary_tree.c
	$(CC) -o binary_tree binary_tree.o $(LIBPATH) $(LIBS)

hash_table:
	$(CC) -o hash_table.o -c $(CFLAGS) $(CPPPATH) hash_table.cpp
	$(CC) -o hash_table hash_table.o $(LIBPATH) $(LIBS)

boyer_moore:
	$(CC) -o BigUnsignedInABase.o -c $(CFLAGS) $(CPPPATH) bigint/BigUnsignedInABase.cc
	$(CC) -o BigIntegerUtils.o -c $(CFLAGS) $(CPPPATH) bigint/BigIntegerUtils.cc
	$(CC) -o BigUnsigned.o -c $(CFLAGS) $(CPPPATH) bigint/BigUnsigned.cc 
	$(CC) -o BigInteger.o -c $(CFLAGS) $(CPPPATH) bigint/BigInteger.cc
	$(CC) -o boyer_moore.o -c $(CFLAGS) $(CPPPATH) boyer_moore.cpp
	$(CC) -o boyer_moore boyer_moore.o BigInteger.o BigUnsigned.o \
			 BigIntegerUtils.o BigUnsignedInABase.o $(LIBPATH) $(LIBS)

similar:
	$(CC) -o similar.o -c $(CFLAGS) $(CPPPATH) similar.c
	$(CC) -o similar similar.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o binary_search binary_tree hash_table boyer_moore similar
