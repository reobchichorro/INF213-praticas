all: game.exe

game.exe: tetris.o game.o
	g++ tetris.o game.o -g -o game.exe
	
clean:
	rm tetris.o tetrisTeste.exe

game.o: game.cpp tetris.h
	g++ -c -g game.cpp

tetris.o: tetris.h tetris.cpp
	g++ -c -g tetris.cpp
