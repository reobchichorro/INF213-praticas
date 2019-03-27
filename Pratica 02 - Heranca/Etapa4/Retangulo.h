#ifndef __Retangulo_h
#define __Retangulo_h

#include "FigBase.h"
#include <iostream>

class Retangulo : public FigBase {
private:
    double largura, altura;

public:
    Retangulo(double, double, double, double, int, int, int);
    Retangulo();

    double getLargura() const;
    void setLargura(double);

    double getAltura() const;
    void setAltura(double);

    float area() const;
    float perimetro() const;

    void le(std::istream&); 
    void imprime() const;

    friend std::istream& operator>>(std::istream&, Retangulo&);
    friend std::ostream& operator<<(std::ostream&, const Retangulo&);

};

#endif
