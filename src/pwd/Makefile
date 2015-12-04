CC			= gcc
CFLAGS		= -g -O2 -Wall -fPIC
CPATH		=
LIBPATH		=
LIBS		=

all: test-shadow

test-shadow:
	$(CC) -o test-shadow.o -c $(CFLAGS) $(CPATH) test-shadow.c
	$(CC) -o test-shadow test-shadow.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o test-shadow
