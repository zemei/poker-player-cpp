
CC=g++

CFLAGS=-c -std=c++11

all: player

player: main.o player.o json.o strategy.o
	$(CC) main.o player.o json.o strategy.o -o player

main.o:
	$(CC) $(CFLAGS) main.cpp

player.o: 
	$(CC) $(CFLAGS) player.cpp

json.o:
	$(CC) $(CFLAGS) json.cpp

strategy.o:
	$(CC) $(CFLAGS) strategy.cpp

clean:
	rm -rf *.o player
