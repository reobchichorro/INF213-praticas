all: TesteFiguras3.exe

TesteFiguras3.exe: TesteFiguras3.o Circulo.o Retangulo.o Segmento.o FigBase.o 
	g++  TesteFiguras3.o Circulo.o Retangulo.o Segmento.o FigBase.o -o TesteFiguras3.exe
	#rm FigBase.o Circulo.o Retangulo.o Segmento.o TesteFiguras3.o

TesteFiguras3.o: TesteFiguras3.cpp Circulo.h Retangulo.h Segmento.h FigBase.h
	g++ -c TesteFiguras3.cpp

Circulo.o: Circulo.h Circulo.cpp FigBase.h
	g++ -c Circulo.cpp

Retangulo.o: Retangulo.h Retangulo.cpp FigBase.h
	g++ -c Retangulo.cpp

Segmento.o: Segmento.h Segmento.cpp FigBase.h
	g++ -c Segmento.cpp

FigBase.o: FigBase.h FigBase.cpp
	g++ -c FigBase.cpp
