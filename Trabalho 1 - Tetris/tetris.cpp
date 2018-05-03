#include <iostream>
#include <string>
#include "tetris.h"

Tetris::Tetris(const int c) {
    col = c;
    jogo = new char*[c];
    alturas = new int[c];

    for(int i=0; i<c; i++) {
        alturas[i] = 0; //Nao ha nenhum pixel.
        jogo[i] = NULL;
    }
}

Tetris::~Tetris() {
    destroy();
    col=0;  //Operacao que nao e' realizada por destroy().
}

void Tetris::destroy() {    //Destroi jogo** e altura*, mas mantem o valor de col.
    delete[] alturas;
    for(int i=0; i<getNumColunas(); i++)
        delete[] jogo[i];
    delete[] jogo;
}

Tetris::Tetris(const Tetris& other) {
    *this = other;
}

Tetris& Tetris::operator=(const Tetris& other) {
    if(&other==this) 
        return *this;

    col = other.getNumColunas();
    jogo = new char*[other.getNumColunas()];
    alturas = new int[other.getNumColunas()];

    for(int i=0; i<other.getNumColunas(); i++) {
        alturas[i] = other.getAltura(i);
        jogo[i] = new char[other.getAltura(i)];
        
        for(int j=0; j<other.getAltura(i); j++)
            jogo[i][j] = other.get(i,j);
    }
    
	return *this;
}

int Tetris::getNumColunas() const {
    return col;
}

int Tetris::getAltura(const int c) const {
    if(0<=c && c<getNumColunas())   //Caso a coluna pedida exista,
        return alturas[c];      //retornamos sua altura, que a posicao do pixel mais alto da coluna.
}

int Tetris::getAltura() const { //Retorna a maior altura.
    int maiorAltura=getAltura(0);
    
    for(int i=1; i<getNumColunas(); i++)
        if(getAltura(i) > maiorAltura)
            maiorAltura = getAltura(i);

    return maiorAltura;
}

int Tetris::getMenorAltura() const {    //Retorna a menor altura.
    int menorAltura = getAltura(0);

    for(int i=1; i<col; i++)
        if(getAltura(i) < menorAltura)
            menorAltura = getAltura(i);

    return menorAltura;
}

char Tetris::get(const int c, const int l) const {
    if(0 <= c && c < getNumColunas())   //Os condicionais verificam se a posicao de jogo** requisitada esta alocada.
        if(0 <= l && l < getAltura(c))
            return jogo[c][l];  //Se sim, retornamos o pixel requisitado.
    
    return ' '; //Caso contrario, retornamos um espaco vazio.
}

void Tetris::alocarColunaAteAltura(const int c, const int l) {
    if(l < getAltura(c))    //Caso a altura nova seja menor do que altura antiga, nao precisamos alocar nada.         
        return;

    char* temp = new char[l+1];   //Variavel temporaria que armazena os novos valores da coluna.
    for(int j=0; j<getAltura(c); j++)   //Ate a altura antiga, usamos os valores antigos da coluna.
        temp[j] = jogo[c][j];
    for(int j=getAltura(c); j<l; j++)   //Dai em diante, preenchemos com espacos em branco.
        temp[j] = ' ';

    alturas[c] = l;     //Passamos l como a nova altura.

    delete[] jogo[c];   //Deletamos a coluna antiga.
    jogo[c] = temp;     //Passamos para jogo[c] a nova coluna armazenada em temp.
    temp = NULL;        
}

void Tetris::removeColuna(const char c) {
    if(0 <= c && c < getNumColunas()) {
        char** temp = new char*[getNumColunas()-1];     //Armazena temporiamente os novos valores de jogo**.
        int* alturasTemp = new int[getNumColunas()-1];  //Armazena temporiamente os novos valores de alturas*.

        for(int i=0; i<getNumColunas()-1; i++) {    //Iteramos ate o novo numero de colunas, que e' (numero antigo - 1).
            if(i < c) {                             //Caso estejamos antes da coluna que sera removida, pegamos os mesmos valores.
                alturasTemp[i] = getAltura(i);
                temp[i] = new char[alturasTemp[i]];
                for(int j=0; j<alturasTemp[i]; j++)
                    temp[i][j] = jogo[i][j];
            } else {                                //Caso contrario, pegamos os valores da coluna seguinte, ja que, 
                alturasTemp[i] = getAltura(i+1);    //se removermos a coluna 4, por exemplo, a nova coluna 4 sera a antiga coluna 5.  
                temp[i] = new char[alturasTemp[i]];
                for(int j=0; j<alturasTemp[i]; j++)
                    temp[i][j] = jogo[i+1][j];
            }
        }

        destroy();      //Destruimos jogo** e alturas* antigos.
        jogo = temp;    //Passamos os novos valores de jogo** .
        col--;          //Novo numero de colunas.
        alturas = alturasTemp;  //Novas alturas.
        temp = NULL;
        alturasTemp = NULL;
    }
}

bool Tetris::removeLinhaCompleta(const int l) { 
    //Caso a linha l esteja completa, ela sera removida.
    //A funcao retorna true se a linha for removida, e false caso contrario.
    for(int i=0; i<getNumColunas(); i++)
        if(get(i, l) == ' ')    //Caso algum valor da linha for vazio, a linha nao esta completa,
            return false;       //logo ela nao pode  ser deletada.
        
    char** temp = new char*[getNumColunas()];   //Armazena temporariamente o novo estado do jogo.
    int* alturasTemp = new int[getNumColunas()];  //Armazena temporiamente os novos valores de alturas*.

    for(int i=0; i<getNumColunas(); i++) {
        alturasTemp[i] = getAltura(i)-1;
        temp[i] = new char[alturasTemp[i]];   //A nova altura sera (altura antiga - 1), ja que vamos remover uma linha.

        for(int j=0; j < alturasTemp[i]; j++) {
            if(j < l)                           //Enquanto estivermos antes da linha que sera removida,
                temp[i][j] = jogo[i][j];        //pegamos o valor antigo.
            else                                //Mas a partir da linha removida pegamos a linha seguinte, ja que,
                temp[i][j] = jogo[i][j+1];      //se removermos a linha 2, por exemplo, a nova linha 2 sera a antiga linha 3.
        }     
    }

    destroy();      //Destruimos os valores antigos de jogo** e alturas*,
    jogo = temp;    //e atribuimos os novos.
    alturas = alturasTemp;
    temp = NULL;
    alturasTemp = NULL;
    return true;
}

void Tetris::removeLinhasCompletas() {
    //Itera sobre todas as linhas e tenta remove-las.
    //So precisamos iterar ate a menor altura, ja que nao teremos nenhuma linha completa a partir disso.
    for(int j=0; j < getMenorAltura(); j++)
        if(removeLinhaCompleta(j))  //Tentamos remover a linha.
            j--;    //Caso a linha seja removida, voltamos uma iteracao, ja que, se removermos a linha 2, por exemplo,
                    //a linha 3 se tornara a nova linha 2. Caso nao facamos j--, essa linha sera pulada.
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
                        if(j<getAltura(i)) {
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