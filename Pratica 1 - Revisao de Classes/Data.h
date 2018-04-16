#ifndef DATA_H
#define DATA_H

#include <iostream>

class Data{
    private:
        int dia;
        int mes;
        int ano;

    public:
        Data(const int d=1, const int m=1, const int a=2018);
        Data(const Data &);
        void setDia(const int d);
        void setMes(const int m);
        void setAno(const int a);
        int getDia() const;
        int getMes() const;
        int getAno() const;
        int compData(const Data&) const;
        int difDias(const Data&) const;
        void imprime() const;
        friend std::istream& operator>>(std::istream&, Data&);
        friend std::ostream& operator<<(std::ostream&, const Data&);
};

#endif
