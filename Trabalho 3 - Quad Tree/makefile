all: trabalho.exe

trabalho.exe: PPMImage.o quadTree.o trabalho.o
	g++ -O3 -std=c++11 -Wall PPMImage.o quadTree.o trabalho.o -g -o trabalho.exe
	
comprimir: trabalho.exe
	./trabalho.exe comprimir < exemplos/brasao.ppm > resultadosT/brasao.txt

descomprimir: trabalho.exe
	./trabalho.exe descomprimir < resultadosT/brasao.txt > resultadosI/brasao.pbm

vcomprimir: trabalho.exe
	valgrind --leak-check=full --show-leak-kinds=all ./trabalho.exe comprimir < exemplos/brasao.ppm > resultadosT/brasao.txt 

vdescomprimir: trabalho.exe
	valgrind ./trabalho.exe descomprimir < resultadosT/brasao.txt > resultadosI/brasao.pbm
	#valgrind --leak-check=full --show-leak-kinds=all ./trabalho.exe descomprimir < resultadosT/brasao.txt > resultadosI/brasao.pbm

clean:
	rm PPMImage.o quadTree.o trabalho.o trabalho.exe

trabalho.o: trabalho.cpp PPMImage.h quadTree.h
	g++ -O3 -std=c++11 -Wall -c -g trabalho.cpp

quadTree.o: quadTree.h quadTree.cpp PPMImage.h
	g++ -O3 -std=c++11 -Wall -c -g quadTree.cpp

PPMImage.o: PPMImage.h PPMImage.cpp
	g++ -O3 -std=c++11 -Wall -c -g PPMImage.cpp
