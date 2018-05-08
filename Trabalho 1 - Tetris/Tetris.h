#ifndef TETRIS_H
#define TETRIS_H

#include <iostream>
using std::cout;
using std::endl;

class Tetris {
    public:
        Tetris(const int c=0);  //Construtor. Caso o usuario nao especifique o numero de colunas, utiliza-se 0 colunas.
        ~Tetris();              //Destrutor.
        void destroy();         //Funcao que deleta memoria, chamada pelo destrutor.
        Tetris(const Tetris&);  //Construtor de copia.
        Tetris& operator=(const Tetris&);   //Sobrecarga do operador =.
        
        //Metodos get:
        int getNumColunas() const;
        int getAltura(const int c) const;
        int getAltura() const;
        int getMenorAltura() const;
        char get(const int c, const int l) const;

        //Metodos que criam e removem linhas e colunas:
        void alocarColunaAteAltura(const int c, const int l);
        void removeColuna(const char c);
        bool removeLinhaCompleta(const int l);
        void removeLinhasCompletas();
        bool adicionaForma(const int coluna, const int linha, const char id, const int rotacao);

    private:
        char** jogo;    //Matriz representando o estado do jogo.
        int col;        //Numero total de colunas.
        int* alturas;   //Vetor que armazena a altura de cada coluna (alturas[i] == 2 indica que existem 2 pecas na coluna).
};

#endif