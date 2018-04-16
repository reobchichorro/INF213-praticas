
#ifndef __FigBase_h
#define __FigBase_h

class FigBase {
private:
    double x, y;
    int espessura; // inteiro de 1 a 5
    int cor;       // inteiro de 1 a 5
    int tipo;      // inteiro de 1 a 3

public:
    FigBase(double, double, int, int, int);

    double getX() const;
    void setX(double);

    double getY() const;
    void setY(double);

    int getEspessura() const;
    void setEspessura(int);

    int getCor() const;
    void setCor(int);

    int getTipo() const;
    void setTipo(int);
    
    void imprime() const;

};

#endif
