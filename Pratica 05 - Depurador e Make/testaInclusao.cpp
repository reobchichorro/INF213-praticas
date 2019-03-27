#include <iostream>
#include "Circulo.h"
#include "Retangulo.h"
#include "Ponto.h"
using namespace std;

//listaFigurasPtr e' um array com numFigurasNaLista apontadores apontando para figuras geometricas
//imprime quantas dessas figuras contem o ponto p
void contaQuantasFigurasContem(FigBase **listaFigurasPtr, int numFigurasNaLista, Ponto p) {
	int ct = 0;
	for(int i=0;i<numFigurasNaLista;i++) 
		if(listaFigurasPtr[i]->contem(p)) {
			ct++;
		}
	cout << "Figuras contendo ponto: " << p.getX() << "," << p.getY() << " : " << ct << endl;
}

int main() {
	FigBase *figuras[5];
	figuras[0] = new Circulo(Ponto(0,0),5);
	figuras[1] = new Circulo(Ponto(1,1),10);
	figuras[2] = new Circulo(Ponto(10,10),2);
	figuras[3] = new Retangulo(Ponto(0,0),Ponto(1,1));
	figuras[4] = new Retangulo(Ponto(10,10),Ponto(20,30));

	//Dica: Desenhe as figuras/pontos em um pedaco de papel para facilitar o processo de depuracao
	Ponto p0(0,0);
	Ponto p1(15,0);
	contaQuantasFigurasContem(figuras,5,p0); // qual deveria ser a resposta?

	contaQuantasFigurasContem(figuras,5,p1); 
}