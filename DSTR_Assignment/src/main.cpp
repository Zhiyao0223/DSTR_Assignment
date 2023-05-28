#include <iostream>
#include <chrono>
#include "Customer.h"
#include "Admin.h"
#include "Favorite.h"
#include "Feedback.h"
#include "FileIO.h"
#include "University.h"
#include "Sort.h"
#include "LinkedList.h"
#include "Validation.h"
#include "Util.h"
#include "Sort.h"
using namespace std;

void test();
void custPlatform(LinkedList<Customer>* custList, LinkedList<Favorite>* favList, LinkedList<Feedback>* feedbackList, LinkedList<University>* uniList);
void adminPlatform(Admin* currentAdmin, LinkedList<Favorite>* favList, LinkedList<University>* uniList, LinkedList<Customer>* custList, LinkedList<Feedback>* feedbackList);
void setupUser(LinkedList<Customer>* custList, LinkedList<Admin>* adminList, LinkedList<Favorite>* favList, LinkedList<Feedback>* feedbackList, LinkedList<University>** uniList);


int main() {
	//test();
	
	// Initialize doubly linked list, classes and variables
	Admin* admin = new Admin();
	Customer* cust = new Customer();
	LinkedList<Admin>* adminList = new LinkedList<Admin>();
	LinkedList<Customer>* custList = new LinkedList<Customer>();
	LinkedList<Favorite>* favList = new LinkedList<Favorite>();
	LinkedList<Feedback>* feedbackList = new LinkedList<Feedback>();
	LinkedList<University>* uniList = new LinkedList<University>();

	string option;
	string programName = "University Rating System";
	string welcomeMsg = "This system is a university rating platform.\n"
						"Get ready to explore the world of command-line magic\n";
	string thanksBanner = R"(
			       ^ ^                         ^ ^   
			      (O,O)                       (O,O)
			      (   )       Thank You       (   )
		            ---"-"-------------------------"-"---

		If you have any feedback or suggestions, please let us know.
				       Have a great day!
						)";

	// Setup dummy data
	setupUser(custList, adminList, favList, feedbackList, &uniList);

	// Update inactive user status
	cust->updateUserStatus(custList);

	// Get user role
	while (true) {
		// Print welcome message
		Util::printHeader(programName);
		cout << welcomeMsg << endl;

		// Select role
		cout << endl << "Please select your role:" << endl;
		cout << "1. Customer" << endl;
		cout << "2. Admin" << endl;
		cout << "3. Exit" << endl;
		cout << "Option: ";

		// Get option
		string option;
		getline(cin, option);

		// Redirect user to its platform. If invalid option, print error message
		try {
			switch (stoi(option)) {
			case 1:
				custPlatform(custList, favList, feedbackList, uniList);
				break;
			case 2:
				admin = admin->login(adminList);
				if (admin == nullptr) {
					cout << "Invalid username or password" << endl;
					Util::sleep(1);
				}
				else {
					adminPlatform(admin, favList, uniList, custList, feedbackList);
				}
				break;
			case 3:
				admin->generateReport(uniList, custList, adminList, feedbackList, favList);
				cout << endl << thanksBanner << endl;
				return  0;
			default:
				cout << "Invalid Option." << endl;
				Util::sleep(1);
			}
		}
		catch (exception) {
			cout << "Invalid Option." << endl;
			Util::sleep(1);
		}
		Util::cleanScreen();
	}

	// Deallocate memory
	delete uniList;

}

// Admin Platform
void adminPlatform(Admin* currentAdmin, LinkedList<Favorite>* favList, LinkedList<University>* uniList, LinkedList<Customer>* custList, LinkedList<Feedback>* feedbackList){
	//Admin Menu
	while (true) {
		// Print header
		Util::printHeader("Admin Platform");
		
		// Display admin menu
		cout << "Welcome, " << currentAdmin->getUsername() << "!" << endl << endl
			<< "Please select your action:" << endl
			<< "[1] Add University" << endl
			<< "[2] Display Registered Users' Detail" << endl
			<< "[3] Modify User Detail" << endl
			<< "[3] Delete inactive account" << endl
			<< "[4] Feedback" << endl
			<< "[5] Generate Report" << endl
			<< "[6] Compare Algorithm Runtime" << endl
			<< "[7] Logout" << endl
			<< "Option: ";

		// Redirect admin to different features. If invalid option, print error message
		string option;
		getline(cin, option);

		try {
			switch (stoi(option)) {
			case 1:
				currentAdmin->addUniversity(uniList);
				break;
			case 2:
				currentAdmin->displayAndModifyUser(custList);
				break;
			case 3:
				currentAdmin->changeInactiveToFreeze(custList);
				break;
			case 4:
				currentAdmin->displayFeedbackByDate(feedbackList);
				break;
			case 5:
				currentAdmin->summarizeTop10Preferred(favList);
				break;
			case 6:
				currentAdmin->compareTimeComplexity(uniList);
			case 7:
				currentAdmin->logOut();
				return;
			default:
				cout << "Invalid Option." << endl << endl;
				Util::sleep(1);
			}
		}
		catch (exception) {
			cout << "Invalid Option." << endl << endl;
			Util::sleep(1);
		}
		Util::cleanScreen();
	}

}

/*
	Customer Platform

	@param custList: Customer linked list
	@param favList: Favorite linked list
	@param feedbackList: Feedback linked list
	@param uniList: University linked list
*/

void custPlatform(LinkedList<Customer>* custList, LinkedList<Favorite>* favList, LinkedList<Feedback>* feedbackList, LinkedList<University>* uniList) {
	// Store login customer information
	Customer* currentCust = new Customer();

	// Record login status
	bool isLogin = false;

	Util::cleanScreen();

	// Display customer Menu
	while (true) {
		// Check if currentCust has value to determine login status
		isLogin = !Validation::isEmpty(currentCust->getUsername());

		isLogin ? currentCust->displayLoginMenu() : currentCust->displayNotLoginMenu();

		// Redirect user to different features. If invalid option, print error message
		string option;
		getline(cin, option);
		cout << endl;

		try {
			if (isLogin) {
				// Registered user menu
				switch (stoi(option)) {
				case 1:
					currentCust->viewUniversity(favList, uniList);
					break;
				case 2:
					currentCust->searchUniversity(uniList, favList);
					break;
				case 3:
					currentCust->sortUniversity(uniList, favList, true);
					break;
				case 4:
					currentCust->displayFav(favList);
					break;
				case 5:
					currentCust->displayFeedback(feedbackList);
					break;
				case 6:
					currentCust->displayProfileMenu();
					break;
				case 7:
					currentCust->logOut();
					return;
				default:
					cout << "Invalid Option." << endl << endl;
				}
			}
			else {
				// Guest user menu
				Customer* tmp = new Customer();
				switch (stoi(option)) {
				case 1:
					currentCust->viewUniversity(favList, uniList);
					break;
				case 2:
					currentCust->searchUniversity(uniList, favList);
					break;
				case 3:
					currentCust->sortUniversity(uniList, favList);
					break;
				case 4:
					tmp = tmp->login(custList);
					if (tmp == nullptr) {
						cout << "Invalid username or password" << endl;
					}
					else {
						cout << endl << tmp->getUsername() << " login successfully" << endl;
						currentCust = tmp;
					}
					break;
				case 5:
					tmp = tmp->registration(custList);
					if (tmp != nullptr) {
						cout << endl << tmp->getUsername() << " register successfully" << endl;
						currentCust = tmp;
					}
					break;
				case 6:
					return;
				default:
					cout << "Invalid Option." << endl << endl;
				}
			}
		}
		catch (exception) {
			cout << "Invalid Option." << endl << endl;
			Util::sleepClean(1);
		}
		Util::cleanScreen();
	}
}


/*
	Setup dummy data for testing purpose
	Cust (ali, 123)
	Admin (admin1, 123)

	@param custList	 : customer list
	@param adminList : admin list
	@param favList : favorite list
	@param feedbackList : feedback list
	@param uniList : university list
*/
void setupUser(LinkedList<Customer>* custList, LinkedList<Admin>* adminList, LinkedList<Favorite>* favList, LinkedList<Feedback>* feedbackList, LinkedList<University>** uniList) {
	// Get new ID for new data
	int custNewId = custList->getNewUID();
	int adminNewId = adminList->getNewUID();
	int favNewId = favList->getNewUID();
	int feedbackNewId = feedbackList->getNewUID();

	// Read university data from file
	FileIO file;
	*uniList = file.readFile();

	// Add dummy data
	custList->insertToEndList(new Customer(custNewId, "ali", "ali1@gmail.com", "123", "01112345678", "57000", "Shah Alam", "Selangor", "Malaysia"));
	custList->insertToEndList(new Customer(custNewId + 1, "abu", "ali2@gmail.com", "123", "01112345678", "57000", "Shah Alam", "Selangor", "Malaysia"));
	custList->insertToEndList(new Customer(custNewId + 2, "ah Meng", "ali3@gmail.com", "123", "01112345678", "57000", "Shah Alam", "Selangor", "Malaysia"));
	custList->insertToEndList(new Customer(custNewId + 3, "aliu", "ali4@gmail.com", "123", "01112345678", "57000", "Shah Alam", "Selangor", "Malaysia"));
	custList->insertToEndList(new Customer(custNewId + 4, "aliaa", "ali5@gmail.com", "123", "01112345678", "57000", "Shah Alam", "Selangor", "Malaysia"));
	custList->tail->data.setLastLogDate(new Date("12/12/2020"));

	adminList->insertToEndList(new Admin(adminNewId, "admin1", "admin1@gmail.com", "123", "01112345678"));
	adminList->insertToEndList(new Admin(adminNewId + 1, "admin2", "admin2@gmail.com", "123", "01112345678"));

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
	favList->insertToEndList(new Favorite(favNewId + 10, 5, 2));
	favList->insertToEndList(new Favorite(favNewId + 11, 5, 21));
	favList->insertToEndList(new Favorite(favNewId + 12, 5, 2));

	feedbackList->insertToEndList(new Feedback(feedbackNewId, 1, "Title", "haha"));
	feedbackList->insertToEndList(new Feedback(feedbackNewId + 1, 1, "Title2", "9"));
	feedbackList->insertToEndList(new Feedback(feedbackNewId + 2, 2, "Title3", "12"));
	feedbackList->insertToEndList(new Feedback(feedbackNewId + 3, 2, "Title4", "12"));
	feedbackList->insertToEndList(new Feedback(feedbackNewId + 4, 2, "Title5", "12"));
	feedbackList->insertToEndList(new Feedback(feedbackNewId + 5, 3, "Title6", "212"));
	feedbackList->insertToEndList(new Feedback(feedbackNewId + 6, 3, "Title7", "2"));
	feedbackList->insertToEndList(new Feedback(feedbackNewId + 7, 4, "Title8", "25"));
	feedbackList->insertToEndList(new Feedback(feedbackNewId + 8, 4, "Title9", "2"));
	feedbackList->insertToEndList(new Feedback(feedbackNewId + 9, 4, "Test", "21"));
	
	// Modify data for testing purpose
	feedbackList->head->data.setReply(feedbackNewId, 4, "Reply", "1111", true);
	feedbackList->head->data.setSpecificDate("12/4/2022");

	node<Feedback>* current = feedbackList->head->nextAddress;
	current->data.setSpecificDate("22/5/2023");
}

// Purely use for testing, delete later
void test() {
	FileIO file;
	LinkedList<University>* uniList = file.readFile();

	int size = uniList->size; // Number of universities
	
	// Create a 2D array to hold the university data
	string** universityData = uniList->convertTo2DArray();
	int index = 2;
	
	auto startTime = std::chrono::high_resolution_clock::now();
	selectionSort(universityData, size, index);
	auto endTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

	auto startTime1 = std::chrono::high_resolution_clock::now();
	quicksort(universityData, 0, size-1, index, true);
	auto endTime1 = std::chrono::high_resolution_clock::now();
	auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(endTime1 - startTime1).count();


	// Display the sorted university data
	for (int i = 0; i < size; i++) {
		cout << universityData[i][index] << ", " << universityData[i][1] << endl;
	}

	cout << duration << endl;
	cout << duration1 << endl;

	//uniList->displayAllUniversity(universityData, size);
}

