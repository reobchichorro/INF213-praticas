
#include "Retangulo.h"
#include <iostream>
using std::cout;
using std::endl;

Retangulo::Retangulo(double x, double y, 
                     double larg, double alt,
                     int esp, int c, int t) 
    : FigBase(x, y, esp, c, t)
{
    setLargura(larg);
    setAltura(alt);
}
Retangulo::Retangulo() : FigBase() {
    setLargura(0);
    setAltura(0);
}

double Retangulo::getLargura() const {
    return largura;
}

void Retangulo::setLargura(double larg) {
    largura = larg;
}
double Retangulo::getAltura() const {
    return altura;
}

void Retangulo::setAltura(double alt) {
    altura = alt;
}

float Retangulo::area() const {
    return altura * largura;     
}      
          
float Retangulo::perimetro() const {
    return 2*(largura + altura);      
}

void Retangulo::le(std::istream& is) {
    FigBase::le(is);
    is >> largura >> altura;
}
void Retangulo::imprime() const {
    cout << "--- [Retangulo] ---" << endl;
    FigBase::imprime();
    cout << " largura = " << getLargura() << " altura = " << getAltura() << endl;  
    cout << " area = " << area() << " perimetro = " << perimetro() << endl; 
}

std::istream& operator>> (std::istream& is, Retangulo& ret) {
    ret.le(is);
    return is;
}
std::ostream& operator<< (std::ostream& os, const Retangulo& ret) {
    os << ret.getX() << " " << ret.getY() << " " << ret.getEspessura() << " " << ret.getCor() << " " << ret.getTipo() << " " << ret.getLargura() << " " << ret.getAltura();
    return os;
}