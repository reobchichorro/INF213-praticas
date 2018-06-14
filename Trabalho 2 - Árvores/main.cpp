#include <iostream>
#include "MySet.h"
using namespace std;

long long int insertionSort(int* v, int n) {  //Ordena o vetor e retorna o numero de movimentos realizados.
    long long int answer = 0;
    for(int i=1; i<n; i++) {
        for(int j=i-1; j>=0; j--) {
            if(v[j+1] < v[j]) {
                swap(v[j+1], v[j]);
                answer++;
            }
        }
    }
    return answer;
}

int main() {
	MySet<int> tree;
	string st; cin >> st;
    int n; cin >> n;
    if(st == "ARVORE") {
        for(int i=0; i<n; i++) {
            int elem; cin >> elem;
            tree.insert(elem);
        }
        cout << tree.getMovements() << endl;
    }
    else if(st == "ORDENAR") {
        int* v = new int[n];
        for(int i=0; i<n; i++) {
            cin >> v[i];
        }
        cout << insertionSort(v, n) << endl;
        delete[] v;
    }
}