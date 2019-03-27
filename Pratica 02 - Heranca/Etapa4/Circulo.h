#ifndef __Circulo_h
#define __Circulo_h

#include "FigBase.h"

class Circulo : public FigBase {
private:
    double raio;

public:
    Circulo(double, double, double, int, int, int);
    Circulo();

    double getRaio() const;
    void setRaio(double);
    
    float area() const;
    float perimetro() const;

    void le(std::istream&); 
    void imprime() const;

    friend std::istream& operator>>(std::istream&, Circulo&);
    friend std::ostream& operator<<(std::ostream&, const Circulo&);
};

#endif
