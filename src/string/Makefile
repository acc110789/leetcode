CC		= gcc
CFLAGS	= -g -O2 -Wall -fPIC -std=gnu11
CPATH	=
LIBPATH	=
LIBS	= -lm

all: strtok strcpy align heart snprintf

strtok:
	$(CC) -o strtok.o -c $(CFLAGS) $(CPATH) strtok.c
	$(CC) -o strtok strtok.o $(LIBPATH) $(LIBS)

strcpy:
	$(CC) -o strcpy.o -c $(CFLAGS) $(CPATH) strcpy.c
	$(CC) -o strcpy strcpy.o $(LIBPATH) $(LIBS)

align:
	$(CC) -o align.o -c $(CFLAGS) $(CPATH) align.c
	$(CC) -o align align.o $(LIBPATH) $(LIBS)

heart:
	$(CC) -o heart.o -c $(CFLAGS) $(CPATH) heart.c
	$(CC) -o heart heart.o $(LIBPATH) $(LIBS)

snprintf:
	$(CC) -o snprintf.o -c $(CFLAGS) $(CPATH) snprintf.c
	$(CC) -o snprintf snprintf.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o strtok strcpy align heart snprintf
