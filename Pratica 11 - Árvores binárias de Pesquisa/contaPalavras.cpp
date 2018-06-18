#include <iostream>
#include <string>
#include "MySet.h"
#include "MyVecNewIterator.h"

using namespace std;

int main(int argc, char * argv[]) {
    string argumento = string(argv[1]);
    if(argumento == "myvec") {
        MyVec<string> palavrasUnicas;
        string palavra;
        int soma = 0;
        while(cin >> palavra) {
            soma++;
            bool estaNoVetor = false;
            for(int i=0; i<palavrasUnicas.size() && !estaNoVetor; i++)
                if(palavrasUnicas[i] == palavra) estaNoVetor = true;
            if(!estaNoVetor) palavrasUnicas.push_back(palavra);
        }
        cout << soma << " " << palavrasUnicas.size() << endl;
    }
    else if(argumento == "myset") {
        MySet<string> palavrasUnicas;
        string palavra;
        int soma = 0;
        while(cin >> palavra) {
            soma++;
            palavrasUnicas.insert(palavra);
        }
        cout << soma << " " << palavrasUnicas.size() << endl;
    }

    return 0;
}