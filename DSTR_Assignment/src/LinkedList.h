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

	/*
		Used to create new node for linked list. Implemented insertion function.
		@param data - Class data
		@return New node
	*/
	node<T>* createNewNode(T* data) {
		node<T>* newNode = new node<T>();
		newNode->data = *data;
		newNode->nextAddress = newNode->prevAddress = NULL;
		return newNode;
	}

	/*
		Set to previous element according to index. Used in displayAll() function.
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
	/*
		Display linked list elements by pages.
		@return Pointer to selected node by input index
	*/
	node<T>* displayAllUniversity() {
		Util::printHeader("University List");

		// Initialize variables
		node<T>* tmp = head;
		T test;
		string option = "";
		int counter = 0;
		const int MAX_ITEM_PER_PAGE = 5;

		// Display all elements in linked list
		while (tmp != NULL) {
			// Continue display if elements are less than max limit per page. Prompt if reach max limit.
			if (counter < MAX_ITEM_PER_PAGE) {
				cout << endl << "[" << counter + 1 << "]" << endl;
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
					cout << endl << "Please enter the index number of university you wish to add: ";
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
						tmp = setToPreviousElement(tmp, MAX_ITEM_PER_PAGE-1);
						counter = 0;
						Util::sleepClean(1);
						continue;
					}
					else {
						tmp = newPointer;
						Util::printHeader("University List");
					}
				}
				// Set to next five records
				else if (option == "3") {
					Util::printHeader("University List");
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

		if (tail == NULL || head == NULL) {
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
		if (isEmpty()) {
			cout << "No item in the list." << endl;
			return T();
		}

		node<T>* temp = head;
		T data = temp->data;

		if (head == tail) {
			head = tail = NULL;
		}
		else {
			head = head->nextAddress;
			head->prevAddress = NULL;
		}

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
		}
		else if (index >= size) {
			cout << "Error: Invalid request for adding data to specific location." << endl;
			return T();
		}
		else if (index == 0) {
			return deleteFromFrontList();
		}
		else if (index == size - 1) {
			return deleteFromEndList();
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
		if (isEmpty()) {
			cout << "No item in the list." << endl;
			return T();
		}

		node<T>* temp = tail;
		T data = temp->data;

		tail = tail->prevAddress;
		tail->nextAddress = NULL;
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

	/*
		Check for user credential based on input
		@param tmpName - Input username
		@param tmpPass - Input password
		@return Pointer to class data if found, NULL if not found
	*/
	T* lookUpProfile(string tmpName, string tmpPass) {
		// Initialize variables
		node<T>* current = head;
		T* classData;
		int counter = 0;

		// Loop through linked list and compare matched data
		while (current != NULL) {
			classData = &current->data;

			if (classData->getUsername() == tmpName && classData->getPassword() == tmpPass) {
				return classData;
			}
			current = current->nextAddress;
		}
		return NULL;
	}

	// Get last UID in linked list and add one to it
	int getNewUID() {
		// Initialize variables
		int tmp = 0;
		node<T>* dataNode = head;

		// Loop through last node in linked list and return its ID + 1
		while (dataNode != NULL) {
			tmp = dataNode->data.getUID();
			dataNode = dataNode->nextAddress;
		}
		return tmp + 1;
	}

	// Get username from linked list
	string getName(LinkedList<T>* list, int searchId) {
		// Initialize variables
		node<T>* current = list->head;

		// Loop through linked list and compare matched data
		while (current != NULL) {
			if (current->data.getUID() == searchId) {
				return current->data.getUsername();
			}
			current = current->nextAddress;
		}
		return "";
	}

	/*
		Swap two nodes in linked list
		@param node1 - First node
		@param node2 - Second node
		@return swap status
	*/
	//bool swapNode(node<T>* node1, node<T>* node2) {
	//	if (node1 == NULL || node2 == NULL) {
	//		return false;
	//	}

	//	T tmp = node1->data;
	//	node1->data = node2->data;
	//	node2->data = tmp;

	//	return true;
	//}

	/*
		Convert Linked list to array
		@return 2D string array
	*/
	string** convertTo2DArray() {
		// Initialize variables
		node<T>* current = this->head;
		int numCols = current->data.getDataCount();
		int numRows = this->size;
		string* tmpData;

		// Create 2D array
		int row = 0;
		string** newData = new string * [numRows];
		for (int i = 0; i < numRows; i++) {
			newData[i] = new string[numCols];
		}

		// Loop through linked list
		while (current != NULL) {
			tmpData = current->data.toStringArray();

			// Copy data to 2D array
			for (int i = 0; i < numCols; i++) {
				newData[row][i] = tmpData[i];
			}
			current = current->nextAddress;
			row++;
		}
		return newData;
	}

	/*
		Convert 2D array to linked list
		@param dataList - 2D string array
		@param totalRow - Total row of 2D array
	*/
	void convertToLinkedList(string** dataList, int totalRow) {
		// Initialize variables
		node<T>* current = head;
		int currentRow = 0;

		// Loop through 2D array and add data to linked list
		while (currentRow != totalRow) {
			T* data = new T();
			data->setColumnValue(dataList[currentRow]);
			this->insertToEndList(data);
			currentRow++;
		}
	}

	T* findNodeByID(int searchID) {
		node<T>* current = head;

		while (current != NULL) {
			if (current->data.getUID() == searchID) return &(current->data);
			current = current->nextAddress;
		}
		return new T();
	}

	node<T>* findNodeListByID(int searchID) {
		node<T>* current = head;

		while (current != NULL) {
			if (current->data.getUID() == searchID) return current;
			current = current->nextAddress;
		}
		return new node<T>();
	}

	bool clearList() {
		node<T>* current = head;

		for (int i = this->size; i > 0; i++) {
			deleteFromFrontList();
		}
		return true;
	}
};