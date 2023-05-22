#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <regex>
#include "LinkedList.h"
using namespace std;

template <class T>
//Needed to be sorted first, the code not include any sorting algorithm
LinkedList<T>* binarySearch(LinkedList<T>* list, string key, int index) {
    if (list == nullptr || list->head == nullptr) {
        return nullptr;  // Empty list, return nullptr
    }

    if (index < 0 || index >= list->head->data.size()) {
        return nullptr;  // Invalid index, return nullptr
    }

    LinkedList<T>* result = nullptr;
    node<T>* left = list->head;
    node<T>* right = nullptr;

    while (left != right) {
        node<T>* slow = left;
        node<T>* fast = left->nextAddress;
        while (fast != right && fast->nextAddress != right) {
            slow = slow->nextAddress;
            fast = fast->nextAddress->nextAddress;
        }

        if (slow->data[index] == key) {
            result = new LinkedList<T>();
            result->insertToEndList(slow->data);
            return result;
        }
        else if (slow->data[index] < key) {
            left = slow->nextAddress;
        }
        else {
            right = slow;
        }
    }

    return result;
}
