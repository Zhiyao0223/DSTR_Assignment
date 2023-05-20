#include <iostream>
#include "Customer.h"
#include "Admin.h"

using namespace std;

int main() {
	// Store data
	Customer cust;
	Admin admin;

	int option = 0;

	// Print welcome message, draft only for now
	cout << "Welcome" << endl;
	cout << "1. Customer" << endl;
	cout << "2. Admin" << endl;

	cin >> option;


	while (option != 6) {
		cout << "1. ..";

		
		switch (option) {
			case 1:
				break;
			case 2:
				break;
			default:
				cout << "Please enter only the option available." << endl;
		}
	}
	cout << "Thanks" << endl;

	return  0;
}