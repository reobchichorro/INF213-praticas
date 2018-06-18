#include <iostream>
#include <string>
#include "MyMap.h"

using namespace std;

/*
Uma importante aplicacao de ABPs e’ na implementacao de “mapas” (tambem conhecidos como dicionarios), 
que sao basicamente estruturas de dados dinamicas que mapeiam um objeto em outro.

Vejam exemplos de uso em testaMyMap e veja a implementacao do mapa em MyMap.h . 
Basicamente a diferenca entre o MyMap e o MySet e’ que MySet armazena apenas chaves, 
enquanto o MyMap armazena pares do tipo chave, valor (sendo que apenas as chaves sao utilizadas nas buscas na ABP).

Obs:
Essa implementacao foi feita rapidamente apenas para mostrar a ideia de mapas. 
Provavelmente ha varias formas de melhorar a sua eficiencia e qualidade 
(por exemplo, para evitar complicar a classe não fornecemos versoes constantes de algumas funcoes).
Essa implementacao não foi muito testada. Logo, pode conter pequenos bugs! 
Agradeco se encontrarem/indicarem problemas nela (ou em qualquer outro programa implementado nesta disciplina)!
Note que usamos a classe generica pair da STL (uma classe muito útil utilizada para armazenar pares de tipos arbitrarios). 
Mais informacoes: http://www.cplusplus.com/reference/utility/pair/


Utilizando a classe MyMap, crie um programa chamado geraCodigo.cpp .
Tal programa devera ler palavras (separadas por espaco, tab ou newlines) da entrada padrao e, 
entao, gerar um codigo unico (de 0 ate n-1, onde n e’ o numero de palavras distintas) para cada palavra. 
O codigo 0 devera ser atribuido a primeira palavra unica lida, o codigo 1 devera ser associado a segunda palavra unica encontrada e assim por diante.

Para cada palavra lida do arquivo, seu programa deve imprimir uma linha com a palavra e seu codigo (separados por um espaco em branco). 

Veja abaixo um exemplo de entrada (a entrada e’ o mesmo conteudo do arquivo testePalavras2.txt)  
e a saida esperada (a primeira linha da saida abaixo apresenta o comando utilizado para gera-la).

abc 123 123 copia copia
hello abc
abc copia copia
$ ./a.out < testePalavras2.txt
abc 0
123 1
123 1
copia 2
copia 2
hello 3
abc 0
abc 0
copia 2
copia 2
*/

int main() {
    
    MyMap<int, string> palavrasUnicas;
    string palavra;
    int n=0;
    while(cin >> palavra) {
        bool unico = true;
        for(int i=0; i<=n; i++) {
            MyMapIterator<int, string> valor_i = palavrasUnicas.find(i);
            if(valor_i == NULL) continue;
            if( (*palavrasUnicas.find(i)).second == palavra) {
                cout << palavrasUnicas[i] << " " << i << endl;
                unico = false;
                break;
            }
        }
        if(unico) {
            palavrasUnicas.insert(make_pair(n, palavra));
            MyMapIterator<int, string> palavraAtual = palavrasUnicas.find(n);
            cout << (*palavraAtual).second << " " << (*palavraAtual).first << endl;
            n++;
        }
    }

    return 0;
}