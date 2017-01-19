CC=g++
CFLAGS=
RM=rm -rf
OUT=app

all: build

build: main.o
	$(CC) $(CFLAGS) main.c -o $(OUT)
	$(RM) *.o

debug: CFLAGS+=-DDEBUG_ON
debug: build

main.o: main.c vector.h adv.h
	$(CC) $(CFLAGS) -c main.c

clean:
	$(RM) *.o $(OUT)
