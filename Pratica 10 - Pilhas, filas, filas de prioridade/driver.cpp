#include <iostream>
#include <string>

using namespace std;


// Insira aqui o codigo para a etapa 1....

//Voce pode adicionar includes como o abaixo...
#include "MyStack.h"
#include "MyQueue.h"


void etapa1() {
	MyStack<int> pilha;
	MyQueue<int> fila;

	int numeros[6];
	for(int i=0; i<6; i++) {
		cin >> numeros[i];
		pilha.push(numeros[i]);
		fila.push(numeros[i]);
	}
	for(int i=0; i<6; i++) {
		cout << pilha.top() << " ";
		pilha.pop();
	}
	cout << endl;
	for(int i=0; i<6; i++) {
		cout << fila.front() << " ";
		fila.pop();
	}
	cout << endl;
}

//---------------------------------------

// Insira aqui o codigo para a etapa 2....

void etapa2() {
	MyStack<char> simbolos;
	string entrada;

	cin >> entrada;
	bool consistente = true;

	for(int i=0; entrada[i] != '\0' && consistente; i++) {
		if(entrada[i] == '(' || entrada[i] == '[' || entrada[i] == '{')
			simbolos.push(entrada[i]);
		else if(entrada[i] == ')') {
			if(!simbolos.empty()) { 
				consistente = (simbolos.top() == '(');
				simbolos.pop();
			}
			else consistente = false;
		}
		else if(entrada[i] == ']') {
			if(!simbolos.empty()) { 
				consistente = (simbolos.top() == '[');
				simbolos.pop();
			}
			else consistente = false;
		}
		else if(entrada[i] == '}') {
			if(!simbolos.empty()) { 
				consistente = (simbolos.top() == '{');
				simbolos.pop();
			}
			else consistente = false;
		}
	}

	if(consistente) cout << "Consistente";
	else cout << "Inconsistente";
	cout << endl;
}

//---------------------------------------

// Insira aqui o codigo para a etapa 3....

#include "Mediana.h" //descomente esta linha para utilizar sua classe mais eficiente!
void etapa3() {
	//descomente o codigo abaixo ao fazer a etapa 3
	Mediana mediana;

	int n,elem;	
	cin >> n;
	for(int i=0;i<n;i++) {
		cin >> elem;
		mediana.insere(elem);
		cout << mediana.getMediana() << " ";
	}
	cout << endl;
}

//---------------------------------------




int main() {
	int etapa;
	cin >> etapa;
	switch(etapa) {
		case 1:
			cout << "Etapa 1" << endl;
			etapa1();
			break;
		case 2:
			cout << "Etapa 2" << endl;
			etapa2();
			break;
		case 3:
			cout << "Etapa 3" << endl;
			etapa3();
			break;
	}
}