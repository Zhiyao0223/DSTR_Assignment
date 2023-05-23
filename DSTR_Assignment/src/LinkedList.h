#pragma once

#include <iostream>
#include "Util.h"
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

	LinkedList<T>() {
		node<T>* newNode = NULL;
		head = tail = newNode;
	}


	node<T>* createNewNode(T* data) {
		node<T>* newNode = new node<T>();
		newNode->data = *data;
		newNode->nextAddress = newNode->prevAddress = NULL;
		return newNode;
	}

	/*
		Set to previous element according to index
		@param data - Class node
		@param counter - Number of element to move forward  
		@return New pointer location of the node
	*/
	node<T>* setToPreviousElement(node<T>* data, int counter) {
		while (counter > 0) {
			data = data->prevAddress;
			if (data == NULL) return NULL;
			counter--;
		}
		return data;
	}


	// Display info by pages
	node<T>* displayAll() {
		node<T>* tmp = head;
		T test;
		string option = "";
		int counter = 0;
		const int MAX_ITEM_PER_PAGE = 5;

		while (tmp != NULL) {
			if (counter < MAX_ITEM_PER_PAGE) {
				test = tmp->data;
				test.display();
				tmp = tmp->nextAddress;
				counter++;
			}
			else {
				cout << endl << "Wish to proceed?" << endl;
				cout << "[1] Add University to Favourite" << endl;
				cout << "[2] Previous Page" << endl;
				cout << "[3] Next Page" << endl;
				cout << "[4] Return" << endl;
				cout << "Option: ";

				getline(cin, option);

				// Set to selected record
				if (option == "1") {
					cout << endl <<"Please enter the index number of university you wish to add: ";
					getline(cin, option);
					cout << endl;

					if (option < "1" || option > to_string(counter)) {
						cerr << "Invalid option. Returning..." << endl;
						Util::sleep(1);
						return NULL;
					}

					node <T>* newPointer = setToPreviousElement(tmp, counter - stoi(option) + 1);

					if (newPointer == NULL) {
						cout << "Error in extracting university details" << endl;
						return NULL;
					}
					else return newPointer;
				}
				// Set to previous five records
				else if (option == "2") {
					node<T>* newPointer = setToPreviousElement(tmp, 2 * MAX_ITEM_PER_PAGE);

					if (newPointer == NULL) {
						cout << "No previous page available!" << endl;
						continue;
					}
					else tmp = newPointer;
				}
				// Set to next five records
				else if (option == "3") {
					// Do nothing
				}
				// Return to previous page
				else if (option == "4") {
					return NULL;
				}
				// Also return to previous page if invalid numeric input
				else {
					cerr << "Invalid option. Returning..." << endl;
					Util::sleep(2);
					return NULL;
				}
				counter = 0;
				Util::sleepClean(2);
				return NULL;
			}


		}
	}


	/*
		Insert class data to head of linked list
		@param data - Class data
	*/
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

	
	/*
		Insert node to specific location in linked list
		@param index - Index location of new node
		@param data - node to be inserted
		@return Insertion status
	*/
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


	/*
		Insert node to end of list
		@param data - Inserted data
	*/
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


	/*
		Delete node from head of linked list
		@return Deleted data in class format
	*/
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


	/*
		Delete node from specific location of linked list
		@param index - Location of node to be deleted
		@return Deleted data in class format
	*/
	T deleteFromSpecificLocation(int index) {
		if (isEmpty()) {
			cout << "No item in the list." << endl;
			return T();
		} else if (index >= size) {
			cout << "Error: Invalid request for adding data to specific location." << endl;
			return T();
		}

		int counter = 0;
		node<T>* current = head;
		T data = T();

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


	/*
		Delete node from end of linked list
		@return Deleted data in class format
	*/
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


	/*
		Check if list is empty
		@return True if list is empty
	*/
	bool isEmpty() {
		return (size == 0);
	}


	// Check for user login status
	T* lookUpProfile(string tmpName, string tmpPass) {
		node<T>* current = head;
		T* classData;
		int counter = 0;

		while (current != NULL) {
			classData = &current->data;

			if (classData->getUsername() == tmpName && classData->getPassword() == tmpPass) {
				return classData;
			}
			current = current->nextAddress;
		}
		return NULL;
	}

	// Get last UID in linked list and add one to its, in progress
	int getNewUID() {
		int tmp = 0;
		node<T>* dataNode = head;

		while (dataNode != NULL) {
			tmp = dataNode->data.getUID();
			dataNode = dataNode->nextAddress;
		}
		return tmp + 1;
	}
};