/*
TAD MyVec
- Representa uma lista implementada por contiguidade
- Interface similar a da classe Vector do STL
- Criado por Salles Magalhaes em 19/02/2018

*/

#ifndef MyVec_H__
#define MyVec_H__

#include <iostream>
#include <string>
#include <ostream>


//Excessao usada pela classe MyVec
class MyVecException {
private:
	std::string msg;
public:
	MyVecException (const std::string &msg0): msg(msg0) { }
	const std::string & what() const { return msg; }
};


template<class T>
class MyVec {
public:
	template<class T2>
	friend std::ostream& operator<<(std::ostream &, const MyVec<T2> &);

	//construtores/destrutures/etc
	MyVec();
	MyVec(int n, const T&init=T());

	//destrutor
	~MyVec() { destroy(); };

	//Construtor de copia
	MyVec(const MyVec &);
	MyVec & operator=(const MyVec &);

	//funcoes de acesso
	T &operator[](int pos) {return data[pos];}
	const T &operator[](int pos) const {return data[pos];}
	void push_back(const T&);
	void resize(int newSize);
	void insert(const T&,int pos);
	void clear();

	void empty() const {return size() == 0;};
	int size() const {return dataSize;};

	int eraseMatchingElements(const T&);

private:
	T* data; //declare o membro de dados data, que devera armazenar os elementos da lista
	int dataSize; //quantos elementos ha na lista?
	int dataCapacity; //quantos elementos atualmente cabem na lista? 

	void create();
	void destroy();
	void resizeCapacity(int newCapacity);
};

template<class T>
void MyVec<T>::push_back(const T&elem) {
	//Implemente esta funcao! (nao reutilize a funcao "insere")
	if(dataSize==dataCapacity) {
		resizeCapacity(dataCapacity*2);
	}
	resize(dataSize+1);
	data[dataSize-1] = elem;
}

template<class T>
void MyVec<T>::resize(int newSize) {
	if(newSize >= dataCapacity) { //primeiro temos que realocar o vector...
		resizeCapacity(newSize); //para o resize vamos usar o tamanho exato caso seja necessario realocar o vector..
	}
	for(int i=dataSize;i<newSize;i++) { //preencha a parte "extra" do vector com valores "em branco"
		T temp = T();
		data[i] = temp;
	}
	dataSize = newSize;
}

//insere o elemento na posicao pos e move os elementos ja presentes no vetor
// pos pode ser:
//   uma posicao apos o final do vetor (para inserir na ultima posicao) 
//   ou uma posicao ja existente (nesse caso os elementos nessa posicao e apos ela serao movidos "para a frente")
template<class T>
void MyVec<T>::insert(const T&elem,int pos) {
	if(pos > dataSize || pos < 0) {
		throw MyVecException("Erro na funcao insert: posicao invalida");
	}

	if(dataSize == dataCapacity) { //preciso redimensionar?
		if(dataCapacity ==0) //Exercicio: Por que e' preciso testar isso?
			resizeCapacity(1);
		else
			resizeCapacity(dataCapacity*2);
	}	

	for(int i=dataSize;i>pos;i--)
		data[i] = data[i-1];
	data[pos] = elem;
	dataSize++;
}


template<class T>
void MyVec<T>::clear() {
	destroy();
	create();
}
/*
Adicione uma função chamada eraseMatchingElements a sua classe (essa função não está disponível nos vetores disponibilizados pela STL). 
Tal função deverá receber um argumento e remover do vetor todos elementos iguais a esse argumento (o argumento devera ser passado por referencia?
Referencia constante? A funcao devera ser constante?). Ao final deve-se retornar quantos elementos foram removidos 
(a capacidade do vetor não deve ser alterada).
Por exemplo, se o MyVec v armazena caracteres e v=[a,b,c,b,w,z], então após a chamada v.eraseMatchingElements(‘b’) 
o valor de v deverá ser [a,c,w,z] e a chamada da função deverá ter retornado o número 2 (visto que dois caracteres ‘b’ foram removidos de v).
Use o programa testaFuncoes.cpp  para testar sua função (entenda o funcionamento da entrada desse programa e crie entradas para avaliar o seu programa). 
Ao usar o programa testaFuncoes.cpp, comente a parte dele que testa funcoes ainda não implementadas.
Obs: sua funcao não deve alocar mais memoria (isso facilitaria bastante a implementacao, mas seria menos eficiente). 

Exercício (escreva a resposta a esse exercício em comentários por cima da sua implementação da funcao eraseMatchingElements): 
qual a ordem de complexidade (pior caso) da função eraseMatchingElements ? e’ possivel melhorar isso?

*/
template<class T>
int MyVec<T>::eraseMatchingElements(const T& erase) {
	//Exercicio: como alocar mais memoria poderia ajudar?
	//Se pudessemos alocar mais memoria. poderiamos nos aproveitar da funcao insert(), que aloca mais memoria.

	int numOfElementsErased = 0;
	for(int i=0; i<dataSize; i++) {
		if(data[i] == erase) {
			numOfElementsErased++;
			for(int j=i; j<dataSize-1; j++) {
				data[j] = data[j+1];
			}
			data[dataSize-1] = T();
		}
	}
	return numOfElementsErased;
}

template<class T>
void MyVec<T>::resizeCapacity(int newCapacity) {
	//implemente esta funcao
	//Ela deve redimensionar o vetor de modo que ele tenha capacidade newCapacity
	//Se newCapacity for menor do que a capacidade atual voce devera ignorar a chamada a esta funcao (i.e., nunca reduziremos a capacidade do vetor)
	//Nao se esqueca de liberar (deletar) a memoria que nao for mais necessaria (para evitar vazamentos de memoria)
	//Exemplo de execucao:
	//data=[1,2,3,,], dataSize=3, dataCapacity=5 (vetor de capacidade 5, com 3 elementos ocupados)
	//se chamarmos resizeCapacity(10), os membros de dados deverao ter os seguintes valores:
	//data=[1,2,3,,,,,,,], dataSize=3, dataCapacity=10

	if(newCapacity < dataCapacity)
		return;
	
	T* temp = new T[dataSize];
	for(int i=0; i<dataSize; i++) {
		temp[i] = data[i];
	}
	
	delete[] data;
	dataCapacity = newCapacity;
	data = new T[dataCapacity];

	for(int i=0; i<dataSize; i++)
		data[i] = temp[i];
	for(int i=dataSize; i<dataCapacity; i++) {
		data[i] = T();
	}

	delete[] temp;
}

template<class T>
void MyVec<T>::destroy() {
	delete []data;
	dataSize = dataCapacity = 0;
}

template<class T>
void MyVec<T>::create() {
	data = NULL;
	dataSize = dataCapacity = 0;
}

template<class T>
MyVec<T>::MyVec() {
	create();
}

template<class T>
MyVec<T>::MyVec(int n, const T&init) {
	//Implemente esta funcao:
	//Cria um vetor de tamanho e capacidade n, onde todos os n elementos valem "init"
	dataCapacity = n;
	dataSize = n;
	data = new T[n];
	for(int i=0; i<n; i++)
		data[i] = init;
}


//Construtor de copia
template<class T>
MyVec<T>::MyVec(const MyVec &other) {
	//Implemente esta funcao
	//Dica: nao duplique codigo! (esta funcao deve ser escrita utilizando apenas 2 linhas de codigo!)
	create();
	*this = other;
}

template<class T>
MyVec<T> & MyVec<T>::operator=(const MyVec &other) {
	if(this==&other) return *this; 
	destroy(); //Exercicio: por que precisamos disso?
	dataCapacity = other.dataCapacity;
	dataSize = other.dataSize;
	//data = other.data; //por que nao podemos fazer isso?
	data = new T[dataCapacity];
	for(int i=0;i<dataSize;i++) data[i] = other.data[i];
	return *this;
}

template<class T2>
std::ostream& operator<<(std::ostream &out, const MyVec<T2> &v) {
	out << "Size: " << v.size() << "\n";
	out << "Capacity: " << v.dataCapacity << "\n";
	for(int i=0;i<v.size();i++) out << v.data[i] << " ";
	out << "\n";
	return out;
}

#endif