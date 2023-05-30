#include <chrono>
#include <iostream>
#include "Admin.h"
#include "Customer.h"
#include "Favorite.h"
#include "Feedback.h"
#include "FileIO.h"
#include "LinkedList.h"
#include "Sort.h"
#include "University.h"
#include "Util.h"
#include "Validation.h"
using namespace std;

void custPlatform(LinkedList<Customer>* custList, LinkedList<Favorite>* favList, LinkedList<Feedback>* feedbackList, LinkedList<University>* uniList);
void adminPlatform(Admin* currentAdmin, LinkedList<Favorite>* favList, LinkedList<University>* uniList, LinkedList<Customer>* custList, LinkedList<Feedback>* feedbackList);
void setupUser(LinkedList<Customer>* custList, LinkedList<Admin>* adminList, LinkedList<Favorite>* favList, LinkedList<Feedback>* feedbackList, LinkedList<University>** uniList);

int main() {
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
	delete admin;
	delete cust;
	delete custList;
	delete adminList;
	delete favList;
	delete feedbackList;
	delete uniList;
}

/*
	Admin Platform

	@param currentAdmin: Current admin
	@param favList: Favorite linked list
	@param uniList: University linked list
	@param custList: Customer linked list
	@param feedbackList: Feedback linked list
*/
void adminPlatform(Admin* currentAdmin, LinkedList<Favorite>* favList, LinkedList<University>* uniList, LinkedList<Customer>* custList, LinkedList<Feedback>* feedbackList) {
	//Admin Menu
	while (true) {
		// Print header
		Util::printHeader("Admin Platform");

		// Display admin menu
		cout << "Welcome, " << currentAdmin->getUsername() << "!" << endl << endl
			<< "Please select your action:" << endl
			<< "[1] Add University" << endl
			<< "[2] Display Registered Users' Detail" << endl
			<< "[3] Delete Inactive Account" << endl
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
				break;
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
					currentCust->profileMenu(custList);
					break;
				case 7:
					currentCust->logOut();
					return;
				default:
					cout << "Invalid Option." << endl << endl;
					Util::sleep(1);
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
						Util::sleep(1);
					}
					else {
						cout << endl << tmp->getUsername() << " login successfully" << endl;
						currentCust = tmp;
						Util::sleep(1);
					}
					break;
				case 5:
					tmp = tmp->registration(custList);
					if (tmp != nullptr) {
						cout << endl << tmp->getUsername() << " register successfully" << endl;
						currentCust = tmp;
						Util::sleep(1);
					}
					break;
				case 6:
					return;
				default:
					cout << "Invalid Option." << endl << endl;
					Util::sleep(1);
				}
			}
		}
		catch (exception) {
			cout << "Invalid Option." << endl << endl;
			Util::sleep(1);
		}
		Util::cleanScreen();
	}

	// Deallocate Memory
	delete currentCust;
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
	custList->insertToEndList(new Customer(custNewId, "ali", "ali@gmail.com", "123", "01112345678", "57000", "Bukit Jalil", "Selangor", "Malaysia"));
	custList->insertToEndList(new Customer(custNewId + 1, "abu", "abu@hotmail.com", "123", "01122223333", "40150", "Shah Alam", "Selangor", "Malaysia"));
	custList->insertToEndList(new Customer(custNewId + 2, "ah Meng", "ahmeng@gmail.com", "123", "0171236677", "41700", "Puchong", "Selangor", "Malaysia"));
	custList->insertToEndList(new Customer(custNewId + 3, "akao", "akao@hotmail.com", "123", "0125553344", "28000", "Temerloh", "Pahang", "Malaysia"));
	custList->insertToEndList(new Customer(custNewId + 4, "tan", "tan@gmail.com", "123", "0107898565", "30000", "Ipoh", "Perak", "Malaysia"));
	custList->tail->data.setLastLogDate(new Date("12/12/2020"));

	adminList->insertToEndList(new Admin(adminNewId, "admin1", "admin1@gmail.com", "123", "0125555667"));
	adminList->insertToEndList(new Admin(adminNewId + 1, "admin2", "admin2@gmail.com", "123", "0103344667"));

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

	feedbackList->insertToEndList(new Feedback(feedbackNewId, 1, "Trouble in Login", "Hi, I'm having trouble accessing the university recommendation system. Is there a technical issue?"));
	feedbackList->insertToEndList(new Feedback(feedbackNewId + 1, 1, "Lack of Response to User Feedback", "I have previously provided feedback on certain university ratings, but there doesn't seem to be any response or acknowledgment. It would be great to receive some feedback on the suggestions and concerns raised."));
	feedbackList->insertToEndList(new Feedback(feedbackNewId + 2, 2, "System Crash during Navigation", "Whenever I search for a uni, the system just stop responding"));
	feedbackList->insertToEndList(new Feedback(feedbackNewId + 3, 2, "Slow Loading Time", "Very slow eh"));
	feedbackList->insertToEndList(new Feedback(feedbackNewId + 4, 2, "For fun", "nothing here"));
	feedbackList->insertToEndList(new Feedback(feedbackNewId + 5, 3, "Clickbait", "Never gonna give you up~"));
	feedbackList->insertToEndList(new Feedback(feedbackNewId + 6, 3, "Unresponsive user interface", "Nothing happen after I enter option"));
	feedbackList->insertToEndList(new Feedback(feedbackNewId + 7, 4, "Forget Password", "I forget pass bruh"));
	feedbackList->insertToEndList(new Feedback(feedbackNewId + 8, 4, "Unable to Register Account", "It keep say my email is being registered"));
	feedbackList->insertToEndList(new Feedback(feedbackNewId + 9, 4, "For testing", "You can't see me"));

	// Modify data for testing purpose
	feedbackList->head->data.setReply(feedbackNewId, 4, "Trouble in Login", "Hello! Sorry to hear about the issue. Could you please provide more details about the problem you're experiencing?", true);
	feedbackList->head->data.setStatus(FeedbackStatus::WAITING_FOR_CUSTOMER);
	feedbackList->head->data.setSpecificDate("12/4/2022");
	feedbackList->head->nextAddress->data.setSpecificDate("20/4/2023");
	feedbackList->head->nextAddress->nextAddress->data.setSpecificDate("29/4/2023");
	feedbackList->head->nextAddress->nextAddress->nextAddress->data.setSpecificDate("10/5/2023");
	feedbackList->head->nextAddress->nextAddress->nextAddress->nextAddress->data.setSpecificDate("17/5/2023");

	//node<Feedback>* current = feedbackList->head->nextAddress;
	//current->data.setSpecificDate("22/5/2023");
}