#include <iostream>
#include "MySet.h"

using namespace std;

int main() {
    char operacao;
    int numero;
    MySet<int> bancoDeDados;
    while(cin >> operacao) {
        cin >> numero;
        if(operacao == 'C') bancoDeDados.insert(numero);
        else if(operacao == 'S') {
            MySetIterator<int> aux = bancoDeDados.find(numero);
            if(aux == NULL) cout << "FALHA" << endl;
            else {
                aux++;
                if(aux == NULL) cout << "FALHA" << endl;
                else cout << *aux << endl;
            }
        }
    }
    return 0;
}