all: testaInclusao.out

testaInclusao.out: testaInclusao.o Circulo.o Retangulo.o FigBase.o Ponto.o
	g++  testaInclusao.o Circulo.o Retangulo.o FigBase.o Ponto.o -g -o testaInclusao.out
	
clean:
	rm Ponto.o FigBase.o Circulo.o Retangulo.o testaInclusao.o testaInclusao.out

testaInclusao.o: testaInclusao.cpp Circulo.h Retangulo.h FigBase.h Ponto.h
	g++ -c -g testaInclusao.cpp

Circulo.o: Circulo.h Circulo.cpp FigBase.h Ponto.h
	g++ -c -g Circulo.cpp

Retangulo.o: Retangulo.h Retangulo.cpp FigBase.h Ponto.h
	g++ -c -g Retangulo.cpp

FigBase.o: FigBase.h FigBase.cpp Ponto.h
	g++ -c -g FigBase.cpp

Ponto.o: Ponto.h Ponto.cpp
	g++ -c -g Ponto.cpp
