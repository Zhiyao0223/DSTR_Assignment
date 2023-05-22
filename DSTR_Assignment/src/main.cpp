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
void adminPlatform(Admin* currentAdmin);
void setupUser(LinkedList<Customer>* custList, LinkedList<Admin>* adminList);


int main() {
	//test();
	
	//Admin* admin;
	//Customer* cust;
	//LinkedList<Admin>* adminList = new LinkedList<Admin>();
	//LinkedList<Customer>* custList = new LinkedList<Customer>();

	//setupUser(custList, adminList);


	//Validation validator;
	//Util util;
	//string option;

	//// Print welcome message, draft only for now
	//while (true) {
	//	cout << "Welcome to XXX System" << endl;
	//	cout << "---------------------------------------" << endl;

	//	cout << "Please select your role:" << endl;
	//	cout << "1. Customer" << endl;
	//	cout << "2. Admin" << endl;
	//	cout << "3. Exit" << endl;
	//	cout << "Option: ";

	//	getline(cin, option);

	//	try {
	//		switch (stoi(option)) {
	//		case 1:
	//			custPlatform();
	//			break;
	//		case 2:
	//			admin = admin->login(adminList);
	//			if (admin == nullptr) {
	//				cout << "Invalid username or password" << endl;
	//				Util::sleepClean(2);
	//			} else {
	//				adminPlatform(admin);
	//			}
	//			break;
	//		case 3:
	//			cout << "Thanks for using the system" << endl;
	//			return  0;
	//		default:
	//			cout << "Please enter only the option available." << endl << endl;
	//		}
	//	}
	//	catch (exception) {
	//		cout << "Please enter only the option available." << endl << endl;
	//	}
	//}
}


void adminPlatform(Admin* currentAdmin) {
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
		cout << "6. Logout" << endl;
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
				currentAdmin->logOut();
				return;
			default:
				cout << "Please enter only the option available." << endl << endl;
			}
		}
		catch (exception) {
			cout << "Please enter only the option available." << endl << endl;
			Util::sleepClean(2);
		}
	}
	
}


void custPlatform() {
	Customer cust;
}


// Prebuilt user database
void setupUser(LinkedList<Customer>* custList, LinkedList<Admin>* adminList) {
	int custNewId = custList->getNewUID();
	int adminNewId = adminList->getNewUID();

	custList->insertToFrontList(new Customer(custNewId, "ali", "ali1@gmail.com", "123", "01112345678", "57000", "Taman Sri Muda1, Shah Alam", "Selangor", "Malaysia"));
	custList->insertToFrontList(new Customer(custNewId+1, "abu", "ali2@gmail.com", "123", "01112345678", "57000", "Taman Sri Muda2, Shah Alam", "Selangor", "Malaysia"));
	custList->insertToFrontList(new Customer(custNewId+2, "ah Meng", "ali3@gmail.com", "123", "01112345678", "57000", "Taman Sri Muda3, Shah Alam", "Selangor", "Malaysia"));
	custList->insertToFrontList(new Customer(custNewId+3, "aliu", "ali4@gmail.com", "123", "01112345678", "57000", "Taman Sri Muda4, Shah Alam", "Selangor", "Malaysia"));
	custList->insertToFrontList(new Customer(custNewId+4, "aliaa", "ali5@gmail.com", "123", "01112345678", "57000", "Taman Sri Muda5, Shah Alam", "Selangor", "Malaysia"));

	adminList->insertToFrontList(new Admin(adminNewId, "admin1", "admin1@gmail.com", "123", "01112345678"));
	adminList->insertToFrontList(new Admin(adminNewId + 1, "admin1", "admin1@gmail.com", "123", "01112345678"));
}

// Purely use for testing, delete later
void test() {
	//Test Binary Search
	FileIO file;
	LinkedList<University>* uniList = file.readFile();
	
	
}