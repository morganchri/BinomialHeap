#ifndef BINOMIALHEAP_BINOMIALHEAP_H
#define BINOMIALHEAP_BINOMIALHEAP_H
#include <iostream>
#include <limits>
#include <queue>

using namespace std;


typedef struct node{
    int key;
    int degree;
    node* parent;
    node* child;
    node* sibling;
    node() {
        key = 0;
        degree = 0;
        parent = nullptr;
        child = nullptr;
        sibling = nullptr;
    }
    node(int k) {
        key = k;
        degree = 0;
        parent = nullptr;
        child = nullptr;
        sibling = nullptr;
    }
}node_t;

class BinomialHeap {
private:
    node_t* head;
public:
    BinomialHeap() {
        head = nullptr;
    }
    BinomialHeap(int k) {
        head = new node(k);
    }
    node_t* minimum();
    node_t* extractMin();
    void heapUnion(BinomialHeap* heap);
    void decreaseKey(node_t* x, int k);
    void nodeRemove(node_t* h, node_t* node);
    node_t* merge(BinomialHeap* a, BinomialHeap* b);
    void binLink(node_t* y, node_t* z);
    void heapDelete(node_t* x);
    node_t* getHead();
    void setHead(node_t*);
    void printTree(node_t* temp);
    void printHeap();
    void insert(int k);
};

static BinomialHeap* makeHeap(int k);
static BinomialHeap* makeHeap();

#endif //BINOMIALHEAP_BINOMIALHEAP_H
