#include <iostream>
#include <cmath>
using namespace std;

void digitos(int digitosCPF[], long int cpf) {
    for(int j=0; j<9; j++) {
        digitosCPF[j] = cpf/pow(10, 8-j);
        cpf %= (int)pow(10, 8-j);
    }
}

int digitoVerificador1(int digitosCPF[]) {
    int verificador1 = 0;
    for(int i=0; i<9; i++)
        verificador1 += digitosCPF[i]*(10-i);

    verificador1 *= 10;
    verificador1 %= 11;
    
    verificador1 %= 10;
    
    return verificador1;
}

int digitoVerificador2(int digitosCPF[]) {
    int verificador2 = 0;
    for(int i=0; i<10; i++)
        verificador2 += digitosCPF[i]*(11-i);

    verificador2 *= 10;
    verificador2 %= 11;
    
    verificador2 %= 10;

    return verificador2;
}

int main() {
    int n; cin >> n;
    for(int i=0; i<n; i++) {
        long int cpf;
        cin >> cpf;
        int digitosCPF[11];
        digitos(digitosCPF, cpf);
        digitosCPF[9] = digitoVerificador1(digitosCPF);
        digitosCPF[10] = digitoVerificador2(digitosCPF);
        cout << digitosCPF[9] << digitosCPF[10] << endl;
    }
}