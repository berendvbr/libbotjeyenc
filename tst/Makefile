APPNAME=run_tests
CC=gcc
FLAGS_INCLUDE=-I/opt/homebrew/include
FLAGS_LIB=-L/opt/homebrew/lib -lcmocka
OBJECTS_SHARED=../src/botje_yenc.o
OBJECTS_TESTS=test_botje_yenc__decode.o test_botje_yenc__encode.o tests.o

all: source tests

clean:
	rm -f $(APPNAME) $(OBJECTS_TESTS)

source:
	$(MAKE) -C ../src/

test_botje_yenc__decode.o: test_botje_yenc__decode.c test_botje_yenc__decode.h
	$(CC) $(FLAGS_INCLUDE) -c -o test_botje_yenc__decode.o test_botje_yenc__decode.c

test_botje_yenc__encode.o: test_botje_yenc__encode.c test_botje_yenc__encode.h
	$(CC) $(FLAGS_INCLUDE) -c -o test_botje_yenc__encode.o test_botje_yenc__encode.c

tests.o: tests.c
	$(CC) $(FLAGS_INCLUDE) -c -o tests.o tests.c

tests: $(OBJECTS_SHARED) $(OBJECTS_TESTS)
	$(CC) $(FLAGS_LIB) -o $(APPNAME) $(OBJECTS_SHARED) $(OBJECTS_TESTS)
