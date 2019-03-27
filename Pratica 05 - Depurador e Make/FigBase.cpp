
#include "FigBase.h"


FigBase::FigBase(const Ponto &p) {
	p0 = p;
}

const Ponto &FigBase::getP0() const {
	return p0;
}

void FigBase::setP0(const Ponto &p) {
	p0 = p;
}

