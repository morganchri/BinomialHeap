#include <cstdlib>
#include <ctime>
#include <iostream>
#include "BinomialHeap.cpp"

using namespace std;

int main() {

    int size;
    cout<< "how big do you want the array?" << endl;
    cin >> size;

    int array[size];

    srand((unsigned)time(0));

    for(int i=0; i<size; i++){
        array[i] = (rand()%100)+1;

        //cout << array[i] << endl;
    }
    BinomialHeap* heap = makeHeap(array[0]);
    for (int i = 1; i < size; ++i) {
        heap->insert(array[i]);
    }
    heap->printHeap(heap->getHead());
    while (true) {
        string x;
        cout << "\nInput a task\n";
        cin >> x;
        if (x == "Print" || x == "print") {
            heap->printHeap(heap->getHead());
        } else if (x == "Minimum"|| x == "minimum") {
            cout << heap->minimum()->key;
        } else if (x == "extract" || x == "Extract") {
            cout << "Extracting min..." << heap->extractMin()->key;
        } else if (x == "delete" || x == "Delete") {
            int y;
            cout << "input the key of a node to delete: ";
            cin >> y;
            heap->heapDelete(heap->findNode(heap->getHead(), y));
        } else if (x == "decrease" || x == "Decrease") {
            int y;
            int k;
            cout << "input the key of a node to decrease: ";
            cin >> y;
            cout << "input the new key: ";
            cin >> k;
            heap->decreaseKey(heap->findNode(heap->getHead(), y), k);
        } else if (x == "Quit" || x == "quit") {
            break;
        }
    }
    //cout << "\n";
    //cout << "The minimum is: " << heap->minimum()->key << "\n";
    //cout << "Extracting min..." << heap->extractMin()->key << "\n";
    //cout << "The minimum is: " << heap->minimum()->key << "\n";
    //heap->printHeap(heap->getHead());
    return 0;
}
