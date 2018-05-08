all: game.exe

game.exe: Tetris.o game.o
	g++ Tetris.o game.o -g -o game.exe
	
run: game.exe
	./game.exe

vrun: game.exe
	valgrind --leak-check=full --show-leak-kinds=all ./game.exe

jogo.exe: Tetris.cpp jogoTetris.cpp
	g++ Tetris.cpp jogoTetris.cpp -lncurses

sallesvrun:
	valgrind --leak-check=full --show-leak-kinds=all ./a.out

clean:
	rm Tetris.o game.o game.exe

game.o: game.cpp Tetris.h
	g++ -c -g game.cpp

Tetris.o: Tetris.h Tetris.cpp
	g++ -c -g Tetris.cpp
