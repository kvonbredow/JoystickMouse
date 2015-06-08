CC=gcc
LIBS=-lpthread

all: libjoystick.so

install: libjoystick.so joystick.h
	cp libjoystick.so /usr/lib/
	cp joystick.h /usr/local/include/

uninstall:
	rm -f /usr/lib/libjoystick.so
	rm -f /usr/local/include/joystick.h

libjoystick.so: joystick.o
	$(CC) -shared -o libjoystick.so joystick.o $(LIBS)

joystick.o: joystick.c
	$(CC) -c joystick.c -o joystick.o -fPIC

test: joy_test.o
	gcc joy_test.o -ljoystick -o printJoy

joy_test.o: joy_test.c
	gcc -c joy_test.c -o joy_test.o

clean:
	rm -f *.o libjoystick.so
