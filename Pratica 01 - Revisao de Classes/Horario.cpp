#include <iostream>
#include "Horario.h"



Horario::Horario(const int h, const int m, const int s) {
    this->setHora(h);
    this->setMinuto(m);
    this->setSegundo(s);
}
Horario::Horario(const Horario &entrada) {
    this->setHora(entrada.getHora());
    this->setMinuto(entrada.getMinuto());
    this->setSegundo(entrada.getSegundo());
}

void Horario::setHora(const int h) {
    this->hora = h;
    if(this->hora < 0)
        this->hora = 0;
    else if(this->hora >= 24)
        this->hora = 23;
}
void Horario::setMinuto(const int m) {
    this->minuto = m;
    if(this->minuto < 0)
        this->minuto = 0;
    else if(this->minuto >= 60)
        this->minuto = 59;
}
void Horario::setSegundo(const int s) {
    this->segundo = s;
    if(this->segundo < 0)
        this->segundo = 0;
    else if(this->segundo >= 60)
        this->segundo = 59;
}

int Horario::getHora() const {
    return this->hora;
}
int Horario::getMinuto() const {
    return this->minuto;
}
int Horario::getSegundo() const {
    return this->segundo;
}

int Horario::compHorario(const Horario& parametro) const{

    if( this->getHora() < parametro.getHora() )
        return -1;

    else if( this->getHora() > parametro.getHora() )
        return 1;

    else if( this->getHora() == parametro.getHora() ) {

        if( this->getMinuto() < parametro.getMinuto() )
            return -1;

        else if( this->getMinuto() > parametro.getMinuto() )
            return 1;

        else if( this->getMinuto() == parametro.getMinuto() ) {

            if( this->getSegundo() < parametro.getSegundo() )
                return -1;

            else if( this->getSegundo() > parametro.getSegundo() )
                return 1;

            else if( this->getSegundo() == parametro.getSegundo() ) {
                return 0;
            }
        }
    }

    return -2; //Indica erro
}

int Horario::difSegundos(const Horario& parametro) const{
    int thisSegundosTotais = 0, parametroSegundosTotais = 0;
    if(this->compHorario(parametro) != 0) {
        thisSegundosTotais += 365*this->getHora();
        thisSegundosTotais += 30*this->getMinuto();
        thisSegundosTotais += this->getSegundo();
        parametroSegundosTotais += 365*parametro.getHora();
        parametroSegundosTotais += 30*parametro.getMinuto();
        parametroSegundosTotais += parametro.getSegundo();
    }
    return thisSegundosTotais - parametroSegundosTotais;
}

void Horario::imprime() const {
    std::cout << this->getHora() << " " << this->getMinuto() << " " << this->getSegundo() << std::endl;
}

std::istream& operator>> (std::istream& is, Horario& hro) {
    is >> hro.hora >> hro.minuto >> hro.segundo;
    return is;
}
std::ostream& operator<< (std::ostream& os, const Horario& hro) {
    os << hro.getHora() << " " << hro.getMinuto() << " " << hro.getSegundo();
    return os;
}
