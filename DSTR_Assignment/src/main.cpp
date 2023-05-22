#include <iostream>
#include "Customer.h"
#include "Admin.h"
#include "FileIO.h"
#include "University.h"
#include "LinkedList.h"

using namespace std;

void test();



int main() {
	//test();

	//Store data
	Customer cust;
	Admin admin;

	int option = 0;

	// Print welcome message, draft only for now
	cout << "Welcome" << endl;
	cout << "1. Customer" << endl;
	cout << "2. Admin" << endl;

	cin >> option;

	// Main Menu
	while (option != 6) {
		cout << "1. A" << endl;
		cout << "2. B" << endl;
		cout << "3. C" << endl;
		cout << "4. D" << endl;
		cout << "5. F" << endl;
		cout << "6. Exit" << endl;

		
		switch (option) {
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			default:
				cout << "Please enter only the option available." << endl;
		}
	}
	cout << "Thanks for using the system" << endl;

	return  0;
}


void adminPlatform() {

}


void custPlatform() {

}


// Purely use for testing, delete later
void test() {
	FileIO fileIO;
	LinkedList<University>* test = fileIO.readFile();
	test->displayAll();
}