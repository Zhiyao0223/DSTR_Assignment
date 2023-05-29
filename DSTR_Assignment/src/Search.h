#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <regex>
#include "LinkedList.h"
#include "Sort.h"
using namespace std;

string** binarySearch(string** array, int arraySize, string key, int columnIndex, int* count) {
	string* tmpArr = new string[arraySize];
	for (int i = 0; i < arraySize; i++) {
		tmpArr[i] = "0";
	}

	int low = 0;
	int high = arraySize - 1;
	int resultCount = 0;  // Count the number of matching rows

	// Count the number of matching rows
	while (low <= high) {
		int mid = low + (high - low) / 2;

		if (array[mid][columnIndex] == key) {
			tmpArr[resultCount] = to_string(mid);

			// Key found, increment the result count
			resultCount++;
			// Continue counting other matching keys
			int left = mid - 1;
			int right = mid + 1;
			while (left >= low && array[left][columnIndex] == key) {
				tmpArr[resultCount] = to_string(left);
				resultCount++;
				left--;
			}
			while (right <= high && array[right][columnIndex] == key) {
				tmpArr[resultCount] = to_string(right);
				resultCount++;
				right++;
			}
			break;
		}

		if (array[mid][columnIndex] < key) {
			low = mid + 1;
		}
		else {
			high = mid - 1;
		}
	}

	if (resultCount == 0) return NULL;

	// Create the result array with the appropriate size
	string** resultArray = new string * [resultCount + 1];

	// Copy the matching rows to the result array
	for (int i = 0; i < resultCount; i++) {
		int index = stoi(tmpArr[i]);
		resultArray[i] = array[index];
	}

	*count = resultCount;

	return resultArray;
}

//Linear Search
template <class T>
LinkedList<T>* linearSearch(LinkedList<T>* list, string key, int columnIndex) {
	if (list == nullptr || list->head == nullptr) {
		return nullptr;  // Empty list, return nullptr
	}

	LinkedList<T>* result = nullptr;
	node<T>* current = list->head;
	while (current != nullptr) {
		if (current->data.getColumn(columnIndex) == key) {
			if (result == nullptr) {
				result = new LinkedList<T>();
			}
			result->insertToEndList(&(current->data));
		}
		current = current->nextAddress;
	}
	return result;
}
