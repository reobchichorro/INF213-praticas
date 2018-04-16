all: TesteFiguras.exe

TesteFiguras.exe: TesteFiguras.o Circulo.o Retangulo.o FigBase.o 
	g++  TesteFiguras.o Circulo.o Retangulo.o FigBase.o -o TesteFiguras.exe
	rm FigBase.o Circulo.o Retangulo.o TesteFiguras.o

TesteFiguras.o: TesteFiguras.cpp Circulo.h Retangulo.h FigBase.h
	g++ -c TesteFiguras.cpp

Circulo.o: Circulo.h Circulo.cpp FigBase.h
	g++ -c Circulo.cpp

Retangulo.o: Retangulo.h Retangulo.cpp FigBase.h
	g++ -c Retangulo.cpp

FigBase.o: FigBase.h FigBase.cpp
	g++ -c FigBase.cpp
