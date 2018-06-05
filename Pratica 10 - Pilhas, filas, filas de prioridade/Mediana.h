#ifndef MEDIANA2_H
#define MEDIANA2_H

#include <iostream>
#include "MyPriorityQueue.h"
using namespace std;


class Mediana {
public:
	void insere(int el);
	int getMediana();

private:
	MyPriorityQueue<int> crescente;
	MyPriorityQueue<int> decrescente;
};

#endif