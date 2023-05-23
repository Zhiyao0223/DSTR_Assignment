#pragma once

#include <iostream>
#include <conio.h>
#include <chrono>
#include <thread>
#include <string>
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

	// Masking password field
	static string getPassword() {
		string tmpPass;
		char ch;

		// Capture input until Enter is pressed
		while ((ch = _getch()) != '\r') {
			// Handle backspace
			if (ch == '\b') {
				if (tmpPass.length() > 0) {
					cout << "\b \b";
					tmpPass.pop_back();
				}
			}
			else {
				tmpPass.push_back(ch);
				cout << "*";
			}
		}
		cout << endl;

		return tmpPass;
	}

	// Retrieve university data from dataset
	LinkedList<University>* getUniversityList() {
		FileIO file;
		return file.readFile();
	}

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