#pragma once

#include <iostream>
#include <string>
#include "University.h"
#include "LinkedList.h"

using namespace std;

/*
	Selection Sort
*/
void selectionSort(string** universityData, int size, int index) {
	for (int i = 0; i < size - 1; i++) {
		int minIndex = i;
		for (int j = i + 1; j < size; j++) {
			// Compare based on the type of the column's value
			if (index >= 1 && index < 4) {
				// String column
				if (universityData[j][index] < universityData[minIndex][index]) {
					minIndex = j;
				}
			}
			else {
				// Integer column
				int value1 = stoi(universityData[j][index]);
				int value2 = stoi(universityData[minIndex][index]);
				if (value1 < value2) {
					minIndex = j;
				}
			}
		}

		if (universityData[minIndex][index] != universityData[i][index]) {
			// Swap the elements manually without using swap function
			string temp = universityData[i][index];
			universityData[i][index] = universityData[minIndex][index];
			universityData[minIndex][index] = temp;
		}
	}
}




/*
*   Quick Sort
*/
// Comparison function to determine the order of two strings
bool compareStrings(const string& a, const string& b, int colIndex, bool isAsc) {
	// Sort string in lexicographical order
	if (colIndex >= 1 && colIndex < 4) {
		return (isAsc) ? a < b : a > b;
	}
	else {
		// Integer column
		int value1 = stoi(a);
		int value2 = stoi(b);

		return (isAsc) ? value1 < value2 : value1 > value2;
	}
}

// Swap two strings
void swapStrings(string** a, string** b) {
	string* temp = *a;
	*a = *b;
	*b = temp;
}

// Partition the array
int partition(string** arr, int low, int high, int colIndex, bool isAsc) {
	string* pivot = arr[high];
	int i = low - 1;

	for (int j = low; j < high; j++) {
		if (compareStrings(arr[j][colIndex], pivot[colIndex], colIndex, isAsc)) {
			i++;
			swapStrings(&arr[i], &arr[j]);
		}
	}

	swapStrings(&arr[i + 1], &arr[high]);

	return i + 1;
}

// Quicksort algorithm
void quicksort(string** arr, int low, int high, int colIndex, bool isAsc) {
	if (low < high) {
		int pivotIndex = partition(arr, low, high, colIndex, isAsc);

		quicksort(arr, low, pivotIndex - 1, colIndex, isAsc);
		quicksort(arr, pivotIndex + 1, high, colIndex, isAsc);
	}
}
