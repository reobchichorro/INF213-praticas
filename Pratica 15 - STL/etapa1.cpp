#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;
/*
double aux(double a, const pair<string,double>& b) { return a + b.second; }

bool CR(const pair<string,double>& a, const pair<string,double>& b) { return a.second > b.second; }

bool maiorQue60(const pair<string,double>& a) { return a.second > 60.0; }
*/
int main() {
    map<string,double> alunos;
    alunos.insert(make_pair("Maria", 69));
    alunos.insert(make_pair("Gustavo", 4.20));
    alunos.insert(make_pair("Augusto", 83.5));
    alunos.insert(make_pair("Yasmin", 54.8));

    double soma = 0; int n=0;
    for(map<string,double>::const_iterator it = alunos.cbegin(); it != alunos.cend(); it++, n++)
        soma += (*it).second;
    cout << "v1 " << soma/n << endl;

    soma=0; n=0;
    for(auto i:alunos)
        soma += i.second;
    cout << "v2 " << soma/alunos.size() << endl;

    cout << "v3 " << accumulate(alunos.begin(), alunos.end(), 0.0, [](double a, const pair<string,double>& b) { return a + b.second; })/alunos.size() << endl;

    for(auto i:alunos)
        cout << i.first << ":" << i.second << " ";
    cout << endl;

    vector<pair<string,double>> v(alunos.begin(), alunos.end());
    sort(v.begin(), v.end(), [](const pair<string,double>& a, const pair<string,double>& b) { return a.second > b.second; });
    for(auto i:v)
        cout << i.first << ":" << i.second << " ";
    cout << endl;

    cout << count_if(alunos.begin(), alunos.end(), [](const pair<string,double>& a) { return a.second >= 60.0; }) << " alunos tem CR maior ou igual a 60." << endl;
}
