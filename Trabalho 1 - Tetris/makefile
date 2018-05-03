all: game.exe

game.exe: tetris.o game.o
	g++ tetris.o game.o -g -o game.exe
	
run: game.exe
	./game.exe

vrun: game.exe
	valgrind ./game.exe

clean:
	rm tetris.o game.o game.exe

game.o: game.cpp tetris.h
	g++ -c -g game.cpp

tetris.o: tetris.h tetris.cpp
	g++ -c -g tetris.cpp
