CC		= gcc
CFLAGS	= -g -O2 -Wall -fPIC
CPPPATH	=
LIBPATH	=
LIBS	= -lm

all: liuhui

liuhui:
	$(CC) -o liuhui.o -c $(CFLAGS) $(CPPPATH) liuhui.c
	$(CC) -o liuhui liuhui.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o liuhui
