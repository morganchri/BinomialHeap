#ifndef BINOMIALHEAP_BINOMIALHEAP_H
#define BINOMIALHEAP_BINOMIALHEAP_H
#include <iostream>
#include <limits>

using namespace std;


typedef struct node{
    int key;
    int degree;
    node* parent;
    node* child;
    node* sibling;
}node_t;

class BinomialHeap {
private:

    node_t* head;
    explicit BinomialHeap() {
        head = nullptr;
    }
    explicit BinomialHeap(int k) {
        head = nullptr;
    }

public:
    static BinomialHeap* makeHeap(int k);
    static BinomialHeap* makeHeap();
    void insert(int k);
    node_t* minimum();
    node_t* extractMin();
    BinomialHeap* heapUnion(BinomialHeap* heap);
    void decreaseKey(node_t* x, int k);
    void nodeRemove(node_t* h, node_t* node);
    node_t* merge(node_t* a);
    void binLink(node_t* y, node_t* z);
    void heapDelete(node_t* x);
    node_t* getHead();
    void printTree(node_t* temp);
    void printHeap();
};

#endif //BINOMIALHEAP_BINOMIALHEAP_H
