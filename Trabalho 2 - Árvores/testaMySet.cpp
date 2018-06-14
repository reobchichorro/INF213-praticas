#include <iostream>
#include "MySet.h"

using namespace std;

void procura(MySet<int> &s, int elem) {
	cout << "Procurando " << elem << " : " << (s.find(elem)!=s.end()) << endl;
}

void insere(MySet<int> &s, int elem) {
	pair<MySetIterator<int>,bool> teste = (s.insert(elem));
	cout << "Inserindo " << elem << " : " << (teste.second) << endl;
}


int main() {
	MySet<int> s;
	insere(s,1);
	insere(s,2);
	insere(s,10);
	insere(s,10); //repetidos..
	insere(s,10); //repetidos..
	insere(s,1);

	procura(s,1);
	procura(s,2);
	procura(s,10);
	procura(s,20);
	procura(s,-1);


	procura(s,1);
	procura(s,2);
	procura(s,10);
	procura(s,24);

	insere(s,-10);
	insere(s,-20);
	insere(s,-5);
	insere(s,5);
	insere(s,30);

	cout << "Procurando.." << endl;
	procura(s,1);
	procura(s,2);
	procura(s,10);
	procura(s,24);
	procura(s,-10);
	procura(s,-20);
	procura(s,-5);
	procura(s,5);
	procura(s,30);	


	procura(s,1);
	procura(s,2);
	procura(s,10);
	procura(s,24);
	procura(s,-10);
	procura(s,-20);
	procura(s,-5);
	procura(s,5);
	procura(s,30);	

	MySet<int> s2 = s;
	MySet<int> s3 ;
	int x;
	s2 = s;
	s3.insert(123);
	procura(s,123);
	procura(s3,123);

}