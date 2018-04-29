#include <iostream>
#include <string>
#include "tetris.h"

Tetris::Tetris(const int c) {
    jogo = new char*[c];
    col = c;
    alturas = new int[c];
}

Tetris::~Tetris() {
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
        for(int i=0; i<col-1; i++) {
            if(i < c) {
                temp[i] = new char[getAltura(i)];
                for(int j=0; j<getAltura(i); j++)
                    temp[i][j] = jogo[i][j];
            }
            else {
                temp[i] = new char[getAltura(i+1)];
                for(int j=0; j<getAltura(i+1); j++)
                    temp[i][j] = jogo[i+1][j];
            }
        }

        for(int i=0; i<col; i++)
            delete[] jogo[i];
        delete[] jogo;
        col--;
        jogo = temp;
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
        }
        delete[] jogo;
        jogo = temp;
    }
}

int Tetris::getNumColunas() const {
    return col;
}
/*
class Tetris {
    public:
        Tetris(const int c);
        char get(const int c, const int l) const;
        void removeColuna(const char c);
        void removeLinhasCompletas();
        int getNumColunas() const { return col; };
        int getAltura(const int c) const;
        int getAltura() const;
        bool adicionaForma(const int coluna, const int linha, const char id, const int rotacao);

    private:
        char** jogo;
        int col;
        int* alturas;
};
*/