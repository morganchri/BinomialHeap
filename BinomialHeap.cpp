#include "BinomialHeap.h"

inline BinomialHeap* BinomialHeap::makeHeap(int k) {
    auto* heap = new BinomialHeap(k);
    return heap;
}

inline BinomialHeap* BinomialHeap::makeHeap() {
    auto* heap = new BinomialHeap();
    return heap;
}

inline node_t* BinomialHeap::getHead() {
    return this->head;
}

inline node_t* BinomialHeap::merge(BinomialHeap* A, BinomialHeap* B) {
    if (A->getHead() == nullptr) {
        return B->getHead();
    }
    if (B->getHead() == nullptr) {
        return A->getHead();
    }
    node_t* head;
    node_t* h1 = A->getHead();
    node_t* h2 = B->getHead();
    node_t* tail;
    if (A->getHead()->degree <= B->getHead()->degree) {
        head = A->getHead();
        h1 = h1->sibling;
    } else {
        head = B->getHead();
        h2 = h2->sibling;
    }
    tail = head;
    while (h1 != nullptr && h2 != nullptr) {
        if (h1->degree <= h2->degree) {
            tail->sibling = h1;
            h1 = h1->sibling;
        } else {
            tail->sibling = h2;
            h2 = h2->sibling;
        }
        tail = tail->sibling;
    }
    tail->sibling = (h1 != nullptr) ? h1:h2;
    return head;
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

inline void BinomialHeap::nodeRemove(node_t *h, node_t *node) {
    if (h == this->head) {
        this->head = head->sibling;
    } else {
        node->sibling = h->sibling;
    }
    node_t *new_head = nullptr;
    node_t *child = head->child;
    while( child != nullptr )
    {
        node_t *next = child->sibling;
        child->sibling = new_head;
        child->parent = nullptr;
        new_head = child;
        child = next;
    }

    BinomialHeap *temp = makeHeap();
    temp->head = new_head;
    this->heapUnion(temp);
    delete(temp);
}

inline node_t* BinomialHeap::extractMin() {
    node_t* prev = nullptr;
    node_t* min = this->head;

    int minKey = this->head->key;
    node_t* curr = this->head;
    while (curr->sibling != nullptr) {
        if (curr->sibling->key < minKey) {
            minKey = curr->sibling->key;
            prev = curr;
            min = curr->sibling;
        }
        curr = curr->sibling;
    }
    nodeRemove(min, prev);
    return min;
}

inline void BinomialHeap::decreaseKey(node_t* x, int k) {
    if (k > x->key) {
        cerr << "new key is greater than the current key";
    }
    x->key = k;
    node_t* y = x;
    node_t* z = y->parent;
    while (z != nullptr && y->key < z->key) {
        swap(y->key, z->key);
        y = z;
        z = y->parent;
    }
}

inline void BinomialHeap::heapDelete(node_t* x) {
    this->decreaseKey(x, -std::numeric_limits<int>::max());
    this->extractMin();
}