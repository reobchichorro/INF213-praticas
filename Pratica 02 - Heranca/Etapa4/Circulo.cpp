
#include "Circulo.h"
#include <iostream>
using std::cout;
using std::endl;

const float PI = 3.141592653589;

Circulo::Circulo(double x, double y, double r, 
                     int esp, int c, int t) 
    : FigBase(x, y, esp, c, t)                     
{
    setRaio(r);
}
Circulo::Circulo() : FigBase() {
    setRaio(0);
}

double Circulo::getRaio() const {
    return raio;
}

void Circulo::setRaio(double r) {
    raio = r;
}

float Circulo::area() const {
    return PI * raio * raio;    
}      
          
float Circulo::perimetro() const {
    return 2 * PI * raio;      
}

void Circulo::le(std::istream& is) {
    FigBase::le(is);
    is >> raio;
}
void Circulo::imprime() const {
    cout << "--- [Circulo] ---" << endl;
    FigBase::imprime();
    cout << " raio = " << getRaio() << endl; 
    cout << " area = " << area() << " perimetro = " << perimetro() << endl; 
}

std::istream& operator>> (std::istream& is, Circulo& cir) {
    cir.le(is);
    return is;
}
std::ostream& operator<< (std::ostream& os, const Circulo& cir) {
    os << cir.getX() << " " << cir.getY() << " " << cir.getEspessura() << " " << cir.getCor() << " " << cir.getTipo() << " " << cir.getRaio();
    return os;
}
