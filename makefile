CC=g++
CFLAGS=
RM=rm -rf
OUT=app

all: build

build: main.o
	$(CC) $(CFLAGS) main.cpp -o $(OUT)
	$(RM) *.o

debug: CFLAGS+=-DDEBUG_ON
debug: build

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

clean:
	$(RM) *.o $(OUT)
