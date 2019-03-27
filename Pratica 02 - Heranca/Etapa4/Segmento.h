#ifndef __Segmento_h
#define __Segmento_h

#include "FigBase.h"

class Segmento : public FigBase {
private:
    double x2, y2;

public:
    Segmento(double, double, double, double, int, int, int);
    Segmento();

    double getX2() const;
    void setX2(double);

    double getY2() const;
    void setY2(double);
    
    float area() const;
    float perimetro() const;

    void le(std::istream&); 
    void imprime() const;

    friend std::istream& operator>>(std::istream&, Segmento&);
    friend std::ostream& operator<<(std::ostream&, const Segmento&);
};

#endif