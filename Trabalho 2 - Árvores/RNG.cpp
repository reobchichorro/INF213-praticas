#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    srand(time(0));
    bool metodo = 1;
    int n = 1000;
    int range = 2000000000;

    if(metodo) cout << "ARVORE" << endl;
    else cout << "ORDENAR" << endl;

    cout << n << endl;

    for(int i=0; i<n; i++) {
        int haha = rand()%2;
        if(haha == 1) cout << rand()%(range) << " ";
        else cout << -1*rand()%(range) << " ";
    }
    cout << endl;

    return 0;
}