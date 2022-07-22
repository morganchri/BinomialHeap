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
    void insert(node_t* x, int k);
    node_t* minimum();
    node_t* extractMin();
    BinomialHeap* heapUnion(BinomialHeap* heap);
    void decreaseKey();
    void heapDelete();
    node_t* merge(BinomialHeap* A, BinomialHeap* B);
    void binLink(node_t* y, node_t* z);
};



#endif //BINOMIALHEAP_BINOMIALHEAP_H
