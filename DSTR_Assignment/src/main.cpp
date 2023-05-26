#include <iostream>
#include "Customer.h"
#include "Admin.h"
#include "Favorite.h"
#include "Feedback.h"
#include "FileIO.h"
#include "University.h"
#include "LinkedList.h"
#include "Validation.h"
#include "Util.h"
#include "Sort.h"

using namespace std;

void test();
void custPlatform(LinkedList<Customer>* custList, LinkedList<Favorite>* favList);
void adminPlatform(Admin* currentAdmin);
void setupUser(LinkedList<Customer>* custList, LinkedList<Admin>* adminList, LinkedList<Favorite>* favList, LinkedList<Feedback>* feedbackList);

int main() {
	test();

	//Admin* admin = new Admin();
	//Customer* cust = new Customer();
	//LinkedList<Admin>* adminList = new LinkedList<Admin>();
	//LinkedList<Customer>* custList = new LinkedList<Customer>();
	//LinkedList<Favorite>* favList = new LinkedList<Favorite>();
	//LinkedList<Feedback>* feedbackList = new LinkedList<Feedback>();

	//setupUser(custList, adminList, favList, feedbackList);

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
	//	cout << endl;

	//	try {
	//		switch (stoi(option)) {
	//		case 1:
	//			custPlatform(custList, favList);
	//			break;
	//		case 2:
	//			admin = admin->login(adminList);
	//			if (admin == nullptr) {
	//				cout << "Invalid username or password" << endl;
	//			}
	//			else {
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
	//	Util::sleepClean(1);
	//}

	
}

// Admin Platform
void adminPlatform(Admin* currentAdmin) {
	Util::cleanScreen();

	//Admin Menu
	while (true) {
		cout << "Welcome to Admin Platform" << endl;
		cout << "---------------------------------------" << endl;

		cout << "Please select your action:" << endl;
		cout << "[1] Add University" << endl;
		cout << "[2] Edit University" << endl;
		cout << "[3] Delete University" << endl;
		cout << "[4] Display University" << endl;
		cout << "[5] Generate Report" << endl;
		cout << "[6] Profile" << endl;
		cout << "[7] Logout" << endl;
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
				//admin.viewProfile();
				break;
			case 7:
				currentAdmin->logOut();
				return;
			default:
				cout << "Please enter only the option available." << endl << endl;
			}
		}
		catch (exception) {
			cout << "Please enter only the option available." << endl << endl;
		}
	}
	Util::sleepClean(1);
}

// Customer Platform
void custPlatform(LinkedList<Customer>* custList, LinkedList<Favorite>* favList) {
	Customer* currentCust = new Customer();

	bool isLogin = false;

	Util::cleanScreen();

	// Customer Menu
	while (true) {
		isLogin = !Validation::isEmpty(currentCust->getUsername());

		isLogin ? currentCust->displayLoginMenu() : currentCust->displayNotLoginMenu();

		string option;
		getline(cin, option);
		cout << endl;

		try {
			if (isLogin) {
				// Registered user menu
				switch (stoi(option)) {
				case 1:
					currentCust->viewUniversity(favList);
					break;
				case 2:
					//cust.searchUniversity();
					break;
				case 3:
					currentCust->displayFav(favList);
					break;
				case 4:
					//cust.feedback();
					break;
				case 5:
					currentCust->displayProfileMenu();
					break;
				case 6:
					currentCust->logOut();
					return;
				default:
					cout << "Please enter only the option available." << endl << endl;
				}
			}
			else {
				// Guest user menu
				Customer* tmp = new Customer();
				switch (stoi(option)) {
				case 1:
					currentCust->viewUniversity(favList);
					break;
				case 2:
					//currentCust->searchUni();
					break;
				case 3:
					tmp = tmp->login(custList);
					if (tmp == nullptr) {
						cout << "Invalid username or password" << endl;
					}
					else {
						cout << endl << tmp->getUsername() << " login successfully" << endl;
						currentCust = tmp;
					}
					break;
				case 4:
					tmp = tmp->registration(custList);
					if (tmp != nullptr) {
						cout << endl << tmp->getUsername() << " register successfully" << endl;
						currentCust = tmp;
					}
					break;
				case 5:
					return;
				default:
					cout << "Please enter only the option available." << endl << endl;
				}
			}
		}
		catch (exception) {
			cout << "Please enter only the option available." << endl << endl;
			Util::sleepClean(2);
		}
		Util::cleanScreen();
	}
}

/*
	Setup dummy data for testing purpose
	Cust: ali, 123
	Admin: admin1, 123
*/
void setupUser(LinkedList<Customer>* custList, LinkedList<Admin>* adminList, LinkedList<Favorite>* favList, LinkedList<Feedback>* feedbackList) {
	int custNewId = custList->getNewUID();
	int adminNewId = adminList->getNewUID();
	int favNewId = favList->getNewUID();
	int feedbackNewId = feedbackList->getNewUID();

	custList->insertToEndList(new Customer(custNewId, "ali", "ali1@gmail.com", "123", "01112345678", "57000", "Taman Sri Muda1, Shah Alam", "Selangor", "Malaysia"));
	custList->insertToEndList(new Customer(custNewId + 1, "abu", "ali2@gmail.com", "123", "01112345678", "57000", "Taman Sri Muda2, Shah Alam", "Selangor", "Malaysia"));
	custList->insertToEndList(new Customer(custNewId + 2, "ah Meng", "ali3@gmail.com", "123", "01112345678", "57000", "Taman Sri Muda3, Shah Alam", "Selangor", "Malaysia"));
	custList->insertToEndList(new Customer(custNewId + 3, "aliu", "ali4@gmail.com", "123", "01112345678", "57000", "Taman Sri Muda4, Shah Alam", "Selangor", "Malaysia"));
	custList->insertToEndList(new Customer(custNewId + 4, "aliaa", "ali5@gmail.com", "123", "01112345678", "57000", "Taman Sri Muda5, Shah Alam", "Selangor", "Malaysia"));

	adminList->insertToEndList(new Admin(adminNewId, "admin1", "admin1@gmail.com", "123", "01112345678"));
	adminList->insertToEndList(new Admin(adminNewId + 1, "admin1", "admin1@gmail.com", "123", "01112345678"));

	favList->insertToEndList(new Favorite(favNewId, 1, 2));
	favList->insertToEndList(new Favorite(favNewId + 1, 1, 9));
	favList->insertToEndList(new Favorite(favNewId + 2, 2, 23));
	favList->insertToEndList(new Favorite(favNewId + 3, 2, 25));
	favList->insertToEndList(new Favorite(favNewId + 4, 2, 2));
	favList->insertToEndList(new Favorite(favNewId + 5, 3, 212));
	favList->insertToEndList(new Favorite(favNewId + 6, 3, 2));
	favList->insertToEndList(new Favorite(favNewId + 7, 4, 5));
	favList->insertToEndList(new Favorite(favNewId + 8, 4, 2));
	favList->insertToEndList(new Favorite(favNewId + 9, 4, 21));
}

// Purely use for testing, delete later


void test() {
	Customer* cust = new Customer();
	LinkedList<Admin>* adminList = new LinkedList<Admin>();
	LinkedList<Customer>* custList = new LinkedList<Customer>();
	LinkedList<Favorite>* favList = new LinkedList<Favorite>();
	LinkedList<Feedback>* feedbackList = new LinkedList<Feedback>();

	setupUser(custList, adminList, favList, feedbackList);

	FileIO file;
	LinkedList<University>* uniList = file.readFile();

	Admin admin;
	Customer customer;
	// Populate the linked list with data


	

	//Edit User
	//LinkedList<Customer> editUser;  // Create an instance of the LinkedList<Customer> class



	modifyUser(custList);  // Call the modifyUser function and pass the address of the userList object

}

