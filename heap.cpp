/*#include <heap.h>
HeapPecados :: HeapPecados(){

}


int HeapPecados :: getSize(){
    return list.size();
}


void HeapPecados::swap(int child, int parent) {
    Persona* temp;
    temp = list[child];
    list[child] = list[parent];
    list[parent] = temp;
}


int HeapPecados :: getParent(int child) {
    if (child % 2 == 0)
        return (child /2 ) -1;
    else
        return child/2;

}


int HeapPecados :: getLeftChild(int parent){
    return 2*parent +1;
}


int HeapPecados :: getRightChild(int parent){
    return 2 * parent + 2;
}


void HeapPecados :: insert(Persona* value) {

    list.push_back(value);
    bubbleUp();

}


void HeapPecados:: bubbleUp() {
    int child = list.size() - 1;
    int parent = getParent(child);

    while (list[child]->sumatoriaDePecados() > list[parent]->sumatoriaDePecados() && child >=0 && parent >= 0) {

        swap(child, parent);
        child = parent;
        parent = getParent(child);

    }


}



Persona* HeapPecados :: remove() {
    int child = list.size()  - 1;
    swap(child, 0);

    Persona* value = list.back();
    list.pop_back();

    bubbleDown();

    return value;


}



void HeapPecados :: bubbleDown() {
    int parent = 0;

    while (1) {
        int left = getLeftChild(parent);
        int right = getRightChild(parent);
        int length = list.size();
        int largest = parent;

        if (left < length && list[left]->sumatoriaDePecados() > list[largest]->sumatoriaDePecados())
            largest = left;

        if (right < length && list[right]->sumatoriaDePecados() > list[largest]->sumatoriaDePecados())
            largest = right;

        if (largest != parent) {
            swap(largest, parent);
            parent = largest;
        }
        else
            break;


    }

}*/
