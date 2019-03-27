
#include "Retangulo.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

Retangulo::Retangulo(const Ponto &p0_, const Ponto &p1_): FigBase(p0) {
	p1 = p1_;
}

const Ponto& Retangulo::getP1() const {
	return p1;
}

void Retangulo::setP1(const Ponto &p1_) {
	p1 = p1_;
}
    
bool Retangulo::contem(const Ponto &p) const {
	//Verifica se o ponto p esta dentro do retangulo definido por p0 (canto inferior esquerdo do retangulo) e p1
	//(canto superior direito do retangulo)
	bool xNoIntervalo = (p.getX() > p0.getX() && p.getX() < p1.getX());
	bool yNoIntervalo = (p.getY() > p0.getY() && p.getY() < p1.getY());
	return  xNoIntervalo && yNoIntervalo;
}