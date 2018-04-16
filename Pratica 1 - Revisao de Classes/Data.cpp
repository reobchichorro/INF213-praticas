#include <iostream>
#include "Data.h"

Data::Data(const int d, const int m, const int a) {
    this->setDia(d);
    this->setMes(m);
    this->setAno(a);
}
Data::Data(const Data &entrada) {
    this->setDia(entrada.getDia());
    this->setMes(entrada.getMes());
    this->setAno(entrada.getAno());
}

void Data::setDia(const int d) {
    this->dia = d;
    if(this->dia < 1)
        this->dia = 1;
    else if(this->dia > 30)
        this->dia = 30;
}
void Data::setMes(const int m) {
    this->mes = m;
    if(this->mes < 1)
        this->mes = 1;
    else if(this->mes > 12)
        this->mes = 12;
}
void Data::setAno(const int a) {
    this->ano = a;
    if(this->ano < 2018)
        this->ano = 2018;
    else if(this->ano > 2020)
        this->ano = 2020;
}

int Data::getDia() const {
    return this->dia;
}
int Data::getMes() const {
    return this->mes;
}
int Data::getAno() const {
    return this->ano;
}

int Data::compData(const Data& parametro) const{

    if( this->getAno() < parametro.getAno() )
        return -1;

    else if( this->getAno() > parametro.getAno() )
        return 1;

    else if( this->getAno() == parametro.getAno() ) {

        if( this->getMes() < parametro.getMes() )
            return -1;

        else if( this->getMes() > parametro.getMes() )
            return 1;

        else if( this->getMes() == parametro.getMes() ) {

            if( this->getDia() < parametro.getDia() )
                return -1;

            else if( this->getDia() > parametro.getDia() )
                return 1;

            else if( this->getDia() == parametro.getDia() ) {
                return 0;
            }
        }
    }

    return -2; //Indica erro
}

int Data::difDias(const Data& parametro) const{
    int thisDiasTotais = 0, parametroDiasTotais = 0;
    if(this->compData(parametro) != 0) {
        thisDiasTotais += 365*this->getAno();
        thisDiasTotais += 30*this->getMes();
        thisDiasTotais += this->getDia();
        parametroDiasTotais += 365*parametro.getAno();
        parametroDiasTotais += 30*parametro.getMes();
        parametroDiasTotais += parametro.getDia();
    }
    return thisDiasTotais - parametroDiasTotais;
}

void Data::imprime() const {
    std::cout << this->getDia() << " " << this->getMes() << " " << this->getAno() << std::endl;
}

std::istream& operator>> (std::istream& is, Data& dt) {
    is >> dt.dia >> dt.mes >> dt.ano;
    return is;
}
std::ostream& operator<< (std::ostream& os, const Data& dt) {
    os << dt.getDia() << " " << dt.getMes() << " " << dt.getAno();
    return os;
}
