CC=gcc
CCFLAGS=-O2 -Wall

all: botje_yenc.o libbotje_yenc.so

clean:
	rm -f botje_yenc.o libbotje_yenc.so

install:
	cp botje_yenc.h /opt/homebrew/include/botje_yenc.h
	cp libbotje_yenc.so /opt/homebrew/lib/libbotje_yenc.so

uninstall:
	rm -f /opt/homebrew/include/botje_yenc.h
	rm -f /opt/homebrew/lib/libbotje_yenc.so

botje_yenc.o: botje_yenc.c botje_yenc.h
	$(CC) $(CCFLAGS) -c -o botje_yenc.o botje_yenc.c

libbotje_yenc.so: botje_yenc.o
	$(CC) $(CCFLAGS) -shared -o libbotje_yenc.so botje_yenc.o
