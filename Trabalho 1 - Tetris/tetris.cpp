#include <iostream>
#include <string>
#include "tetris.h"

Tetris::Tetris(const int c) {
    jogo = new char*[c];
    col = c;
    alturas = new int[c];
}

Tetris::~Tetris() {
    destroy();
    col=0;
}

void Tetris::destroy() {
    delete[] alturas;
    for(int i=0; i<col; i++)
        delete[] jogo[i];
    delete[] jogo;
}

char Tetris::get(const int c, const int l) const {
    if(0 <= c && c < col)
        if(0 <= l && l < getAltura(c))
            return jogo[c][l];
    return ' ';
}

void Tetris::removeColuna(const char c) {
    if(0 <= c && c < col) {
        char** temp = new char*[col-1];
        int* alturasTemp = new int[col-1];
        for(int i=0; i<col-1; i++) {
            if(i < c) {
                alturasTemp[i] = getAltura(i);
                temp[i] = new char[alturasTemp[i]];
                for(int j=0; j<alturasTemp[i]; j++)
                    temp[i][j] = jogo[i][j];
            }
            else {
                alturasTemp[i] = getAltura(i+1);
                temp[i] = new char[alturasTemp[i]];
                for(int j=0; j<alturasTemp[i]; j++)
                    temp[i][j] = jogo[i+1][j];
            }
        }

        destroy();
        col--;
        jogo = temp;
        alturas = alturasTemp;
        temp = NULL;
        alturasTemp = NULL;
    }
}

void Tetris::removeLinhasCompletas() {
    while(true) {
        for(int i=0; i<col; i++)
            if(getAltura(i) == 0 || get(i, 0) == ' ')
                return;
        
        char** temp = new char*[col];
        for(int i=0; i<col; i++) {
            temp[i] = new char[getAltura(i) - 1];
            for(int j=0; j < getAltura(i)-1; j++)
                temp[i][j] = jogo[i][j+1];
            
            delete[] jogo[i];
            alturas[i]--;
        }
        delete[] jogo;
        jogo = temp;
    }
}

int Tetris::getNumColunas() const {
    return col;
}

int Tetris::getAltura(const int c) const {
    if(0<=c && c<col)
        return alturas[c];
}

int Tetris::getAltura() const {
    int maiorAltura=0;
    
    for(int i=0; i<col; i++)
        if(getAltura(i) > maiorAltura)
            maiorAltura = getAltura(i);

    return maiorAltura;
}

bool Tetris::adicionaForma(const int coluna, const int linha, const char id, const int rotacao) {
    if(0 <= coluna && coluna < getNumColunas() - 1) {
        if(1 <= linha) {
            for(int i=coluna; i<=coluna+1; i++) {
                for(int j=linha; j>=linha-1; j--) {
                    if(j<=getAltura(i)) {
                        if(get(i, j) != ' ') 
                            return false;
                    }
                    
                }
            }
            /*
            for(int j=linha; j<getAltura(coluna); j--)
                if(get(coluna, j) != ' ') return false;
            */

        }
        return false;
    }
    return false;
}