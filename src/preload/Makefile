CC		= gcc
CFLAGS	= -g -O2 -Wall -fPIC
CPATH	=
LIBPATH	=
LIBS	=

all: test_preload malloc

test_preload:
	$(CC) -o test_preload.o -c $(CFLAGS) $(CPATH) test_preload.c
	$(CC) -o test_preload test_preload.o $(LIBPATH) $(LIBS)

malloc:
	$(CC) -o malloc.o -c $(CFLAGS) $(CPATH) malloc.c
	$(CC) -o malloc.so malloc.o $(LIBPATH) $(LIBS) -shared

clean: 
	rm -rf *.o *.so test_preload
