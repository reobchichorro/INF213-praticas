#include <iostream>

using namespace std;




#include "MyList2NewIterator.h"

//Etapa 1: Adicione sua implementacao de "reverse" antes da funcao "testaReverse"
template<class T>
void reverse(MyList2<T>& list) {
	MyList2Iterator<T> left = list.begin(), right = list.begin();
	for(int i=0; i<list.size()-1; right++, i++);

	for(int i=0; i<list.size()/2; left++, right--, i++) {
		swap(*left, *right);
	}
}

void testaReverse() {
	cout << "Testando a funcao reverse..." << endl;
	MyList2<int> l1;

	for(int i=0;i<6;i++) {
		MyList2<int> l2 = l1;
		reverse(l2);
		cout << "Lista: " << endl << l1 << " Reverse: " << endl << l2 << endl << "--------------" << endl;
		l1.push_back(i);
	}
}

//Etapa 2: descomente o codigo abaixo para testar a sua implementacao da operacao de decremento do 
//iterador end...

//imprime de forma reversa utilizando o iterador end...

void printReverse(MyList2<int> &l1) { 
	//nao passamos por referencia constante porque nao nos preocupamos com iteradores constantes
	//na implementacao da classe MyList2 (sem esses iteradores nao podemos iterar em listas constantes,
	//visto que um iterador pode modificar a lista com a operacao de derreferencia)
	MyList2<int>::iterator it = l1.end();
	if(it!=l1.begin()) { //lista nao vazia...
		do {
			it--;
			cout << *it << " ";
		} while(it!=l1.begin());
	}
	cout << endl;
}

void testaDecrementoEnd() {
	cout << "Testando o decremento do iterador end()" << endl;
	MyList2<int> l1;

	for(int i=0;i<6;i++) {
		printReverse(l1);
		l1.push_back(i);
	}

	//e se criarmos um iterador para end() e inserirmos algo antes do end(), o decremento
	//vai acessar o novo valor corretamente?
	MyList2<int>::iterator it = l1.end();
	l1.insert(6,l1.end());
	it--;
	cout << "Isso deve imprimir o numero 6...: " << *it << endl;
	it--;
	cout << "Isso deve imprimir o numero 5...: " << *it << endl;

}


//Etapa 3: descomente o codigo abaixo para testar sua implementacao da classe Range...
/*#include "Range.h"
void testaRange() {
	cout << "Testando a classe Range..." << endl;
	Range range(1,5);
	Range::iterator it = range.begin();
	while(it!=range.end()) {
		cout << *it << endl;
		++it;
	}

	cout << endl;
	for(int i:Range(1,5)) cout << i << endl;
}*/


int main() {
	//Etapa 1: implemente a funcao reverse()
	testaReverse();

	//Etapa 2: descomente o codigo abaixo (mantenha o codigo da etapa 1 descomentado...)
	testaDecrementoEnd();

	//Etapa 3: descomente o codigo abaixo (mantenha o codigo das etapas 1 e 2 descomentado...)
	//testaRange();
}

/* Saida esperada apos a implementacao das 3 etapas:

Testando a funcao reverse...
Lista: 
Size: 0

 Reverse: 
Size: 0


--------------
Lista: 
Size: 1
0 
 Reverse: 
Size: 1
0 

--------------
Lista: 
Size: 2
0 1 
 Reverse: 
Size: 2
1 0 

--------------
Lista: 
Size: 3
0 1 2 
 Reverse: 
Size: 3
2 1 0 

--------------
Lista: 
Size: 4
0 1 2 3 
 Reverse: 
Size: 4
3 2 1 0 

--------------
Lista: 
Size: 5
0 1 2 3 4 
 Reverse: 
Size: 5
4 3 2 1 0 

--------------
Testando o decremento do iterador end()

0 
1 0 
2 1 0 
3 2 1 0 
4 3 2 1 0 
Isso deve imprimir o numero 6...: 6
Isso deve imprimir o numero 5...: 5
Testando a classe Range...
1
2
3
4
5

1
2
3
4
5
*/