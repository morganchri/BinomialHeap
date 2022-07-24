#include <cmath>
#include "BinomialHeap.h"

inline BinomialHeap* makeHeap(int k) {
    auto* heap = new BinomialHeap(k);
    return heap;
}

inline BinomialHeap* makeHeap() {
    auto* heap = new BinomialHeap();
    return heap;
}

inline node_t* BinomialHeap::getHead() {
    return this->head;
}

inline void BinomialHeap::setHead(node_t* node) {
    this->head = node;
}

inline node_t* BinomialHeap::merge(BinomialHeap* a, BinomialHeap* b) {
    node_t* temp = new node();
    node_t* end = temp;

    node_t* l = a->getHead();
    node_t* r = b->getHead();
    if (l == nullptr) {
        return r;
    }
    if (r == nullptr) {
        return l;
    }
    while (l != nullptr || r != nullptr) {
        if (l == nullptr) {
            end->sibling = r;
            end = end->sibling;
            r = r->sibling;
        } else if (r == nullptr) {
            end->sibling = l;
            end = end->sibling;
            l = l->sibling;
        } else {
            if (l->degree < r->degree) {
                end->sibling = l;
                end = end->sibling;
                l = l->sibling;
            } else {
                end->sibling = r;
                end = end->sibling;
                r = r->sibling;
            }
        }
    }
    return temp->sibling;
}

inline void BinomialHeap::heapUnion(BinomialHeap *heap) {
    auto* temp = makeHeap();
    temp->head = merge(this, heap);
    if (temp->head == nullptr) {
        this->head = nullptr;
        return;
    }
    node_t* prevX = nullptr;
    node_t* x = temp->head;
    node_t* nextX = x->sibling;
    while (nextX != nullptr) {
        if (x->degree != nextX->degree
        || (nextX->sibling != nullptr
        && nextX->sibling->degree == x->degree)) {
            prevX = x;
            x = nextX;
        } else if (x->key <= nextX->key) {
            x->sibling = nextX->sibling;
            binLink(nextX, x);
        } else {
            if (prevX == nullptr) {
                temp->head = nextX;
            } else {
                prevX->sibling = nextX;
            }
            binLink(x, nextX);
            x = nextX;
        }
        nextX = x->sibling;
    }
    this->head = temp->head;
}

inline void BinomialHeap::insert(int k) {
    BinomialHeap* temp = makeHeap(k);
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

inline void BinomialHeap::printHeap() {
    node_t* currPtr = head;
    while (currPtr != nullptr) {
        cout<<"B"<<currPtr->degree<<endl;
        cout<<"There are "<<pow(2, currPtr->degree)<<" nodes in this tree"<<endl;
        cout<<"The level order traversal is"<<endl;
        queue<node_t*> q;
        q.push(currPtr);
        while (!q.empty()) {
            node_t* p = q.front();
            q.pop();
            cout<<p->key<<" ";

            if (p->child != nullptr) {
                node_t* tempPtr = p->child;
                while (tempPtr != nullptr) {
                    q.push(tempPtr);
                    tempPtr = tempPtr->sibling;
                }
            }
        }
        currPtr = currPtr->sibling;
        cout<<endl<<endl;
    }
}