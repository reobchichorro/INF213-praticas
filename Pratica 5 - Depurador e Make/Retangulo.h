
#ifndef __RETANGULO_H
#define __RETANGULO_H

#include "FigBase.h"

//Um retangulo e' definido usando dois pontos extremos.
//Por simplicidade, supomos que p1 esta acima e a direita de p0 (nao fazemos qualquer tratamento de erros)
class Retangulo : public FigBase {

private:
    Ponto p1;

public:
    Retangulo(const Ponto &p0, const Ponto &p1);

    const Ponto &getP1() const;
    void setP1(const Ponto &p1);
    
    bool contem(const Ponto &p) const;
};

#endif
