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

        cout << array[i] << endl;
    }
    BinomialHeap* heap = heap->makeHeap();
    for (int i = 0; i < size; ++i) {
        heap->insert(array[i]);
    }
    heap->printHeap();
    return 0;
}
