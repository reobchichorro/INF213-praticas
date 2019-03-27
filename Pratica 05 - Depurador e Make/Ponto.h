#ifndef PONTO_H
#define PONTO_H

//Representa um ponto em 2D

class Ponto {
public:
	Ponto(float x_=0, float y_=0) : x(x_),y(y_) {}
	void setX(float x_);
	void setY(float y_);
	float getX() const;
	float getY() const;
private:
	float x,y;
};

#endif
