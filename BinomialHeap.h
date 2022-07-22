#ifndef BINOMIALHEAP_BINOMIALHEAP_H
#define BINOMIALHEAP_BINOMIALHEAP_H

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
    void insert(node_t* x, int k);
    void minimum();
    void ExtractMin() ;
    BinomialHeap* heapUnion(BinomialHeap* heap);
    void decreaseKey();
    void heapDelete();
    node_t* merge(BinomialHeap* A, BinomialHeap* B);
};


#endif //BINOMIALHEAP_BINOMIALHEAP_H
