CC		= gcc
CFLAGS	= -g -O2 -Wall -fPIC -std=gnu99
CPATH	=
LIBPATH	=
LIBS	= -lX11 -lXt -lXaw

all: xmenu

xmenu:
	$(CC) -o xmenu.o -c $(CFLAGS) $(CPATH) xmenu.c
	$(CC) -o xmenu xmenu.o $(LIBPATH) $(LIBS)

clean: 
	rm -rf *.o xmenu
