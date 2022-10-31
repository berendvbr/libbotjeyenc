CC=gcc

all: botje_yenc.o libbotjeyenc.so

clean:
	rm -f botje_yenc.o libbotjeyenc.so

install:
	cp libbotjeyenc.so /opt/homebrew/lib/libbotjeyenc.so
	cp botje_yenc.h /opt/homebrew/include/botje_yenc.h

uninstall:
	rm -f /opt/homebrew/lib/libbotjeyenc.so
	rm -f /opt/homebrew/include/botje_yenc.h

botje_yenc.o: botje_yenc.c botje_yenc.h
	$(CC) -c -o botje_yenc.o botje_yenc.c

libbotjeyenc.so: botje_yenc.o
	$(CC) -shared -o libbotjeyenc.so botje_yenc.o
