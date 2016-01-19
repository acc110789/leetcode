CC		= gcc
CFLAGS	= -g -O2 -Wall -fPIC -std=gnu11
CPATH	=
LIBPATH	=
LIBS	=

all: trie

trie:
	$(CC) -o trie.o -c $(CFLAGS) $(CPATH) trie.c
	$(CC) -o trie trie.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o trie
