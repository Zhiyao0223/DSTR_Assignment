#pragma once

#include <iostream>
#include "FileIO.h"
#include "University.h"
#include "LinkedList.h"
using namespace std;

template <class T>
void selectionSort(LinkedList<T>* list, string key, int index) {
    FileIO file;
    LinkedList<University>* uniList = file.readFile();
    node<T>* current = list->head;

    while(current != nullptr) {
        node<T>* minNode = current;
        node<T>* nextNode = current->nextAddress;

        while (nextNode != nullptr) {
            if (nextNode->nextAddress < minNode->data) {
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
