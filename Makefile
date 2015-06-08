CC=gcc
CFLAGS=-I./include
LIBS=-lxdo -ljoystick -lpthread

all: xdotool.so joystick.so joy2mouse
	mv src/joy2mouse bin/

xdotool.so:
	make -C xdotool/
	cp xdotool/xdo.h include/
	cp xdotool/libxdo.so lib/
	ln -fs libxdo.so lib/libxdo.so.2

joystick.so:
	make -C joystick/
	cp joystick/joystick.h include/
	cp joystick/libjoystick.so lib/

joy2mouse:
	make -C src/

clean:
	make clean -C xdotool/
	make clean -C joystick/
	make clean -C src/
	rm -f include/* lib/* bin/*
