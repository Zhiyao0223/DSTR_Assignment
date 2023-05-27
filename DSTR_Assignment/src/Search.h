#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <regex>
#include "LinkedList.h"
using namespace std;

// Binary Search (Modified Version for Linked List)
template <class T>
LinkedList<T>* binarySearch(LinkedList<T>* list, string key, int columnIndex) {
	if (list == nullptr || list->head == nullptr) {
		return nullptr;  // Empty list, return nullptr
	}

	LinkedList<T>* result = nullptr;
	node<T>* start = list->head;
	node<T>* end = getEndNode(start);

	while (start != end) {
		node<T>* mid = getMiddleNode(start, end);
		if (mid->data.getColumn(columnIndex) == key) {
			if (result == nullptr) {
				result = new LinkedList<T>();
			}
			result->insertToEndList(&(mid->data));
			// Continue searching in the left and right halves
			searchRange(start, mid->prevAddress, columnIndex, key, result);
			searchRange(mid->nextAddress, end, columnIndex, key, result);
			break;  // Found a match, no need to continue searching
		}
		else if (mid->data.getColumn(columnIndex) > key) {
			start = mid->nextAddress;
		}
		else {
			end = mid->prevAddress;
		}
	}

	// Check if the last node matches the key
	if (start != nullptr && start->data.getColumn(columnIndex) == key) {
		if (result == nullptr) {
			result = new LinkedList<T>();
		}
		result->insertToEndList(&(start->data));
	}

	return result;
}

template <class T>
void searchRange(node<T>* start, node<T>* end, int columnIndex, string key, LinkedList<T>* result) {
	node<T>* current = start;
	while (current != end) {
		if (current->data.getColumn(columnIndex) == key) {
			result->insertToEndList(&(current->data));
		}
		current = current->nextAddress;
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

template <class T>
node<T>* getEndNode(node<T>* start) {
	node<T>* current = start;
	while (current->nextAddress != nullptr) {
		current = current->nextAddress;
	}
	return current;
}
