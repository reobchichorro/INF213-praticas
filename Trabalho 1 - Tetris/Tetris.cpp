#include <iostream>
#include <string>
#include "Tetris.h"

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
}

void Tetris::destroy() {    //Destroi jogo** e altura* e coloca o numero de colunas como 0.
    if(getNumColunas() != 0) {
        delete[] alturas;
        for(int i=0; i<getNumColunas(); i++)
            delete[] jogo[i];
        delete[] jogo;
    }
    col=0;
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
    //if(c==2 && l==4) cout << "rola " << getNumColunas() << " " << getAltura(c) << endl; 
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
                if(alturasTemp[i] != 0) {
                    temp[i] = new char[alturasTemp[i]];
                    for(int j=0; j<alturasTemp[i]; j++)
                        temp[i][j] = jogo[i][j];
                } 
                else temp[i] = NULL; 
            } else {                                //Caso contrario, pegamos os valores da coluna seguinte, ja que, 
                alturasTemp[i] = getAltura(i+1);    //se removermos a coluna 4, por exemplo, a nova coluna 4 sera a antiga coluna 5.  
                temp[i] = new char[alturasTemp[i]];
                for(int j=0; j<alturasTemp[i]; j++)
                    temp[i][j] = jogo[i+1][j];
            }
        }
        int colunas = getNumColunas() - 1;
        destroy();      //Destruimos jogo** e alturas* antigos.
        jogo = temp;    //Passamos os novos valores de jogo** .
        col = colunas;  //Novo numero de colunas.
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

        bool colunaVazia = true;
        for(int j=0; j < alturasTemp[i]; j++) {
            if(j < l)                           //Enquanto estivermos antes da linha que sera removida,
                temp[i][j] = jogo[i][j];        //pegamos o valor antigo.
            else                                //Mas a partir da linha removida pegamos a linha seguinte, ja que,
                temp[i][j] = jogo[i][j+1];      //se removermos a linha 2, por exemplo, a nova linha 2 sera a antiga linha 3.
            if(temp[i][j] != ' ') colunaVazia = false;
        }
        if(colunaVazia) {
            delete[] temp[i];
            temp[i] = NULL;
            alturasTemp[i] = 0;
        }     
    }

    int colunas = getNumColunas();
    destroy();      //Destruimos os valores antigos de jogo** e alturas*,
    col = colunas;
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
    if(rotacao%90 != 0 || rotacao < 0) return false;    //Nao sera possivel adicionar a peca caso a rotacao seja invalida.
    
    //Fase 1: Criar uma matriz representando a peca que sera adicionada. 
    //O tamanho da matriz sera o mais compacto possivel para armazenar a peca.
    char** peca;
    int largura, altura;    //Guardam a altura e a largura da peca. Essas variaveis serao usadas/relevantes durante toda a funcao.
    if(id == 'O') {         //Os condicionais tratam cada um dos possiveis ids, criando a peca com a largura e altura corretas e a preenche de acordo com a especificacao.
        largura = altura = 2;
        peca = new char*[largura];
        peca[0] = new char[altura];
        peca[1] = new char[altura];
        peca[0][0] = peca[0][1] = peca[1][0] = peca[1][1] = id;
    } else if(id == 'I') {
        largura = 1; altura = 4;
        peca = new char*[largura];
        peca[0] = new char[altura];
        peca[0][0] = peca[0][1] = peca[0][2] = peca[0][3] = id;
    } else if(id == 'J') {
        largura = 4; altura = 2;
        peca = new char*[largura];
        for(int i=0; i<largura; i++) {
            peca[i] = new char[altura];
            peca[i][0] = id;
            peca[i][1] = ' ';
        }
        peca[3][1] = 'J';
    } else if(id == 'L') {
        largura = 4; altura = 2;
        peca = new char*[largura];
        for(int i=0; i<largura; i++) {
            peca[i] = new char[altura];
            peca[i][0] = id;
            peca[i][1] = ' ';
        }
        peca[0][1] = 'L';
    } else {    //As pecas de id Z, S e T teraoa o mesmo tamanho, logo, para a alocacao de memoria, as tres estao sendo contempladas no mesmo condicional. 
        largura = 3; altura = 2;
        peca = new char*[largura];
        for(int i=0; i<largura; i++)
            peca[i] = new char[altura];

        if(id == 'S') {
            peca[0][0] = peca[2][1] = ' ';
            peca[0][1] = peca[1][0] = peca[1][1] = peca[2][0] = id;
        } else if(id == 'T') {
            peca[0][1] = peca[2][1] = ' ';
            peca[0][0] = peca[1][0] = peca[1][1] = peca[2][0] = id;
        } else if(id == 'Z') {
            peca[0][1] = peca[2][0] = ' ';
            peca[0][0] = peca[1][0] = peca[1][1] = peca[2][1] = id;
        } else {    //Caso o programa chegue neste condicional, significa que o id passado como parametro e' invalido.
            for(int i=0; i<largura; i++)
                delete[] peca[i];
            delete[] peca;
            return false; //Caractere invalido
        }
    }

    //Fase 2: Rotacionar a peca
    int rotacaoPeca = 0;    //Guarda a rotacao atual da peca
    while(rotacaoPeca != rotacao) {
        char** novaPeca = new char*[altura];
        for(int j=0; j<altura; j++)
            novaPeca[j] = new char[largura];

        for(int j=0; j<altura; j++)
            for(int i=0; i<largura; i++) 
                novaPeca[j][i] = peca[i][altura-1-j]; 

        for(int i=0; i<largura; i++)
            delete[] peca[i];
        delete[] peca;
        peca = novaPeca;
        novaPeca = NULL;

        int temp = largura;
        largura = altura;
        altura = temp;
        rotacaoPeca+=90;
    }
    
    if(0 <= coluna && coluna <= getNumColunas() - largura) {
        if(altura-1 <= linha) {
            bool ehValido = true;
            for(int i=0; i<largura && ehValido; i++)
                for(int j=altura-1; j>=0 && ehValido; j--)
                    if(peca[i][j] != ' ') 
                        ehValido = ehValido && (get(i+coluna, linha-j) == ' '); 

            if(ehValido) {
                for(int i=0; i<largura; i++) {
                    for(int j=altura-1; j>=0; j--) {
                        if(j+linha<getAltura(i+coluna)) {
                            jogo[i+coluna][linha-j] = peca[i][j];
                        }
                        else {
                            alocarColunaAteAltura(i+coluna, linha+1-j);
                            jogo[i+coluna][linha-j] = peca[i][j];
                        }
                        
                    }
                }
            }
            for(int i=0; i<largura; i++)
                delete[] peca[i];
            delete[] peca;
            return ehValido;
        }
        return false;
    }

    for(int i=0; i<largura; i++)
        delete[] peca[i];
    delete[] peca;
    return false;
}