#include <iostream>
#include "tetris.h"

using namespace std;

void display(const Tetris& mostrar) {
    for(int j=mostrar.getAltura(); j>=-1; j--) {
        for(int i=-1; i<mostrar.getNumColunas()+1; i++) {
            if(i==-1 || j==-1 || i==mostrar.getNumColunas() || j==mostrar.getAltura())
                cout << "|";
            else
                cout << mostrar.get(i, j);
        }
        cout << endl;
    }
}

int main() {
    Tetris rodrigo(8);
    display(rodrigo);
    cout << endl;
    bool haha = rodrigo.adicionaForma(0,1,'O',0);
    //cout << rodrigo.get(0, 1) << rodrigo.get(1, 1) << endl;
    //cout << rodrigo.get(0, 0) << rodrigo.get(1, 0) << endl;
    display(rodrigo);
    cout << endl;
    rodrigo.adicionaForma(0,4,'O',0);
    display(rodrigo);
    cout << endl;
    rodrigo.adicionaForma(6,4,'O',0);
    rodrigo.adicionaForma(4,3,'O',0);
    display(rodrigo);
    cout << endl;
    rodrigo.removeColuna(7);
    display(rodrigo);
    cout << endl;
    rodrigo.removeLinhasCompletas();
    display(rodrigo);
    cout << endl;
}