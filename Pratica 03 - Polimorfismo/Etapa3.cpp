#include <iostream>
using namespace std;

#include "FigBase.h"
#include "Retangulo.h"
#include "Circulo.h"
#include "Segmento.h"

int main() {

    FigBase *arr[5];
    Circulo c0, c1;
    Retangulo r;
    Segmento s3, s4;
    arr[0] = &c0;
    arr[1] = &c1;
    arr[2] = &r;
    arr[3] = &s3;
    arr[4] = &s4;
    
    for(int i=0; i < 5; i++) {
        cin >> *arr[i];
    }
    
    for(int i=0; i < 5; i++) {
       cout << *arr[i];
       cout << "-----------------------------------\n";
    }

    return 0;

}