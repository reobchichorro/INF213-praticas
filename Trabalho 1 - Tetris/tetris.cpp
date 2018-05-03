#include <iostream>
#include <string>
#include "tetris.h"

Tetris::Tetris(const int c) {
    jogo = new char*[c];
    col = c;
    alturas = new int[c];
    for(int i=0; i<c; i++)
        alturas[i] = 0;
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

void Tetris::alocarColunaAteAltura(const int c, const int l) {
    int alturaDaColuna = getAltura(c);
    if(l < alturaDaColuna)
        return;

    char* temp = new char[l];
    for(int i=0; i<alturaDaColuna; i++)
        temp[i] = jogo[c][i];
    for(int i=alturaDaColuna; i<l; i++)
        temp[i] = ' ';

    alturas[c] = l;

    if(alturaDaColuna != 0)
        delete[] jogo[c];
    jogo[c] = temp;
    temp = NULL;
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

bool Tetris::removeLinhaCompleta(const int l) {
    for(int i=0; i<col; i++)
        if(get(i, l) == ' ')
            return false;
        
    char** temp = new char*[col];
    for(int i=0; i<col; i++) {
        temp[i] = new char[getAltura(i) - 1];
        for(int j=0; j < getAltura(i)-1; j++) {
            if(j < l)
                temp[i][j] = jogo[i][j];
            else
                temp[i][j] = jogo[i][j+1];
        }
        
        delete[] jogo[i];
        alturas[i]--;
    }
    delete[] jogo;
    jogo = temp;
    temp = NULL;
    return true;
}

void Tetris::removeLinhasCompletas() {
    for(int i=0; i < getMenorAltura(); i++)
        if(removeLinhaCompleta(i))
            i--;
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

int Tetris::getMenorAltura() const {
    int menorAltura = getAltura(0);
    for(int i=1; i<col; i++)
        if(getAltura(i) < menorAltura)
            menorAltura = getAltura(i);
    return menorAltura;
}

bool Tetris::adicionaForma(const int coluna, const int linha, const char id, const int rotacao) {
    if(0 <= coluna && coluna < getNumColunas() - 1) {
        if(1 <= linha) {
            bool ehValido = get(coluna, linha) == ' ';
            //cout << ehValido << endl;
            ehValido = ehValido && get(coluna+1, linha);
            ehValido = ehValido && get(coluna, linha-1);
            ehValido = ehValido && get(coluna+1, linha-1);

            if(ehValido) {
                for(int i=coluna; i<=coluna+1; i++) {
                    for(int j=linha; j>=linha-1; j--) {
                        if(j<=getAltura(i)) {
                            jogo[i][j] = id;
                            //cout << "Teste " << i << " " << j << " " << jogo[i][j] << endl;
                        }
                        else {
                            alocarColunaAteAltura(i, j+1);
                            jogo[i][j] = id;
                            //cout << "Teste2 " << i << " " << j << " " << jogo[i][j] << " " << getAltura(i) << endl;
                        }
                        
                    }
                }
            }
            return ehValido;
            /*
            for(int j=linha; j<getAltura(coluna); j--)
                if(get(coluna, j) != ' ') return false;
            */

        }
        return false;
    }
    return false;
}