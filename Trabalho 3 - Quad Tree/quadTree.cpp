#include "quadTree.h"
#include <iostream>
#include <string>
using std::cout;
using std::string;

//Funcoes publicas:

QuadTree::~QuadTree() {
    destroy(root);
}

QuadTree::QuadTree(const QuadTree& other) {
    size = 0;
    root = NULL;
    *this = other;
}

QuadTree& QuadTree::operator=(const QuadTree& other) {
    if(this==&other) 
        return *this;
    
	destroy(root);
	root = copyNodes(other.root);
	size = other.getSize();
	return *this;
}


void QuadTree::comprimir(const PPMImage& imagem) {
    comprimirQuadrante(imagem, 0, 0, imagem.getRows(), root);
}

void QuadTree::insertOnLevelH(const Color& pixel, int h) {
    insertOnLevelH_aux(root, pixel, h);
}

ostream &operator<<(ostream& os, const QuadTree& tree) {
    tree.print(os, tree.root);
    return os;
}

void QuadTree::gravarImagemPPM(PPMImage& imagem) const {
    gravarQuadranteImagemPPM(imagem, 0, 0, imagem.getRows(), imagem.getColumns(), root);
}

//Funcoes Auxiliares (privadas):

void QuadTree::destroy(Node* root) {
    if(!root) return;
	destroy(root->a);
	destroy(root->b);
    destroy(root->c);
    destroy(root->d);
    root->full = false;
	delete root;
}

Node* QuadTree::copyNodes(const Node* otherRoot) const {
    if(!otherRoot) return NULL;
	Node* aux = new Node(otherRoot->pixel);
    aux->full = otherRoot->full;
	aux->a = copyNodes(otherRoot->a);
	aux->b = copyNodes(otherRoot->b);
	aux->c = copyNodes(otherRoot->c);
    aux->d = copyNodes(otherRoot->d);
	return aux;
}

int QuadTree::calcularSize(Node* root) const {
    if(!root) return 0;
    return 1 + calcularSize(root->a) + calcularSize(root->b) + calcularSize(root->c) + calcularSize(root->d);
}

void QuadTree::comprimirQuadrante(const PPMImage& imagem, const int yMin, const int xMin, const int size, Node* &curr) {
    Color representingColor;  
    if(imagem.isUniform(yMin, xMin, size, representingColor)) {
        insert(curr, representingColor);
    }
    else {
        representingColor.r = representingColor.g = representingColor.b = -1; 
        // (-1,-1,-1) e' um valor auxiliar que indica que nao ha nada no nodo, mas ele possui filhos. 
        //Como a cor (-1,-1,-1) nao existe, podemos definir esse valor como um valor auxiliar com seguranca.
        insert(curr, representingColor);
        curr->full = false;

        comprimirQuadrante(imagem, yMin+(size/2), xMin+(size/2), size/2, curr->a);
        comprimirQuadrante(imagem, yMin+(size/2), xMin, size/2, curr->b);
        comprimirQuadrante(imagem, yMin, xMin, size/2, curr->c);
        comprimirQuadrante(imagem, yMin, xMin+(size/2), size/2, curr->d);
        curr->full = (curr->a->full && curr->b->full && curr->c->full && curr->d->full);
    }
}

void QuadTree::insert(Node* &curr, const Color& pixel) {
    if(curr) destroy(curr);

    curr = new Node(pixel);
}

void QuadTree::print(ostream& os, const Node* curr) const {
    if(!curr) return; 
    
    os << "(";
    if(curr->pixel.r != -1 && curr->pixel.g != -1 && curr->pixel.b != -1) {
        os << curr->pixel.r << "," << curr->pixel.g << "," << curr->pixel.b;
    }
    else {
        print(os, curr->a);
        print(os, curr->b);
        print(os, curr->c);
        print(os, curr->d);
    }
    os << ")";
}

bool QuadTree::insertOnLevelH_aux(Node* &curr, const Color& pixel, int h) {
    if(!curr){
        if(h == 1) {
            insert(curr, pixel);
            return true;
        }
        insert(curr, Color(-1,-1,-1));
        curr->full = false;
        return insertOnLevelH_aux(curr->a, pixel, h-1);
    }
    else if(!(curr->full) && curr->pixel.r == -1) {
        if(insertOnLevelH_aux(curr->a, pixel, h-1)) return true;
        if(insertOnLevelH_aux(curr->b, pixel, h-1)) return true;
        if(insertOnLevelH_aux(curr->c, pixel, h-1)) return true;
        if(insertOnLevelH_aux(curr->d, pixel, h-1)) {
            if(curr->d->full) curr->full = true;
            return true;
        }
    }
    else if(curr->pixel.r != -1) {
        return false;
    }
    return false;
}

void QuadTree::gravarQuadranteImagemPPM(PPMImage& imagem, const int yMin, const int xMin, const int yMax, const int xMax, Node* curr) const {
    if(!curr) return;
    if(curr->pixel.r == -1) {
        int avgX = (xMin+xMax)/2, avgY = (yMin+yMax)/2;
        gravarQuadranteImagemPPM(imagem, avgY, avgX, yMax, xMax, curr->a);
        gravarQuadranteImagemPPM(imagem, avgY, xMin, yMax, avgX, curr->b);
        gravarQuadranteImagemPPM(imagem, yMin, xMin, avgY, avgX, curr->c);
        gravarQuadranteImagemPPM(imagem, yMin, avgX, avgY, xMax, curr->d);
    }
    else {
        //cerr << curr->pixel.r << " " << curr->pixel.g << " " << curr->pixel.b << endl;
        for(int j=yMin; j<yMax; j++) {
            for(int i=xMin; i<xMax; i++) {
                imagem.set(j, i, curr->pixel);
                //cerr << j << "," << i << " "; 
            }
            //cerr << endl;
        }
    }
}