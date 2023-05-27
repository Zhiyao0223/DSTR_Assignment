#pragma once

#include <iostream>
#include <string>
#include "University.h"
#include "LinkedList.h"

using namespace std;

/*
	Selection Sort
*/
template <class T>
void selectionSort(LinkedList<T>* uniList) {
	node<T>* current = uniList->head;

	while (current != nullptr) {
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

/*
*   Quick Sort
*/
// Comparison function to determine the order of two strings
bool compareStrings(string& a, string& b, bool isAsc) {
	// Sort in numerical order if both strings are numbers
	if (Validation::isNumber(a) && Validation::isNumber(b)) {
		// Sort in numerical order
		if (isAsc) {
			return stoi(a) < stoi(b);
		}
		else {
			return stoi(a) > stoi(b);
		}
	}

	// Sort string in lexicographical order
	if (isAsc) {
		return a < b;
	}
	else {
		return a > b;
	}
}

// Swap two strings
void swapStrings(string* a, std::string* b) {
	std::string temp = *a;
	*a = *b;
	*b = temp;
}

// Partition the array
int partition(string** arr, int low, int high, int colIndex, bool isAsc) {
	std::string pivot = arr[high][colIndex];
	int i = low - 1;

	for (int j = low; j < high; j++) {
		if (compareStrings(arr[j][colIndex], pivot, isAsc)) {
			i++;
			for (int k = 0; k < colIndex + 1; k++) {
				swapStrings(&arr[i][k], &arr[j][k]);
			}
		}
	}

	for (int k = 0; k < colIndex + 1; k++) {
		swapStrings(&arr[i + 1][k], &arr[high][k]);
	}

	return i + 1;
}

// Quicksort algorithm
void quicksort(std::string** arr, int low, int high, int colIndex, bool isAsc) {
	if (low < high) {
		int pivotIndex = partition(arr, low, high, colIndex, isAsc);

		quicksort(arr, low, pivotIndex - 1, colIndex, isAsc);
		quicksort(arr, pivotIndex + 1, high, colIndex, isAsc);
	}
}
