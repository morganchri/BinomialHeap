#include "BinomialHeap.h"

inline BinomialHeap* BinomialHeap::makeHeap(int k) {
    auto* heap = new BinomialHeap(k);
    return heap;
}

inline BinomialHeap* BinomialHeap::heapUnion(BinomialHeap *heap) {
    auto* temp = new BinomialHeap();
    temp->head = merge(this, heap);
    if (temp->head == nullptr) {
        return temp;
    }
}

inline void BinomialHeap::insert(node_t* x, int k) {
    BinomialHeap* temp = BinomialHeap::makeHeap(k);
    this->heapUnion(temp);
}
