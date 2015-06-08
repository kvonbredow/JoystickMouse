CC=gcc
CFLAGS=-I../include -L../lib
LIBS=-lxdo -ljoystick

all: joy2mouse.o
	$(CC) $(CFLAGS) joy2mouse.o -o joy2mouse $(LIBS)

joy2mouse.o:
	$(CC) $(CFLAGS) -c joy2mouse.c -o joy2mouse.o $(LIBS)

clean:
	rm -rf joy2mouse.o joy2mouse
