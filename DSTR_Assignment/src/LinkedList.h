#pragma once

#include <iostream>
using namespace std;

template <class T>
struct node {
	T data;
	node<T>* prevAddress;
	node<T>* nextAddress;
};


template <class T>
class LinkedList {
public:
	node<T>* head;
	node<T>* tail;
	int size;

	LinkedList() {
		head = tail = NULL;
	}

	LinkedList(T* data) {
		node<T>* newNode;
		head = tail = newNode;
	}




	void displayAll() {
		node<T>* tmp = head;

		while (tmp != NULL) {
			cout << tmp->data << endl;
			tmp = tmp->next;
		}
	}

	node<T>* createNewNode(T* data) {
		node<T>* newNode = new node<T>;
		newNode->nextAddress = newNode->prevAddress = NULL;
		return newNode;
	}

	void insertToFrontList(T* data) {
		node<T>* newNode = createNewNode(data);

		if (head == NULL) {
			head = tail = newNode;
		}
		else {
			newNode->nextAddress = head;
			head->prevAddress = newNode;
			head = newNode;
		}
		size++;
	}

	bool insertToSpecificLocation(int index, T* data) {
		if (index >= size) {
			cout << "Error: Invalid request for adding data to specific location." << endl;
			return false;
		}

		int counter = 0;
		node<T>* tmp = head;
		node<T>* newNode = createNewNode(data);

		while (tmp != NULL) {
			if (counter == index) {
				newNode = tmp->prevAddress;
				newNode->nextAddress = tmp;
				tmp->prevAddress = newNode;

				return true;
			}
			tmp = tmp->nextAddress;
			counter++;
		}
		return false;
	}

	void insertToEndList(T* data) {
		node<T>* newNode = createNewNode(data);

		if (tail == NULL) {
			head = tail = newNode;
		}
		else {
			newNode->prevAddress = tail;
			tail->nextAddress = newNode;
			tail = newNode;
		}
		size++;
	}

	T deleteFromFrontList() {
		if (isEmpty) {
			cout << "No item in the list." << endl;
			return NULL;
		}

		node<T>* temp = head;
		T data = temp->data;

		head = head->nextAddress;
		delete temp;
		size--;

		return data;
		
	}

	T deleteFromSpecificLocation(int index) {
		if (isEmpty) {
			cout << "No item in the list." << endl;
			return NULL;
		} else if (index >= size) {
			cout << "Error: Invalid request for adding data to specific location." << endl;
			return NULL;
		}

		int counter = 0;
		node<T>* current = head;
		T data = NULL;

		while (current != NULL) {
			if (counter == index) {
				data = current->data;
				
				node<T>* prev = current->prevAddress;
				prev->nextAddress = current->nextAddress;
				node<T>* next = current->nextAddress;
				next->prevAddress = prev;
				
				delete current;

				return data;
			}
			current = current->nextAddress;
			counter++;
		}
	}

	T deleteFromEndList() {
		if (isEmpty) {
			cout << "No item in the list." << endl;
			return NULL;
		}

		node<T>* temp = tail;
		T data = temp->data;

		tail = tail->prevAddress;
		delete temp;
		size--;

		return data;
	}


	// Check if list is empty
	bool isEmpty() {
		return (size == 0);
	}




	//// Getter Function
	//node<T>* getFirstElement() {
	//	return front;
	//}

	//node<T>* getLastElement() {
	//	return rear;
	//}
};