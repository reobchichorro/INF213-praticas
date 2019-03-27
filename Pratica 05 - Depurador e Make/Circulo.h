
#ifndef __CIRCULO_H
#define __CIRCULO_H

#include "FigBase.h"
#include <iostream>


class Circulo : public FigBase {

private:
    double raio;

public:
    Circulo(const Ponto &p, float raio);

    void setRaio(float r);
    float getRaio() const;
    
    bool contem(const Ponto &p) const;
};

#endif
