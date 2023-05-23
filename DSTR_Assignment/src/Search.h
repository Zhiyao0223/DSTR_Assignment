#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <regex>
#include "LinkedList.h"
using namespace std;

// Binary search
template <class T>
LinkedList<T>* binarySearch(LinkedList<T>* list, string key, int index) {
	LinkedList<T>* result = new LinkedList<T>();
	node<T>* tmp = list->head;
	int counter = 0;
	while (tmp != NULL) {
		if (tmp->data[index] == key) {
			result->insertAtEnd(tmp->data);
			counter++;
		}
		tmp = tmp->nextAddress;
	}
	if (counter == 0) return NULL;
	return result;
};
