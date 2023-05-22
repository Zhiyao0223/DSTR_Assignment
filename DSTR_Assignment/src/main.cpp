#include <iostream>
#include "Customer.h"
#include "Admin.h"
#include "FileIO.h"
#include "University.h"
#include "LinkedList.h"
#include "Validation.h"
#include "Util.h"

using namespace std;

void test();
void custPlatform();
void adminPlatform();


int main() {
	//test();

	Validation validator;
	Util util;
	string option;

	// Print welcome message, draft only for now
	while (true) {
		cout << "Welcome to XXX System" << endl;
		cout << "---------------------------------------" << endl;

		cout << "Please select your role:" << endl;
		cout << "1. Customer" << endl;
		cout << "2. Admin" << endl;
		cout << "3. Exit" << endl;
		cout << "Option: ";

		getline(cin, option);

		try {
			switch (stoi(option)) {
			case 1:
				custPlatform();
				break;
			case 2:
				adminPlatform();
				break;
			case 3:
				cout << "Thanks for using the system" << endl;
				return  0;
			default:
				cout << "Please enter only the option available." << endl << endl;
			}
		}
		catch (exception) {
			cout << "Please enter only the option available." << endl << endl;
		}
	}
}


void adminPlatform() {
	Admin admin;

	//Admin Menu
	while (true) {
		cout << "Welcome to Admin Platform" << endl;
		cout << "---------------------------------------" << endl;

		cout << "Please select your action:" << endl;
		cout << "1. Add University" << endl;
		cout << "2. Edit University" << endl;
		cout << "3. Delete University" << endl;
		cout << "4. Display University" << endl;
		cout << "5. Generate Report" << endl;
		cout << "6. Exit" << endl;
		cout << "Option: ";

		string option;
		getline(cin, option);

		try {
			switch (stoi(option)) {
			case 1:
				//admin.addUniversity();
				break;
			case 2:
				//admin.editUniversity();
				break;
			case 3:
				//admin.deleteUniversity();
				break;
			case 4:
				//admin.displayUniversity();
				break;
			case 5:
				//admin.generateReport();
				break;
			case 6:
				cout << "Thanks for using the system" << endl;
				return;
			default:
				cout << "Please enter only the option available." << endl << endl;
			}
		}
		catch (exception) {
			cout << "Please enter only the option available." << endl << endl;
		}
	}
	
}


void custPlatform() {
	Customer cust;
}


// Purely use for testing, delete later
void test() {
	FileIO fileIO;
	LinkedList<University>* test = fileIO.readFile();
	test->displayAll();
}