#ifndef HORARIO_H
#define HORARIO_H

#include <iostream>

class Horario{
    private:
        int hora;
        int minuto;
        int segundo;

    public:
        Horario(const int h=0, const int m=0, const int s=0);
        Horario(const Horario &);
        void setHora(const int h);
        void setMinuto(const int m);
        void setSegundo(const int s);
        int getHora() const;
        int getMinuto() const;
        int getSegundo() const;
        int compHorario(const Horario&) const;
        int difSegundos(const Horario&) const;
        void imprime() const;
        friend std::istream& operator>>(std::istream&, Horario&);
        friend std::ostream& operator<<(std::ostream&, const Horario&);
};

#endif
