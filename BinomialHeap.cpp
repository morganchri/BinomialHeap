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
    auto* temp = new node();
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

inline void BinomialHeap::reverse(node_t* h) {
    if (h->sibling != nullptr) {
        reverse(h->sibling);
        (h->sibling)->sibling = h;
    }
    else {
        this->head = h;
    }
}

inline node_t* BinomialHeap::extractMin() {
    node_t* minNode = this->minimum();
    node_t* prevX = nullptr;
    node_t* x = this->head;
    while (x != minNode)
    {
        prevX = x;
        x = x->sibling;
    }
    if (prevX == nullptr) {
        this->head = x->sibling;
    }
    else {
        prevX->sibling = x->sibling;
    }
    node_t *revChild = nullptr;
    node_t* curr = minNode->child;
    while (curr != nullptr)
    {
        node_t* next = curr->sibling;
        curr->sibling = revChild;
        revChild = curr;
        curr = next;
    }
    BinomialHeap* H = makeHeap();
    H->head = revChild;
    this->merge(this, H);
    return minNode;
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

inline void BinomialHeap::printHeap(node_t* h) {
    //node_t* currPtr = head;
    //while (currPtr != nullptr) {
    //    cout<<"B"<<currPtr->degree<<endl;
    //    cout<<"There are "<<pow(2, currPtr->degree)<<" nodes in this tree"<<endl;
    //    cout<<"Nodes in this heap"<<endl;
    //    queue<node_t*> q;
    //    q.push(currPtr);
    //    while (!q.empty()) {
    //        node_t* p = q.front();
    //        q.pop();
    //        cout<<p->key<<" ";

    //        if (p->child != nullptr) {
    //            node_t* tempPtr = p->child;
    //            while (tempPtr != nullptr) {
    //                q.push(tempPtr);
    //                tempPtr = tempPtr->sibling;
    //            }
    //        }
    //    }
    //    currPtr = currPtr->sibling;
    //    cout<<endl<<endl;
    //}
    while (h) {
        cout << h->key << " ";
        printHeap(h->child);
        h = h->sibling;
    }
}