#ifndef QUAD_TREE_H
#define QUAD_TREE_H

#include <iostream>
#include <string>
#include "PPMImage.h"
using std::cout;
using std::string;

class Node {
    public:
        Node() : a(NULL), b(NULL), c(NULL), d(NULL), full(false) {};
        Node(const int r, const int g, const int b) : a(NULL), b(NULL), c(NULL), d(NULL), pixel(r, g, b), full(true) {};
        Node(const Color pixel_) : a(NULL), b(NULL), c(NULL), d(NULL), pixel(pixel_.r, pixel_.g, pixel_.b), full(true) {};
        Node *a, *b, *c, *d;
        Color pixel;

        bool full;  
};

class QuadTree {
    public:
        QuadTree() : root(NULL), size(0) {};
        ~QuadTree();
        QuadTree(const QuadTree &other);
        QuadTree& operator=(const QuadTree &other);

        const int getSize() const { return size; };
        void comprimir(const PPMImage& imagem);
        void insertOnLevelH(const Color& pixel, int h);

        void gravarImagemPPM(PPMImage& imagem) const;

        friend ostream &operator<<(ostream& os, const QuadTree& tree);

    private:
        Node* root;
        int size;
        
        void destroy(Node* root);
        Node* copyNodes(const Node* otherRoot) const;
        int calcularSize(Node* root) const;
        void comprimirQuadrante(const PPMImage& imagem, const int yMin, const int xMin, const int size, Node* &curr);
        void insert(Node* &curr, const Color& pixel);
        void print(ostream& os, const Node* curr) const;
        bool insertOnLevelH_aux(Node* &curr, const Color& pixel,int h);
        void gravarQuadranteImagemPPM(PPMImage& imagem, const int yMin, const int xMin, const int yMax, const int xMax, Node* curr) const;
}
;

#endif