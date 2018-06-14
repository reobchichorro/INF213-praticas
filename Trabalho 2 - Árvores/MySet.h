#ifndef MY_SET_LIST_H
#define MY_SET_LIST_H

#include <algorithm> //classe pair esta aqui...
using namespace std;

template<class T>
class MySetIterator;

template  <class T>
class Node {
	public: //classe auxiliar.. vamos utiliza-la apenas neste arquivo (nao e' muito necessario ter encapsulamento)
		Node(const T &elem_) : elem(elem_),left(NULL), right(NULL) { itemCount = 1; subTreeSize=1; } //Inicializamos os novos atributos com o valor 1, ja que possuimos um item na arvore: elem_.
		T elem;
		Node<T> *left, *right;
		long long int itemCount; //Novos atributos pedidos na especificacao do trabalho.
		long long int subTreeSize;
};

template  <class T>
class MySet {
	typedef MySetIterator<T> iterator;
public:
	int size() const;
	MySet() : size_(0), root(NULL), movements(0) {} //Movements e' inicializado como 0, ja que a arvore nao possui elementos, logo o insertionSort nao realizou movimentos.

	pair<iterator,bool> insert(const T&elem); //retorna um iterador para o elemento inserido (o valor booleano sera' true se o elemento nao existia no conjunto e falso caso ele ja exista (ou seja, o novo elemento nao foi inserido) ).
	iterator find(const T&elem); //por simplicidade, nao vamos deixar implementar um find constante...

	iterator end() {return iterator(NULL);}; //por enquanto nao vamos ter um metodo "begin()"

	const long long int getMovements() const { return movements; } //Funcao get para o atributo.

	MySet(const MySet &other);
	MySet &operator=(const MySet &other);
	~MySet();
private:
	int size_;
	Node<T> *root;
	long long int movements; //Armazena quantos movimentos teriam sido feitos pelo insertionSort, que e' a resposta do problema.

	//funcoes auxiliares...
	pair<iterator,bool> insert(const T&elem, Node<T> *&root); 
	iterator find(const T&elem, Node<T> *root);

	void deleteNodes(Node<T> *root);
	Node<T> * copyNodes(const Node<T> *root) const;

};




//por enquanto vamos desconsiderar os operadores ++ e -- em conjuntos...
//tais operadores serao "escondidos"
template<class T>
class MySetIterator {
	friend class MySet<T>;
public:
	MySetIterator(Node<T> *ptr_): ptr(ptr_) { }
	T &operator*() {return ptr->elem;}

	bool operator==(const MySetIterator &other) const {return ptr==other.ptr;}
	bool operator!=(const MySetIterator &other) const {return ptr!=other.ptr;}

private:
	Node<T> *ptr;
};



template  <class T>
MySet<T>::MySet(const MySet &other) {
	size_=0;
	root= NULL;
	*this = other; //vamos usar o operador de atribuicao..
}


template  <class T>
void MySet<T>::deleteNodes(Node<T> *root) {
	if(!root) return;
	deleteNodes(root->left);
	deleteNodes(root->right);
	root->itemCount=0; //Como deletamos o nodo, a arvore/subarvore nao possui elementos.
	root->subTreeSize=0;
	delete root;
}

template  <class T>
MySet<T>::~MySet() {
	deleteNodes(root);
	movements = 0; //Como deletamos toda a arvore, nao temos mais nenhum movimento.
}


template  <class T>
Node<T> * MySet<T>::copyNodes(const Node<T> *root) const {
	if(root==NULL) { //caso base
		return NULL;
	}
	Node<T> *  ans = new Node<T>(root->elem);
	ans->left = copyNodes(root->left);
	ans->right = copyNodes(root->right);
	ans->itemCount = root->itemCount;
	ans->subTreeSize = root->subTreeSize;

	return ans;
}

template  <class T>
MySet<T> & MySet<T>::operator=(const MySet &other) {
	if(this==&other) return *this; //testa auto-atribuicao...
	root = copyNodes(other.root);
	size_ = other.size_;
	movements = other.getMovements();
}



template  <class T>
int MySet<T>::size() const {
	return size_; //exercicio: como calcular o tamanho de forma dinamica? (i.e., sem armazenar o inteiro "size" na classe)
}


//funcao auxiliar...
//exercicio: por que a raiz precisa ser passada por referencia?
template  <class T>
pair<typename MySet<T>::iterator,bool> MySet<T>::insert(const T&elem, Node<T> * &root) { //retorna um iterador para o elemento inserido (o valor booleano sera' true se o elemento nao existia no conjunto e falso caso ele ja exista (ou seja, o novo elemento nao foi inserido) ).
	if(!root) {
		root = new Node<T>(elem);
		size_++;
		return make_pair(iterator(root),true);
	} else {
		root->subTreeSize++; //Como vamos inserir o elemento na arvore, devemos aumentar o valor de subTreeSize armazenado pela raiz de toda subarvore pela qual passamos.
		if(root->elem > elem) {
			movements += root->itemCount; //Se inserirmos o elemento `a esquerda, devemos adicionar todos os valores maiores que ele, ou seja, itemCount da raiz, 
			if(root->right != NULL) movements += root->right->subTreeSize; //e subTreeSize do filho `a direita.
			return insert(elem, root->left);
		}
		else if (root->elem < elem) return insert(elem, root->right);
		else {
			root->itemCount++; //Se o numero ja estiver inserido na arvore, o valor de itemCount aumenta em 1 naquele nodo.
			if(root->right != NULL) movements += root->right->subTreeSize; //Adicionamos o numero de valores restantes que sao maiores que elem.
			return make_pair(iterator(root),false);//igual..
		}
	}
}

template  <class T>
pair<typename MySet<T>::iterator,bool> MySet<T>::insert(const T&elem) { //retorna um iterador para o elemento inserido (o valor booleano sera' true se o elemento nao existia no conjunto e falso caso ele ja exista (ou seja, o novo elemento nao foi inserido) ).
	return insert(elem,root);
}



//funcao auxiliar...
template  <class T>
typename MySet<T>::iterator MySet<T>::find(const T&elem, Node<T> *root) { //retorna um iterador para o elemento inserido (o valor booleano sera' true se o elemento nao existia no conjunto e falso caso ele ja exista (ou seja, o novo elemento nao foi inserido) ).
	if(!root) {		
		return iterator(NULL);
	} else {
		if(root->elem > elem) return find(elem, root->left);
		else if (root->elem < elem) return find(elem, root->right);
		else return iterator(root);//igual..
	}
}


template  <class T>
typename MySet<T>::iterator MySet<T>::find(const T&elem) {
	find(elem,root);
}

#endif