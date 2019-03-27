#ifndef __Conjunto1_h
#define __Conjunto1_h

#include <iostream>
using namespace std;

template <class T>
class Conjunto;

template <class T>
ostream &operator<<(ostream &, const Conjunto<T> &c);

template <class T>
istream &operator>>(istream &, Conjunto<T> &c);

template <class T>
class Conjunto {

    public:
        Conjunto(const int tamanho=10);
        Conjunto(const Conjunto<T> &other);
        ~Conjunto();

        bool pertence(const T &x) const;
        bool insere(const T &x);
        int numelementos() const;
        int tamarray() const;

        bool operator==(const Conjunto<T> &other) const;
        Conjunto<T> &operator=(const Conjunto<T> &other);

	    friend ostream &operator<< <T>(ostream &, const Conjunto<T> &c);
        friend istream &operator>> <T>(istream &, Conjunto<T> &c);

    private:
        T* elementos;
        int num_elementos;
        int tam_array;
};

template <class T>
Conjunto<T>::Conjunto(const int tamanho) {
	elementos = new T[tamanho];
    tam_array = tamanho;
    num_elementos = 0;
}
template <class T>
Conjunto<T>::Conjunto(const Conjunto<T> &other) {

    tam_array = other.tamarray();
    num_elementos = other.numelementos();
    elementos = new T[tam_array];

    for(int i=0; i<num_elementos; i++)
        elementos[i] = other.elementos[i];
    
}
template <class T>
Conjunto<T>::~Conjunto() {
	delete []elementos;
    num_elementos = 0;
    tam_array = 0;
}

template <class T>
bool Conjunto<T>::pertence(const T &x) const{
    for(int i=0; i<num_elementos; i++)
        if(elementos[i] == x)
            return true;
    return false;
}
template <class T>
bool Conjunto<T>::insere(const T &x) {
    if(tam_array == num_elementos || pertence(x))
        return false;
    elementos[num_elementos] = x;
    num_elementos++;
    return true;
    
}
template <class T>
int Conjunto<T>::numelementos() const{
    return num_elementos;
}
template <class T>
int Conjunto<T>::tamarray() const{
    return tam_array;
}

template <class T>
bool Conjunto<T>::operator==(const Conjunto<T> &other) const {
    if(num_elementos != other.numelementos())
        return false;
    for(int i=0; i<num_elementos; i++) {
        if( !other.pertence(elementos[i]) )
            return false;
    }
    return true;
}

template <class T>
Conjunto<T> & Conjunto<T>::operator=(const Conjunto<T> &other) {
    
    if(&other==this) 
        return *this;
        
    tam_array = other.tamarray();
    num_elementos = other.numelementos();
	delete []elementos;
    elementos = new T[tam_array];

    for(int i=0; i<num_elementos; i++)
        elementos[i] = other.elementos[i];
    
	return *this;
}

template <class T>
ostream &operator<<(ostream &os, const Conjunto<T> &c) {
	os << "{";
    for(int i=0; i<c.numelementos(); i++) {
        os << c.elementos[i];
        if(i != (c.numelementos() - 1))
            os << ",";
    }
    os << "}";
	return os;
}
template <class T>
istream &operator>>(istream &is, Conjunto<T> &c) {
    T item;
    while(is >> item) {
        c.insere(item);
    }
	return is;
}

#endif