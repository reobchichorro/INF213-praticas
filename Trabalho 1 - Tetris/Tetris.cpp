#include <iostream>
#include <string>
#include "Tetris.h"

Tetris::Tetris(const int c) {
    col = c;
    if(c > 0) { //Nao podemos ter um numero negativo de colunas. 0 colunas e' tratado como caso especial.
        jogo = new char*[c];
        alturas = new int[c];
    }
    else {      //Caso c seja 0 ou negativo, criamos um Tetris com 0 colunas.
        col = 0; 
        jogo = NULL;
        alturas = NULL;
    }

    for(int i=0; i<c; i++) {    //Caso c seja 0 ou negativo, nao ocorrera nenhuma iteracao deste loop, entao eestamos protegidos.
        alturas[i] = 0; //Nao ha nenhum pixel alocado, logo a altura e' 0.
        jogo[i] = NULL;
    }
}

Tetris::~Tetris() {
    destroy();
}

void Tetris::destroy() {    //Destroi jogo** e altura* e coloca o numero de colunas como 0.
    if(getNumColunas() != 0) {  //Caso o numero de colunas seja 0, nao precisamos destruir nada, pois os ponteiros estarao apontados para NULL.
        delete[] alturas;
        for(int i=0; i<getNumColunas(); i++)
            delete[] jogo[i];
        delete[] jogo;
        alturas = NULL;
        jogo = NULL;
    }
    col=0;
}

Tetris::Tetris(const Tetris& other) {
    if(&other==this) 
        return;

    col = other.getNumColunas();
    if(other.getNumColunas() > 0) {
        jogo = new char*[other.getNumColunas()];
        alturas = new int[other.getNumColunas()];
    } else {
        jogo = NULL;
        alturas = NULL;
    }

    for(int i=0; i<other.getNumColunas(); i++) {
        alturas[i] = other.getAltura(i);
        jogo[i] = new char[other.getAltura(i)];

        for(int j=0; j<other.getAltura(i); j++)
            jogo[i][j] = other.get(i,j);
    }
}

Tetris& Tetris::operator=(const Tetris& other) {
    if(&other==this) 
        return *this;

    destroy();  //Destruimos os valores antigos de this. Fora isso, esta funcaao faz os mesmos passos do construtor de copia.
    col = other.getNumColunas();
    if(other.getNumColunas() > 0) {
        jogo = new char*[other.getNumColunas()];
        alturas = new int[other.getNumColunas()];
    } else {
        jogo = NULL;
        alturas = NULL;
    }

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
        return alturas[c];          //retornamos sua altura, que a posicao do pixel mais alto da coluna.
}

int Tetris::getAltura() const {         //Retorna a maior altura.
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
            return jogo[c][l];          //Se sim, retornamos o pixel requisitado.
    return ' ';                         //Caso contrario, retornamos um espaco vazio.
}

void Tetris::alocarColunaAteAltura(const int c, const int l) {  //Aloca memoria na coluna c tal que sua nova altura seja l+1.
    if(l < getAltura(c))    //Caso a altura nova seja menor do que altura antiga, nao precisamos alocar nada.         
        return;

    char* temp = new char[l+1];         //Variavel temporaria que armazena os novos valores da coluna.
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
            return false;       //logo ela nao pode ser deletada.
        
    char** temp = new char*[getNumColunas()];       //Armazena temporariamente o novo estado do jogo.
    int* alturasTemp = new int[getNumColunas()];    //Armazena temporiamente os novos valores de alturas*.

    for(int i=0; i<getNumColunas(); i++) {
        alturasTemp[i] = getAltura(i)-1;        //A nova altura sera (altura antiga - 1), ja que vamos remover uma linha.
        temp[i] = new char[alturasTemp[i]];   

        bool colunaVazia = true;                //Variavel que verifica se, apos a remocao da linha, a coluna ficara' vazia.
        for(int j=0; j < alturasTemp[i]; j++) {
            if(j < l)                           //Enquanto estivermos antes da linha que sera removida,
                temp[i][j] = jogo[i][j];        //pegamos o valor antigo.
            else                                //Mas a partir da linha removida pegamos a linha seguinte, ja que,
                temp[i][j] = jogo[i][j+1];      //se removermos a linha 2, por exemplo, a nova linha 2 sera a antiga linha 3.
            
            if(temp[i][j] != ' ')               //Se houver algum valor nao-vazio na coluna, a variavel e' claramente falsa.
                colunaVazia = false;  
        }
        if(colunaVazia) {       //Se a coluna ficou apenas com caracteres ' ', devemos deletar a memoria da coluna.
            delete[] temp[i];
            temp[i] = NULL;
            alturasTemp[i] = 0;
        }     
    }

    int c = getNumColunas();    //Armazenamos temporariamente o numero de colunas, pois este sera passado para 0 na linha seguinte.
    destroy();                  //Destruimos os valores antigos de jogo** e alturas* e atribuimos 0 para o atributo col.
    col = c;                    //Voltamos para col o seu valor antigo, armazenado pela variavel auxiliar c. 
    jogo = temp;                //Atribuimos os novos valores de jogo** e alturas*.
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

void Tetris::criarPeca(char**& peca, int& largura, int& altura, const char id) const {
    //Os condicionais tratam cada um dos possiveis ids, criando a menor matriz possivel para armazenar a peca,
    //atribuindo o valor de largura e altura corretas e preenche a peca de acordo com a especificacao.
    if(id == 'O') {         
        largura = altura = 2;           //Atribui os valores da largura e altura,
        peca = new char*[largura];      //aloca memoria de peca**,
        peca[0] = new char[altura];
        peca[1] = new char[altura];
        peca[0][0] = peca[0][1] = peca[1][0] = peca[1][1] = id; //preenche a peca.
    } 
    else if(id == 'I') {            //Todos os outros ids funcionam de maneira analoga ao 'O'.
        largura = 1; altura = 4;
        peca = new char*[largura];
        peca[0] = new char[altura];
        peca[0][0] = peca[0][1] = peca[0][2] = peca[0][3] = id;
    } 
    else if(id == 'J') {
        largura = 4; altura = 2;
        peca = new char*[largura];
        for(int i=0; i<largura; i++) {
            peca[i] = new char[altura];
            peca[i][0] = id;        //Cria a matriz na forma:"JJJJ"
            peca[i][1] = ' ';       //                      :"    "     
        }
        peca[3][1] = 'J';           //Corrige o valor de [3][1], que deveria ser J
    } 
    else if(id == 'L') {
        largura = 4; altura = 2;
        peca = new char*[largura];
        for(int i=0; i<largura; i++) {
            peca[i] = new char[altura];
            peca[i][0] = id;    //Cria a matriz na forma:"LLLL  "
            peca[i][1] = ' ';   //                      :"    " 
        }
        peca[0][1] = 'L';       //Corrige o valor de [0][1], que deveria ser L
    } 
    else {    //As pecas de id Z, S e T terao o mesmo tamanho, logo, para a alocacao de memoria, as tres estao sendo contempladas no mesmo condicional. 
        largura = 3; altura = 2;
        peca = new char*[largura];
        for(int i=0; i<largura; i++)
            peca[i] = new char[altura];

        if(id == 'S') {
            peca[0][0] = peca[2][1] = ' ';
            peca[0][1] = peca[1][0] = peca[1][1] = peca[2][0] = id;
        } 
        else if(id == 'T') {
            peca[0][1] = peca[2][1] = ' ';
            peca[0][0] = peca[1][0] = peca[1][1] = peca[2][0] = id;
        } 
        else if(id == 'Z') {
            peca[0][1] = peca[2][0] = ' ';
            peca[0][0] = peca[1][0] = peca[1][1] = peca[2][1] = id;
        } 
        else {                      //Caso o programa chegue neste condicional, significa que o id passado como parametro e' invalido.
            for(int i=0; i<largura; i++)
                delete[] peca[i];   //Nesse caso, destruimos a peca.
            delete[] peca;
            peca = NULL;
        }
    }
}

void Tetris::rotacionar(char**& peca, int& largura, int& altura, const int rotacao) const {
    for(int rotacaoPeca = 0; rotacaoPeca<rotacao; rotacaoPeca+=90) {    //rotacaoPeca guarda a rotacao atual da peca.
        char** novaPeca = new char*[altura];    //Variavel auxiliar que armazena como sera a peca depois de rotacionada. 
        for(int j=0; j<altura; j++)             //Sua largura sera a altura da peca antiga,
            novaPeca[j] = new char[largura];    //e sua altura sera a largura da peca antiga.

        for(int j=0; j<altura; j++)
            for(int i=0; i<largura; i++) 
                novaPeca[j][i] = peca[i][altura-1-j];   //Esta e' uma relacao entre a peca nova (rotacionada em 90 graus) e a peca antiga.

        for(int i=0; i<largura; i++)
            delete[] peca[i];   
        delete[] peca;      //Destruimos a peca antiga,
        peca = novaPeca;    //e passamos a ela os valores da peca nova.
        novaPeca = NULL;

        int temp = largura; //Variavel auxiliar para fazer a troca de largura e altura.
        largura = altura;
        altura = temp;
    }
}

bool Tetris::colocarPeca(char**& peca, const int largura, const int altura, const int coluna, const int linha) {
    //ehValido e' responsavel por dizer se houve sucesso em colocar a peca ou nao.
    bool ehValido = (0 <= coluna && coluna <= getNumColunas() - largura);   //Verificamos se a peca cabe horizontalmente.
    if(ehValido) {
        ehValido = ehValido && (altura-1 <= linha);     //Verificamos se a peca cabe verticalmente.
        if(ehValido) {
            for(int i=0; i<largura && ehValido; i++)        //Esse loop verifica se nao ha' conflito entre uma peca ja alocada no jogo,
                for(int j=altura-1; j>=0 && ehValido; j--)  //e a peca que queremos colocar.
                    if(peca[i][j] != ' ') 
                        ehValido = ehValido && (get(i+coluna, linha-j) == ' '); 

            if(ehValido) { 
                for(int i=0; i<largura; i++) {
                    for(int j=altura-1; j>=0; j--) {
                        if(peca[i][j] != ' ') {
                            if(j+linha<getAltura(i+coluna)) {   //Se ja houver memoria alocada na coluna, e' so colocar o pixel.
                                jogo[i+coluna][linha-j] = peca[i][j];
                            }
                            else {
                                alocarColunaAteAltura(i+coluna, linha+1-j); //Senao, precisamos alocar memoria primeiro.
                                jogo[i+coluna][linha-j] = peca[i][j];
                            }
                        }
                    }
                }
            }
        }
    }
    for(int i=0; i<largura; i++)    //Nao precisamos mais da peca, entao devemos deleta-la
        delete[] peca[i];
    delete[] peca;
    return ehValido;    //Retornamos o valor de ehValido.
}

bool Tetris::adicionaForma(const int coluna, const int linha, const char id, const int rotacao) {
    if(rotacao%90 != 0 || rotacao < 0) return false;    //Nao sera possivel adicionar a peca caso a rotacao seja invalida.
    
    //Fase 1: Criar uma matriz representando a peca que sera adicionada. 
    //O tamanho da matriz sera o mais compacto possivel para armazenar a peca.
    char** peca;
    int largura, altura;    //Guardam a altura e a largura da peca. Essas variaveis serao usadas/relevantes durante toda a funcao.
    criarPeca(peca, largura, altura, id);

    if(peca == NULL) return false;  //Indica que criarPeca() atribuiu NULL para peca, ou seja, o id usado e' invalido.

    //Fase 2: Rotacionar a peca
    rotacionar(peca, largura, altura, rotacao);

    //Fase 3: Alocar a peca
    return colocarPeca(peca, largura, altura, coluna, linha);   //Retorna true se a peca foi colocada com sucesso.
}