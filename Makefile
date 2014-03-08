
all: player

player: main.o player.o json.o
	g++ main.o player.o json.o -o player

main.o:
	g++ -c main.cpp

player.o: 
	g++ -c player.cpp

json.o:
	g++ -c json.cpp

clean:
	rm -rf *.o player
