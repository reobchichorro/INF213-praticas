#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

//Observacoes:
//-- Atencao: C++11 e' necessario para compilar este codigo

#include "PPMImage.h" //nao modifique a classe PPMImage!!!

//--------------------------------
//Implemente seu trabalho a partir daqui... (crie outros arquivos .h/.cpp se necessario)

#include <string>
#include "quadTree.h"
#include <stack>


int main(int argc,char**argv) {
    string argumento = string(argv[1]);
    //cout << argumento << " " << argv[1] << " " << string(argv[1]) << endl;

    if(argumento == "comprimir") {
        PPMImage imagem;
        cin >> imagem;
        QuadTree tree;
        tree.comprimir(imagem);
        cout << imagem.getRows() << " " << imagem.getMaxCol() << endl;
        cout << tree;
    } 
    else if (argumento == "descomprimir") {
        QuadTree tree;
        int nRows, maxIntensity;
        char aux; 
        Color pixel(0, 0, 0);
        stack<char> parenteses;

        cin >> nRows >> maxIntensity;

        int counter = 0;
        while(cin>>aux) { 
            if(aux >= '0' && aux <='9') {
                if(counter == 0) {
                    pixel.r *= 10;
                    pixel.r += aux - '0';
                } else if(counter == 1) {
                    pixel.g *= 10;
                    pixel.g += aux - '0';
                } else if(counter  == 2) {
                    pixel.b *= 10;
                    pixel.b += aux - '0';
                }
            }
            else if(aux == ',') counter++;
            else if(aux == '(') parenteses.push(aux);
            else {
                if(counter == 2) {
                    tree.insertOnLevelH(pixel, parenteses.size());
                    pixel.r = pixel.g = pixel.b = 0;
                    parenteses.pop();
                }
                
                counter = 0;
            }
        }
        PPMImage imagem(nRows, nRows, maxIntensity);
        tree.gravarImagemPPM(imagem);
        //cout << tree;
        cout << imagem;
    }
    
}
