
#ifndef __FIG_BASE_H
#define __FIG_BASE_H

#include <iostream>
#include "Ponto.h"


class FigBase {

protected:
    Ponto p0; //toda figura tem pelo menos um ponto base

public:
    FigBase(const Ponto &p);

    const Ponto& getP0() const;
    void setP0(const Ponto &);

    virtual bool contem(const Ponto &p) const = 0; //dado um ponto p, verifica se p esta no interior da figura
    																					 //pontos exatamente na borda da figura nao sao considerados
    																					 //como pertencendo ao interior
};

#endif
