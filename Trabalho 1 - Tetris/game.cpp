#include <iostream>
#include "Tetris.h"

using namespace std;

void display(const Tetris mostrar) {
    for(int j=mostrar.getAltura(); j>=-1; j--) {
        for(int i=-1; i<mostrar.getNumColunas()+1; i++) {
            if(i==-1 || j==-1 || i==mostrar.getNumColunas() || j==mostrar.getAltura())
                cout << "|";
            else
                cout << mostrar.get(i, j);
        }
        cout << " " << j << endl;
    }
    
    for(int i=-1; i<mostrar.getNumColunas()+1; i++) {
        if(i==-1 || i==mostrar.getNumColunas())
            cout << " ";
        else
            cout << mostrar.getAltura(i);
    }
    cout << endl << endl;
}

int main() {
    Tetris rodrigo(8);
    
    /*
    bool haha = rodrigo.adicionaForma(1,1,'O',90);
    rodrigo.adicionaForma(2,4,'O',0);
    rodrigo.adicionaForma(4,3,'O',180);
    rodrigo.adicionaForma(2,3,'O',270);
    display(rodrigo);

    rodrigo.adicionaForma(6,5,'I',0);
    rodrigo.adicionaForma(2,4,'I',270);
    rodrigo.adicionaForma(1,2,'I',270);
    rodrigo.adicionaForma(0,4,'Z',90);
    display(rodrigo);
    
    rodrigo.adicionaForma(5,4,'S',270);
    rodrigo.adicionaForma(7,4,'I',0);
    rodrigo.adicionaForma(2,3,'T',0);
    */

    display(rodrigo);
    rodrigo.adicionaForma(0,0,'K',270);
    rodrigo.adicionaForma(4,0,'I',90);
    display(rodrigo);
    rodrigo.removeLinhasCompletas();
    display(rodrigo);
    /*
    rodrigo.removeLinhasCompletas();
    display(rodrigo);

    rodrigo.removeColuna(8);
    rodrigo.removeColuna(7);
    rodrigo.removeColuna(6);
    rodrigo.removeColuna(5);
    rodrigo.removeColuna(4);
    display(rodrigo);
    */
    
    
    rodrigo.destroy();

}
