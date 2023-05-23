#pragma once

#include <iostream>
#include <chrono>
#include <thread>
#include "LinkedList.h"
#include "Customer.h"
using namespace std;


// All extra features throw here
class Util {
public:
	// Clean screen
	static void cleanScreen() {
		system("cls");
	}

	// Freeze system
	static void sleep(int second) {
		this_thread::sleep_for(chrono::seconds(second));
	}

	// Freeze and sleep screen
	static void sleepClean(int second) {
		sleep(second);
		cleanScreen();
	}

	// Get last UID in linked list and add one to its, in progress
	//template <class T>
	//int getNewUID(LinkedList<T>* dataList) {
	//	int tmp = 0;
	//	node<T>* data = dataList->head;

	//	while (data != NULL) {
	//		tmp = data.getUID();
	//		data = data->nextAddress;
	//	}
	//	return tmp + 1;
	//}

	// Delete inactive user, in progress
	//void deleteInactiveUser(LinkedList<Customer>* user){
	//	node<Customer>* tmp = user->head;
	//	string date = "";
	//	int counter = 0;

	//	while (tmp != NULL) {
	//		if (tmp->data.checkInactiveStatus()) {
	//			Customer cust = user->deleteFromSpecificLocation(counter);
	//			cout << "Deleted: " << cust.getUsername() << endl;
	//		}
	//		counter++;
	//		tmp = tmp->nextAddress;
	//	}
	//}
};