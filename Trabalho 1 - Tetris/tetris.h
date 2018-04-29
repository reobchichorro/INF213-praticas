#ifndef TETRIS_H
#define TETRIS_H

#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;

class Tetris {
    public:
        Tetris(const int c);
        ~Tetris();
        void destroy();

        char get(const int c, const int l) const;
        void removeColuna(const char c);
        void removeLinhasCompletas();
        int getNumColunas() const;
        int getAltura(const int c) const;
        int getAltura() const;
        bool adicionaForma(const int coluna, const int linha, const char id='O', const int rotacao=0);

    private:
        char** jogo;
        int col;
        int* alturas;
};

#endif