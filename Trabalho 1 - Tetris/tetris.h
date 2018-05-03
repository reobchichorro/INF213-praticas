#ifndef TETRIS_H
#define TETRIS_H

#include <iostream>
using std::cout;
using std::endl;

class Tetris {
    public:
        Tetris(const int c);    //Construtor
        ~Tetris();              //Destrutor
        void destroy();         //Funcao que deleta memoria, chamada pelo destrutor
        
        //Metodos get
        int getNumColunas() const;
        int getAltura(const int c) const;
        int getAltura() const;
        int getMenorAltura() const;
        char get(const int c, const int l) const;

        //Metodos que criam e removem linhas e colunas
        void alocarColunaAteAltura(const int c, const int l);
        void removeColuna(const char c);
        bool removeLinhaCompleta(const int l);
        void removeLinhasCompletas();
        bool adicionaForma(const int coluna, const int linha, const char id='O', const int rotacao=0);

    private:
        char** jogo;    //Matriz representando o estado do jogo
        int col;        //Numero total de colunas
        int* alturas;   //Vetor que armazena a altura de cada coluna (altura[i] == 2 indica que existem 2 pecas na coluna)
};

#endif