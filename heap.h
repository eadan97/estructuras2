#ifndef HEAP_H
#define HEAP_H
#include <persona.h>
#include <iostream>
#include <vector>

using namespace std;


class HeapPecados {
    vector<Persona*> list;

    void bubbleUp() {
        int child = list.size() - 1;
        int parent = getParent(child);

        while (child >=0 && parent >= 0&& list[child]->sumatoriaDePecados() > list[parent]->sumatoriaDePecados() ) {

            swap(child, parent);
            child = parent;
            parent = getParent(child);

        }


    }
    void bubbleDown(){
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

    }
    void swap(int child, int parent){
        Persona* temp;
        temp = list[child];
        list[child] = list[parent];
        list[parent] = temp;
    }
    int getLeftChild(int parent){
        return 2*parent +1;
    }


    int getRightChild(int parent){
        return 2 * parent + 2;
    }
    int getParent(int child){
        if (child % 2 == 0)
            return (child /2 ) -1;
        else
            return child/2;

    }
public:
    HeapPecados(){

    }
    void insert(Persona* value ){

        list.push_back(value);
        bubbleUp();

    }
    Persona* remove(){
        int child = list.size()  - 1;
        swap(child, 0);

        Persona* value = list.back();
        list.pop_back();

        bubbleDown();

        return value;


    }

    int getSize(){
        return list.size();
    }

};



#endif // HEAP_H
