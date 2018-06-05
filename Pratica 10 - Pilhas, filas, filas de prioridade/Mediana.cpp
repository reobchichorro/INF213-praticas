#include <iostream>
#include "Mediana.h"
#include <algorithm>
using namespace std;

void Mediana::insere(int el) {
	if(decrescente.size() == 0)
        decrescente.push(-1*el);
    else if(el < -1*decrescente.top())
        crescente.push(el);
    else 
        decrescente.push(-1*el);
    
    if(crescente.size() - decrescente.size() == 2) {
        int elem = crescente.top();
        crescente.pop();
        decrescente.push(-1*elem);
    }
    else if(decrescente.size() - crescente.size() == 2) {
        int elem = -1*decrescente.top();
        decrescente.pop();
        crescente.push(elem);
    }
}

int Mediana::getMediana() {
	if(crescente.size() == decrescente.size())
		return crescente.top()+(-1*decrescente.top())/2;
	else if (crescente.size() > decrescente.size())
		return crescente.top();
	else
        return -1*decrescente.top();
}