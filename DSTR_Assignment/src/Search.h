#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <regex>
#include "LinkedList.h"
using namespace std;

//Binary Search (Modified Version)
template <class T>
LinkedList<T>* binarySearch(LinkedList<T>* list, string key, int columnIndex) {
    if (list == nullptr || list->head == nullptr) {
        return nullptr;  // Empty list, return nullptr
    }

    LinkedList<T>* result = nullptr;
    node<T>* start = list->head;
    node<T>* end = nullptr;

    while (start != end && start->nextAddress != end) {
        node<T>* mid = getMiddleNode(start, end);
        if (mid->data.getColumn(columnIndex) == key) {
            if (result == nullptr) {
                result = new LinkedList<T>();
            }
            result->insertToEndList(mid->data);
            // Include the middle node in the subsequent search range
            searchRange(start, mid, columnIndex, key, result);
            searchRange(mid->nextAddress, end, columnIndex, key, result);
            break;  // Found a match, no need to continue searching
        }
        else if (mid->data.getColumn(columnIndex) < key) {
            start = mid->nextAddress;
        }
        else {
            end = mid;
        }
    }

    return result;
}



template <class T>
void searchRange(node<T>* start, node<T>* end, int columnIndex, string key, LinkedList<T>* result) {
    node<T>* left = start;
    node<T>* right = end;

    while (left != right && left->nextAddress != right) {
        node<T>* mid = getMiddleNode(left, right);
        if (mid->data.getColumn(columnIndex) == key) {
            result->insertToEndList(mid->data);
            // Include the middle node in the subsequent search range
            searchRange(start, mid, columnIndex, key, result);
            searchRange(mid->nextAddress, end, columnIndex, key, result);
            return;  // Found a match, no need to continue searching
        }
        else if (mid->data.getColumn(columnIndex) < key) {
            left = mid->nextAddress;
        }
        else {
            right = mid;
        }
    }

    // Check if the last node matches the key
    if (left != nullptr && left->data.getColumn(columnIndex) == key) {
        result->insertToEndList(left->data);
    }
}


template <class T>
node<T>* getMiddleNode(node<T>* start, node<T>* end) {
    node<T>* slow = start;
    node<T>* fast = start;

    while (fast != end && fast->nextAddress != end) {
        slow = slow->nextAddress;
        fast = fast->nextAddress->nextAddress;
    }

    return slow;
}
