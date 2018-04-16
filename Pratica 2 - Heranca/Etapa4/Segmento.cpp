
#include "Segmento.h"
#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

Segmento::Segmento(double x, double y, double x2, double y2, 
                     int esp, int c, int t) 
    : FigBase(x, y, esp, c, t)                     
{
    setX2(x2);
    setY2(y2);
}
Segmento::Segmento() : FigBase() {
    setX2(0);
    setY2(0);
}

double Segmento::getX2() const {
    return x2;
}

void Segmento::setX2(double x2) {
    this->x2 = x2;
}

double Segmento::getY2() const {
    return y2;
}

void Segmento::setY2(double y2) {
    this->y2 = y2;
}

float Segmento::area() const {
    return 0;    
}      
          
float Segmento::perimetro() const {
    double distancia = pow(x2 - FigBase::getX(), 2);
    distancia += pow(y2 - FigBase::getY(), 2);
    distancia = sqrt(distancia);
    return distancia;      
}

void Segmento::le(std::istream& is) {
    FigBase::le(is);
    is >> x2 >> y2;
}
void Segmento::imprime() const {
    cout << "--- [Segmento] ---" << endl;
    FigBase::imprime();
    cout << " x2 = " << getX2() << " y2 = " << getY2() << endl;
    cout << " area = " << area() << " perimetro = " << perimetro() << endl; 
}

std::istream& operator>> (std::istream& is, Segmento& seg) {
    seg.le(is);
    return is;
}
std::ostream& operator<< (std::ostream& os, const Segmento& seg) {
    os << seg.getX() << " " << seg.getY() << " " << seg.getEspessura() << " " << seg.getCor() << " " << seg.getTipo() << " " << seg.getX2() << " " << seg.getY2();
    return os;
}