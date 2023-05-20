#pragma once

#include <iostream>
#include "LinkedList.h"
#include "Customer.h"
using namespace std;

// All extra features throw here
class Util {
protected:

public:
	// Get last UID in linked list and add one to its
	template <class T>
	int getNewUID(LinkedList<T>* dataList) {
		int tmp = 0;
		node<T>* data = dataList->head;

		while (data != NULL) {
			tmp = data.getUID();
			data = data->nextAddress;
		}
		return tmp + 1;
	}

	// Clean screen
	void cleanScreen() {
		system("cls");
	}

	// Delete inactive user
	void deleteInactiveUser(LinkedList<Customer>* user){
		node<Customer>* tmp = user->head;
		string date = "";
		int counter = 0;

		while (tmp != NULL) {
			if (tmp->data.checkInactiveStatus()) {
				Customer cust = user->deleteFromSpecificLocation(counter);
				cout << "Deleted: " << cust.getUsername() << endl;
			}
			counter++;
			tmp = tmp->nextAddress;
		}
	}
};