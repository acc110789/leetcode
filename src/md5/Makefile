CC		= gcc
CFLAGS	= -g -O2 -Wall -fPIC
CPPPATH	=
LIBPATH	=
LIBS	=

all: hello_md5

hello_md5:
	$(CC) -o hello_md5.o -c $(CFLAGS) $(CPPPATH) hello_md5.c
	$(CC) -o md5.o -c $(CFLAGS) $(CPPPATH) md5.c
	$(CC) -o hello_md5 hello_md5.o md5.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o hello_md5
