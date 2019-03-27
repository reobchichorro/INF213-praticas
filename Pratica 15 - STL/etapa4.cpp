/*
A seguir, desenvolva um programa que gera todas as possibilidades de percurso e, entao, imprime na tela o custo do menor percurso. 
Se você utilziar a STL (utilize!) seu programa sera bastante simples e com poucas linhas de codigo! 

Use a funcao time para medir o tempo de execucao do seu programa considerando matrizes de diferentes tamanhos. 
O arquivo fornecido como material para a pratica contem matrizes de diferentes tamanhos como exemplo (o inicio de cada matriz contem o tamanho dela).

Dica para deixar seu programa um pouco mais rapido (tente fazer isso após resolver o problema): 
e’ necessario testar todas possibilidades para a primeira cidade do percurso? Ou a cidade na qual comecamos não importa?

Curiosidade: apesar desse problema ser extremamente dificil de ser resolvido, 
encontrar a melhor rota entre duas cidades e’ uma tarefa simples de ser realizada de forma eficiente! 
(ha inclusive um algoritmo que faz isso utilizando apenas 4 linhas de codigo!). Isso será estudado em teoria de grafos e em paa. 
*/
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int calcularCusto(const vector<vector<int>>& mat, const vector<int>& cidades) {
    int custo = 0;
    for(int i=0; i < cidades.size()-1; i++) custo += mat[cidades[i]][cidades[i+1]];
    custo += mat[cidades[cidades.size()-1]][cidades[0]];
    return custo;
}

void procurarSolucaoOtima(const vector<vector<int>>& mat, vector<int>& melhorCaminho, int& menorCusto) {
    vector<int> caminho(mat.size());
    int i=0;
    for(auto it=caminho.begin(); it!=caminho.end(); it++, i++) *it = i;

    //cout << " ";
    int custo = calcularCusto(mat, caminho);
    menorCusto = custo;
    melhorCaminho = caminho;

    while( next_permutation( caminho.begin(), caminho.end() ) ) {
        int custo = calcularCusto(mat, caminho);
        if(custo < menorCusto) {
            menorCusto = custo;
            melhorCaminho = caminho;
        }
    }
}

int main() {
    int n; cin>>n;
    vector<vector<int>> mat(n);

    for(int i=0; i<n; i++) {
        mat[i].reserve(n);
        for(int j=0; j<n; j++) cin >> mat[i][j];
    }

    vector<int> cidades;
    int menorCusto = -1;
    procurarSolucaoOtima(mat, cidades, menorCusto);
    cout << "Custo: " << menorCusto << endl;
    cout << "Caminho: ";
    for(auto i:cidades) cout << i << ", ";
    cout << cidades[0] << endl;

    //cout << calcularCusto(mat, cidades) << endl;
}
