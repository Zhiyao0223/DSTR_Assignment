#pragma once

#include <iostream>
#include "FileIO.h"
#include "University.h"
#include "LinkedList.h"
using namespace std;

template <class T>
void selectionSort(LinkedList<T>* uniList) {
    //FileIO file;
    //LinkedList<University>* uniList = file.readFile();
    node<T>* current = uniList->head;
    

    while(current != nullptr) {
        node<T>* minNode = current;
        node<T>* nextNode = current->nextAddress;

        while (nextNode != nullptr) {
            if (nextNode->data < minNode->data) {
                minNode = nextNode;
            }
            nextNode = nextNode->nextAddress;
        }

        if (minNode != current) {
            std::swap(minNode->data, current->data);
        }

        current = current->nextAddress;
    }
}
