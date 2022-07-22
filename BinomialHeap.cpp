#include "BinomialHeap.h"

inline BinomialHeap* BinomialHeap::makeHeap(int k) {
    auto* heap = new BinomialHeap(k);
    return heap;
}

inline BinomialHeap* BinomialHeap::makeHeap() {
    auto* heap = new BinomialHeap();
    return heap;
}

inline BinomialHeap* BinomialHeap::heapUnion(BinomialHeap *heap) {
    auto* temp = BinomialHeap::makeHeap();
    temp->head = merge(this, heap);
    if (temp->head == nullptr) {
        return temp;
    }
    node_t* prevX = nullptr;
    node_t* x = temp->head;
    node_t* nextX = x->sibling;
    while (nextX != nullptr) {
        if ((x->degree != nextX->degree) || (nextX->sibling != nullptr
        && nextX->sibling->degree == x->degree)) {
            prevX = x;
            x = nextX;
        } else if (x->key <= nextX->key) {
            x->sibling = nextX->sibling;
            binLink(nextX,x);
        } else if (prevX == nullptr) {
            temp->head = nextX;
        } else {
            prevX->sibling = nextX;
            binLink(x, nextX);
            x = nextX;
        }
        nextX = x->sibling;
    }
    return temp;
}

inline void BinomialHeap::insert(node_t* x, int k) {
    BinomialHeap* temp = BinomialHeap::makeHeap(k);
    this->heapUnion(temp);
}

inline node_t* BinomialHeap::minimum() {
    node_t* y = nullptr;
    node_t* x = this->head;
    int min = std::numeric_limits<int>::max();
    while (x != nullptr) {
        if (x->key < min) {
            min = x->key;
            y = x;
        }
        x = x->sibling;
    }
    return y;
}

inline void BinomialHeap::binLink(node_t *y, node_t *z) {
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree = z->degree + 1;
}

inline node_t* BinomialHeap::extractMin() {
    node_t* prev = nullptr;
    node_t* min = this->head;

    int minKey = this->head->key;
    node_t* curr = this->head;
    while (curr->sibling != nullptr)
    {
        if (curr->sibling->key < minKey) {
            minKey = curr->sibling->key;
            prev = curr;
            min = curr->sibling;
        }
        curr = curr->sibling;
    }

    if (prev == nullptr && min->sibling == nullptr) {
        this->head = nullptr;
    } else if (prev == nullptr) {
        this->head = min->sibling;
    } else {
        prev->sibling = min->sibling;
    }
    if (min->child != nullptr) {
        min->child->sibling = nullptr;
    }


}

