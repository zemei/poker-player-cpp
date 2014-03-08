
CC=g++

CFLAGS=-c -std=c++11

all: player

player: main.o player.o json.o
	$(CC) main.o player.o json.o -o player

main.o:
	$(CC) $(CFLAGS) main.cpp

player.o: 
	$(CC) $(CFLAGS) player.cpp

json.o:
	$(CC) $(CFLAGS) json.cpp

clean:
	rm -rf *.o player
