#pragma once

#include <iostream>
#include "User.h"
#include "Date.h"
#include "FileIO.h"
#include "Feedback.h"
#include "Favorite.h"
#include "Util.h"
#include "Search.h"
#include "LinkedList.h"
#include "Validation.h"
using namespace std;

enum class AccountStatus {
	ACTIVE,
	BLOCKED,
	FREEZE,
	INACTIVE
};

// Customer class
class Customer : public User {
protected:
	string postcode;
	string city;
	string state;
	string country;
	Date* lastLogDate;
	AccountStatus status;
public:
	// Constructor
	Customer() : User() {
		postcode = city = state = country = "";
		lastLogDate = new Date();
	}

	Customer(int UID, string username, string email, string password, string phoneNo, string postCode, string city, string state, string country)
		: User(UID, username, email, password, phoneNo) {
		Date date;
		this->postcode = postCode;
		this->city = city;
		this->state = state;
		this->country = country;
		lastLogDate = new Date();
		updateLogDate();
	}

	// Update latest login date
	void updateLogDate() {
		lastLogDate->setToday();
	}

	// Check login date if inactive
	bool checkInactiveStatus() {
		return lastLogDate->isExpired();
	}

	// Login function
	Customer* login(LinkedList<Customer>* list) {
		Util::printHeader("Login");

		string tmpUsername, tmpPass;

		cout << "* Enter 0 at \"Username\" to register" << endl << endl;
		cout << "Username: ";
		getline(cin, tmpUsername);

		// Cancel login
		if (tmpUsername == "0") return registration(list);

		cout << "Password: ";
		tmpPass = Util::getPassword();

		// Check if username and password match
		return list->lookUpProfile(tmpUsername, tmpPass);
	}

	void displayNotLoginMenu() {
		Util::printHeader("Customer Platform");

		cout << "Welcome !" << endl << endl;
		cout << "Please select your action:" << endl;
		cout << "[1] View University" << endl;
		cout << "[2] Search University" << endl;
		cout << "[3] Sort University" << endl;
		cout << "[4] Login" << endl;
		cout << "[5] Register" << endl;
		cout << "[6] Exit" << endl;
		cout << "Option: ";
	}

	void displayLoginMenu() {
		Util::printHeader("Customer Platform");

		cout << "Welcome , " << this->username << endl << endl;
		cout << "Please select your action:" << endl;
		cout << "[1] View University" << endl;
		cout << "[2] Search University" << endl;
		cout << "[3] Sort University" << endl;
		cout << "[4] Favorites" << endl;
		cout << "[5] MoHE Feedback" << endl;
		cout << "[6] Profile" << endl;
		cout << "[7] Logout" << endl;
		cout << "Option: ";
	}

	Customer* registration(LinkedList<Customer>* custList) {
		string tmpUsername, tmpEmail, tmpPass, confirmPass, tmpPhoneNo, tmpPostcode, tmpAddress, tmpState, tmpCountry;

		while (true) {
			Util::printHeader("Registration");

			cout << "Enter -1 if you want to cancel registration" << endl << endl;

			cout << "Username" << "\t\t" << ": ";
			getline(cin, tmpUsername);

			if (tmpUsername == "-1") return NULL;
			else if (!Validation::isUsername(tmpUsername)) {
				cout << "Username could only accept alphabet and underscore." << endl;
				Util::sleep(1);
				continue;
			}

			cout << "Password" << "\t\t" << ": ";
			tmpPass = Util::getPassword();

			cout << "Confirm Password" << "\t" << ": ";
			confirmPass = Util::getPassword();

			if (tmpPass != confirmPass) {
				cout << "Different password detected." << endl;
				Util::sleep(1);
				continue;
			}
			else if (tmpUsername == "-1") return NULL;

			cout << "Email" << "\t\t\t" << ": ";
			getline(cin, tmpEmail);

			if (!Validation::isEmail(tmpEmail)) {
				cout << "Invalid email format." << endl;
				Util::sleep(1);
				continue;
			}
			else if (checkRegisteredEmail(custList, tmpEmail)) {
				cout << "Email is being registered. Please proceed with login." << endl;
				Util::sleep(1);
				return NULL;
			}
			else if (tmpUsername == "-1") return NULL;

			cout << "Phone Number" << "\t\t" << ": ";
			getline(cin, tmpPhoneNo);

			if (!Validation::isPhoneNo(tmpPhoneNo)) {
				cout << "Invalid phone number format." << endl;
				Util::sleep(1);
				continue;
			}
			else if (tmpUsername == "-1") return NULL;

			cout << "City" << "\t\t\t" << ": ";
			getline(cin, tmpAddress);

			if (Validation::isEmpty(tmpAddress)) {
				cout << "City field cannot empty" << endl;
				Util::sleep(1);
				continue;
			} else if (!Validation::isString(tmpAddress)) {
				cout << "City field cannot contain number" << endl;
				Util::sleep(1);
				continue;
			}
			else if (tmpUsername == "-1") return NULL;

			cout << "Postcode" << "\t\t" << ": ";
			getline(cin, tmpPostcode);

			if (Validation::isEmpty(tmpPostcode)) {
				cout << "Postcode field cannot empty." << endl;
				Util::sleep(1);
				continue;
			}
			else if (!Validation::isNumber(tmpPostcode)) {
				cout << "Postcode field cannot contain alphabet." << endl;
				Util::sleep(1);
				continue;
			} 
			else if (!Validation::isNumberInRange(stoi(tmpState), 0, 99999)) {
				cout << "Invalid state field format" << endl;
				Util::sleep(1);
				continue;
			}
			else if (tmpUsername == "-1") return NULL;

			cout << "State" << "\t\t\t" << ": ";
			getline(cin, tmpState);

			if (Validation::isEmpty(tmpState)) {
				cout << "State field cannot empty" << endl;
				Util::sleep(1);
				continue;
			} else if (!Validation::isString(tmpState)) {
				cout << "State field cannot contain number" << endl;
				Util::sleep(1);
				continue;
			}
			else if (tmpUsername == "-1") return NULL;

			cout << "Country" << "\t\t\t" << ": ";
			getline(cin, tmpCountry);

			if (Validation::isEmpty(tmpCountry)) {
				cout << "Country field cannot empty" << endl;
				Util::sleep(1);
				continue;
			} else if (!Validation::isString(tmpCountry)) {
				cout << "Country field cannot contain number" << endl;
				Util::sleep(1);
				continue;
			}
			else if (tmpUsername == "-1") return NULL;

			break;
		}

		Customer* newCust = new Customer(custList->getNewUID(), tmpUsername, tmpEmail, tmpPass, tmpPhoneNo, tmpPostcode, tmpAddress, tmpState, tmpCountry);
		custList->insertToEndList(newCust);

		return newCust;
	}

	bool checkRegisteredEmail(LinkedList<Customer>* custList, string email) {
		node<Customer>* temp = custList->head;

		while (temp != NULL) {
			if (temp->data.getEmail() == email) {
				//delete temp;
				return true;
			}
			temp = temp->nextAddress;
		}
		//delete temp;
		return false;
	}

	// Profile Menu
	void profileMenu(LinkedList<Customer>* custList) {
		string tmp;

		while (true) {
			displayProfileMenu();

			getline(cin, tmp);
			try {
				switch (stoi(tmp)) {
				case 1:
					editProfile(custList);
				case 2:
					break;
				default:
					cout << "Invalid option." << endl;
					cout << "Returning to previous page" << endl;
					Util::sleep(1);
					break;
				}
			}
			catch (exception) {
				cout << "Invalid option." << endl;
				cout << "Returning to previous page" << endl;
				Util::sleep(1);
			}
		}
	}

	// Display profile menu
	void displayProfileMenu() {
		Util::printHeader("Profile Menu");
		display();

		cout << endl << "Please select your action:" << endl;
		cout << "[1] Edit Profile" << endl;
		cout << "[2] Back" << endl;
		cout << "Option: ";
	}

	// Edit Profile
	bool editProfile(LinkedList<Customer>* custList) {
		string index, newData;
		while (true) {
			Util::printHeader("Edit Profile");
			display();

			cout << endl << "Please select your action:" << endl;
			cout << "[1] Edit Email" << endl;
			cout << "[2] Edit Phone Number" << endl;
			cout << "[3] Edit Postcode" << endl;
			cout << "[4] Edit Address" << endl;
			cout << "[5] Edit State" << endl;
			cout << "[6] Edit Country" << endl;
			cout << "[7] Back" << endl;
			cout << "Option: ";

			getline(cin, index);
			try {
				int tmp = stoi(index);
			}
			catch (exception) {
				cout << "Invalid option." << endl;
				Util::sleep(1);
				return false;
			}

			if (stoi(index) < 0 || stoi(index) > 7) {
				cout << "Invalid option." << endl;
			}
			else if (stoi(index) == 7) return false;
			break;
		}

		cout << endl << "Please enter your new data: ";
		getline(cin, newData);

		try {
			switch (stoi(index)) {
			case 1:
				if (!Validation::isEmail(newData)) {
					cout << "Invalid email format." << endl;
					Util::sleep(1);
					return false;
				}
				else if (checkRegisteredEmail(custList, newData)) {
					cout << "Email already registered." << endl;
					Util::sleep(1);
					return false;
				}
				setEmail(newData);
				cout << "Email updated." << endl;
				break;
			case 2:
				if (!Validation::isNumber(newData)) {
					cout << "Invalid phone number format." << endl;
					Util::sleep(1);
					return false;
				}
				setPhoneNo(newData);
				cout << "Phone Number updated." << endl;
				break;
			case 3:
				if (!Validation::isNumber(newData)) {
					cout << "Invalid postcode format." << endl;
					Util::sleep(1);
					return false;
				}
				setPostcode(newData);
				cout << "Postcode updated." << endl;
				break;
			case 4:
				if (!Validation::isString(newData)) {
					cout << "Invalid address format." << endl;
					Util::sleep(1);
					return false;
				}
				setCity(newData);
				cout << "City updated." << endl;
				break;
			case 5:
				if (!Validation::isString(newData)) {
					cout << "Invalid state format." << endl;
					Util::sleep(1);
					return false;
				}
				setState(newData);
				cout << "State updated." << endl;
				break;
			case 6:
				if (!Validation::isString(newData)) {
					cout << "Invalid country format." << endl;
					Util::sleep(1);
					return false;
				}
				setCountry(newData);
				cout << "Country updated." << endl;
				break;
			case 7:
				break;
			default:
				cout << "Invalid option." << endl;
			}
		}
		catch (exception) {
			cout << "Invalid option." << endl;
		}
		Util::sleep(1);
		return true;
	}

	// Display individual profile
	void display() {
		cout << "Username" << "\t\t" << ": " << username << endl;
		cout << "Email" << "\t\t\t" << ": " << email << endl;
		cout << "Phone Number" << "\t\t" << ": " << getPhoneNo() << endl;
		cout << "Postcode" << "\t\t" << ": " << postcode << endl;
		cout << "City" << "\t\t\t" << ": " << city << endl;
		cout << "State" << "\t\t\t" << ": " << state << endl;
		cout << "Country" << "\t\t\t" << ": " << country << endl;
	}

	// Return string of data for csv export
	string toDataString() {
		return to_string(getUID()) + "," + username + "," + email + "," + password + ","
			+ getPhoneNo() + "," + getPostcode() + "," + city + "," + state + "," + country + ","
			+ getLastLogDate() + "," + getAccountStatus();
	}

	/*
		Display University
		@para favList: Favorite List
	*/
	void viewUniversity(LinkedList<Favorite>* favList, LinkedList<University>* uniList, int selectedUniIndex = 0) {
		Util::printHeader("University List");

		while (true) {
			node <University>* selectedUni = new node<University>();
			if (selectedUniIndex != 0) {
				selectedUni = uniList->findNodeListByID(selectedUniIndex);
			}
			else {
				selectedUni = uniList->displayAllUniversity();
			}

			if (selectedUni != NULL) {
				if (Validation::isEmpty(getUsername())) {
					cout << "Please login before proceed." << endl;
					Util::sleep(1);
					return;
				}
				else {
					Util::cleanScreen();
					selectedUni->data.display();

					cout << "Please select your action:" << endl;
					cout << "[1] Add to Wishlist" << endl;
					cout << "[2] Back" << endl;
					cout << "Option: ";

					string index;
					getline(cin, index);

					if (index == "1") {
						int favUID = favList->getNewUID();
						favList->insertToEndList(new Favorite(favUID, this->getUID(), selectedUni->data.getRank()));
						cout << endl << selectedUni->data.getInstitution() << " added to wishlist." << endl;
						Util::sleep(1);
					}
					else if (index == "2") {
						break;
					}
					else {
						cout << "Invalid option." << endl;
						Util::sleep(1);
					}
				}
			}
			else break;
		}
	}

	/*
		Display Favorite
		@param favList - Favorite List
	*/
	void displayFav(LinkedList<Favorite>* favList) {
		// Display all favorite
		Util::printHeader("Favorite");

		LinkedList<University>* favUniList = new LinkedList<University>();
		node<Favorite>* tmp = favList->head;
		int favSize = 1;
		Favorite tmpClass;

		while (tmp != NULL) {
			tmpClass = tmp->data;

			if (tmpClass.getUID() == this->getUID()) {
				favUniList->insertToEndList(tmpClass.getUniversity(tmpClass.getInstitutionRank()));

				cout << "[" << favSize << "] " << endl;
				University* uni = tmpClass.getUniversity(tmpClass.getInstitutionRank());
				uni->display();
				favSize++;
			}
			tmp = tmp->nextAddress;
		}

		// No favorite
		if (favSize == 1) {
			cout << "No favorite at the moment." << endl;
			Util::sleep(1);
		}
		else {
			cout << "Please select your action:" << endl;
			cout << "[1] Remove from Wishlist" << endl;
			cout << "[2] Back" << endl;
			cout << "Option: ";

			string selection;
			getline(cin, selection);

			if (selection == "1") {
				cout << endl << "Please enter the index number you wish to remove: ";

				string removeUniIndex;
				getline(cin, removeUniIndex);

				try {
					int indexInt = stoi(removeUniIndex);
					if (indexInt > 0 && indexInt < favSize) {
						tmp = favList->head;
						node<University>* tmpUni = favUniList->head;
						int counter = 0;

						for (int i = 0; i < indexInt - 1; i++) {
							tmpUni = tmpUni->nextAddress;
						}

						int uniRank = tmpUni->data.getRank();
						while (tmp != NULL) {
							tmpClass = tmp->data;

							if (tmpClass.getInstitutionRank() == uniRank) {
								Favorite tmp;

								if (counter == 0) tmp = favList->deleteFromFrontList(); // Delete from front
								else if (counter == favList->size - 1) tmp = favList->deleteFromEndList(); // Delete from end
								else favList->deleteFromSpecificLocation(counter); // Delete from specific location

								if (Validation::isEmpty(to_string(tmp.getID()))) {
									cout << "Error: Unable to remove from wishlist." << endl;
									Util::sleep(1);
									return;
								}

								cout << endl << tmpClass.getUniversity(tmpClass.getInstitutionRank())->getInstitution() << " removed from wishlist." << endl;
								Util::sleep(1);
								break;
							}
							counter++;
							tmp = tmp->nextAddress;
						}
					}
					else {
						cout << "Invalid option." << endl;
						Util::sleep(1);
					}
				}
				catch (exception) {
					cout << "Invalid option." << endl;
					Util::sleep(1);
				}
			}
			else if (selection == "2") {
				return;
			}
			else {
				cout << "Invalid option." << endl;
				Util::sleep(1);
			}
		}
	}

	// View Feedback
	void displayFeedback(LinkedList<Feedback>* feedbackList, bool isAdmin = false) {
		// Initialize variables
		node<Feedback>* current = feedbackList->tail;
		int ticketCounter = 1;

		Util::printHeader("Feedback");

		// Display ticket in brief info
		while (current != NULL) {
			if (current->data.getUID() == this->getUID() || isAdmin) {
				// Ignore reply feedback
				if (current->data.getIsReply()) {
					current = current->prevAddress;
					continue;
				}

				if (ticketCounter == 1) {
					cout << "Ticket ID" << "\t" << "Latest Date" << "\t" << "Status" << endl;
				}

				cout << "   [" << ticketCounter << "] " << "\t\t"
					<< current->data.getDate() << "\t"
					<< current->data.getStatus() << endl;

				ticketCounter++;
			}
			current = current->prevAddress;
		}
		cout << endl;

		// Prompt if no ticket found
		if (ticketCounter == 1) {
			if (isAdmin) {
				cout << "No ticket at the moment." << endl;
				Util::sleepClean(2);
				return;
			}
			cout << "No ticket at the moment." << endl;

			cout << "Please select your action:" << endl;
			cout << "[1] Create Ticket" << endl;
			cout << "[2] Back" << endl;
			cout << "Option: ";
		}
		else {
			if (isAdmin) {
				cout << "Please select your action:" << endl;
				cout << "[1] Check Ticket Details" << endl;
				cout << "[2] Back" << endl;
				cout << "Option: ";
			}
			else {
				cout << "Please select your action:" << endl;
				cout << "[1] Create Ticket" << endl;
				cout << "[2] Check Ticket Details" << endl;
				cout << "[3] Back" << endl;
				cout << "Option: ";
			}
		}

		string selection;
		getline(cin, selection);

		if (selection == "1" && !isAdmin) {
			Util::printHeader("Create Ticket");

			string title, description;
			cout << "Title: ";
			getline(cin, title);
			cout << "Description: ";
			getline(cin, description);

			feedbackList->insertToEndList(new Feedback(feedbackList->getNewUID(), this->getUID(), title, description));

			cout << endl << "Ticket created." << endl;
			Util::sleep(1);
		}
		else if ((selection == "2" && ticketCounter != 1 && !isAdmin) || (selection == "1" && isAdmin && ticketCounter != 1)) {
			cout << endl << "Please enter the index number you wish to view: ";
			cin >> selection;

			try {
				int indexInt = stoi(selection);
				if (indexInt > 0 && indexInt < ticketCounter) {
					current = feedbackList->tail;
					int counter = 0;

					while (current != NULL) {
						if (current->data.getUID() == this->getUID()) {
							// Ignore reply feedback
							if (current->data.getIsReply()) {
								current = current->prevAddress;
								continue;
							}

							if (counter == indexInt - 1) {
								current->data.display(feedbackList);
								break;
							}
							counter++;
						}
						current = current->prevAddress;
					}
				}
				else {
					cout << "Invalid option." << endl;
					Util::sleep(1);
				}
			}
			catch (exception) {
				cout << "Invalid option." << endl;
				Util::sleep(1);
			}
		}
		else if ((selection == "2" && ticketCounter == 1) || (selection == "3" && ticketCounter != 1 && !isAdmin) || (selection == "2" && isAdmin)) {
			return;
		}
		else {
			cout << "Invalid option." << endl;
			Util::sleepClean(1);
		}
	}

	/*
		Convert account status enum to string
	*/
	string accountStatusToString(AccountStatus tmpStatus) {
		switch (tmpStatus) {
		case AccountStatus::ACTIVE:
			return "ACTIVE";
		case AccountStatus::INACTIVE:
			return "INACTIVE";
		case AccountStatus::BLOCKED:
			return "BLOCKED";
		case AccountStatus::FREEZE:
			return "FREEZE";
		default:
			return "UNKNOWN";
		}
	}

	string* displayUniByArray(string** arr, int row) {
		Util::printHeader("Search University");

		int counter = 0;
		const int MAX_ITEM_PER_PAGE = 5;
		string option, rank;

		for (int i = 0; i < row; i++) {
			for (int j = 4; j < 21; j++) {
				if (arr[i][j] == "-1") {
					arr[i][j] = "-";
				}
				else if (arr[i][j] == "501" || arr[i][j] == "601") {
					arr[i][j] += "+";
				}
			}

			cout << endl << "[" << counter + 1 << "]" << endl;
			cout << "Rank " << "\t\t\t\t\t" << ": " << arr[i][0] << endl;
			cout << "Intitution Name" << "\t\t\t\t" << ": " << arr[i][1] << endl;
			cout << "Location " << "\t\t\t\t" << ": " << arr[i][3] << " (" << arr[i][2] << ")" << endl;
			cout << "Academic Reputation (rank)" << "\t\t" << ": " << arr[i][4] << " (" << arr[i][5] << ")" << endl;
			cout << "Employer Reputation (rank)" << "\t\t" << ": " << arr[i][6] << " (" << arr[i][7] << ")" << endl;
			cout << "Faculty / Student Ratio (rank)" << "\t\t" << ": " << arr[i][8] << " (" << arr[i][9] << ")" << endl;
			cout << "Citations Per Faculty (rank)" << "\t\t" << ": " << arr[i][10] << " (" << arr[i][11] << ")" << endl;
			cout << "Internation Faculty Ratio (rank)" << "\t" << ": " << arr[i][12] << " (" << arr[i][13] << ")" << endl;
			cout << "Internation Student Ratio (rank)" << "\t" << ": " << arr[i][14] << " (" << arr[i][15] << ")" << endl;
			cout << "International Research Network (rank)" << "\t" << ": " << arr[i][16] << " (" << arr[i][17] << ")" << endl;
			cout << "Employment Outcome (rank)" << "\t\t" << ": " << arr[i][18] << " (" << arr[i][19] << ")" << endl;
			cout << "Overall Score" << "\t\t\t\t" << ": " << arr[i][20] << endl;

			//cout << "Rank: " <<  << endl;
			//cout << "Institution Name: " << arr[i][1] << endl;
			//cout << "Location: " << arr[i][2] << endl;
			//cout << "Academic Reputation (rank): " << arr[i][3] << endl;
			//cout << "Employer Reputation (rank): " << arr[i][4] << endl;
			//cout << "Faculty / Student Ratio (rank): " << arr[i][5] << endl;
			//cout << "Citations Per Faculty (rank): " << arr[i][6] << endl;
			//cout << "Internation Faculty Ratio (rank): " << arr[i][7] << endl;
			//cout << "International Student Ratio (rank): " << arr[i][8] << endl;
			//cout << "Overall Score: " << arr[i][9] << endl << endl;
		}

		cout << endl << "[1] Add University to Favourite" << endl;
		cout << "[2] Return" << endl;
		cout << "Option: ";

		getline(cin, option);

		// Set to selected record
		if (option == "1") {
			if (counter > 1) {
				cout << endl << "Please enter the index number of university you wish to add: ";
				getline(cin, option);
				cout << endl;

				if (option < "1" || option > to_string(counter)) {
					cerr << "Invalid option. Returning..." << endl;
					Util::sleep(1);
					return NULL;
				}
			}

			return arr[stoi(option) - 1];
		}
		// Return to previous page
		else if (option == "2") {
			return NULL;
		}
		// Also return to previous page if invalid numeric input
		else {
			cerr << "Invalid option. Returning..." << endl;
			Util::sleep(2);
			return NULL;
		}
		counter = 0;
	}

	/*
		Search university. IN PROGRESS
	*/
	void searchUniversity(LinkedList<University>* uniList, LinkedList<Favorite>* favList) {
		Util::printHeader("Search University");

		string uniName = "";
		cout << "* Exact Match Only *" << endl << endl;
		cout << "Enter university name: ";
		getline(cin, uniName);

		cout << endl << "Searching..." << endl
			<< "It may take a while..." << endl << endl;

		string** arr = uniList->convertTo2DArray();
		quicksort(arr, 0, uniList->size - 1, 1, true);

		int counter = 0, numRows = 0;

		arr = binarySearch(arr, uniList->size, uniName, 1, &numRows);
		//LinkedList<University>* tmp = linearSearch(uniList, uniName, 1);
		//arr = tmp->convertTo2DArray();

		if (arr == NULL) {
			cout << "No result found." << endl;
			Util::sleepClean(1);
			return;
		}

		string* selectedUni = displayUniByArray(arr, numRows);

		if (selectedUni != NULL) {
			if (Validation::isEmpty(this->getUsername())) {
				cout << "Please login to proceed." << endl;
				Util::sleepClean(1);
				return;
			}

			int favUID = favList->getNewUID();
			favList->insertToEndList(new Favorite(favUID, this->getUID(), stoi(selectedUni[0])));
			cout << endl << selectedUni[1] << " added to wishlist." << endl;
			Util::sleep(1);
		}
	}

	void sortUniversity(LinkedList<University>* uniList, LinkedList<Favorite>* favList, bool isLogin = false) {
		Util::cleanScreen();
		Util::printBorderLine();
		cout << "\t\t\t\t" << "Sort University" << endl;
		Util::printBorderLine();
		cout << endl;

		if (isLogin) {
			cout << "Please select the sorting method: " << endl
				<< "[1] Sort by name" << endl
				<< "[2] Sort by location code" << endl
				<< "[3] Sort by location" << endl
				<< "[4] Sort by academic reputation (score)" << endl
				<< "[5] Sort by academic reputation (rank)" << endl
				<< "[6] Sort by employer reputation (score)" << endl
				<< "[7] Sort by employer reputation (rank)" << endl
				<< "[8] Sort by faculty / student ratio (score)" << endl
				<< "[9] Sort by faculty / student ratio (rank)" << endl
				<< "[10] Sort by citations per faculty (score)" << endl
				<< "[11] Sort by citations per faculty (rank)" << endl
				<< "[12] Sort by internation faculty ratio (score)" << endl
				<< "[13] Sort by internation faculty ratio (rank)" << endl
				<< "[14] Sort by international student ratio (score)" << endl
				<< "[15] Sort by international student ratio (rank)" << endl
				<< "[16] Sort by international research network (score)" << endl
				<< "[17] Sort by international research network (rank)" << endl
				<< "[18] Sort by employment outcome (score)" << endl
				<< "[19] Sort by employment outcome (rank)" << endl
				<< "[20] Sort by Score Scaled" << endl
				<< "[21] Back" << endl
				<< "Option: ";
		}
		else {
			cout << "Please select the sorting method: " << endl;
			cout << "[1] Sort by name" << endl;
			cout << "[2] Back" << endl;
			cout << "Option: ";
		}

		int colIndex = 0;
		string indexSelection, ascSelection;
		getline(cin, indexSelection);

		try {
			colIndex = stoi(indexSelection);

			if (isLogin) {
				if (colIndex < 1 || colIndex > 21) {
					cout << "Invalid option." << endl;
					Util::sleepClean(1);
					return;
				}
				else if (colIndex == 21) return;
			}
			else {
				if (colIndex < 1 || colIndex > 2) {
					cout << "Invalid option." << endl;
					Util::sleepClean(1);
					return;
				}
				else if (colIndex == 2) return;
			}
		}
		catch (exception) {
			cout << "Invalid option." << endl;
			Util::sleepClean(1);
			return;
		}

		cout << endl << "Ascending or Descending?" << endl
			<< "[1] Ascending" << endl
			<< "[2] Descending" << endl
			<< "Option: ";
		getline(cin, ascSelection);

		if (ascSelection != "1" && ascSelection != "2") {
			cout << "Invalid option." << endl;
			Util::sleepClean(1);
			return;
		}
		bool isAsc = (ascSelection == "1") ? true : false;

		cout << endl << "Sorting..." << endl
			<< "It may take a while." << endl;

		LinkedList<University>* tmpList = new LinkedList<University>();
		string** arr = uniList->convertTo2DArray();
		quicksort(arr, 0, uniList->size - 1, colIndex, isAsc);
		tmpList->convertToLinkedList(arr, uniList->size);

		//Util::cleanScreen();
		node<University>* newNode = tmpList->displayAllUniversity();
		if (newNode != NULL) {
			if (Validation::isEmpty(getUsername())) {
				cout << "Please login before proceed." << endl;
				Util::sleep(1);
				return;
			}

			favList->insertToEndList(new Favorite(favList->getNewUID(), this->getUID(), newNode->data.getRank()));
			cout << endl << newNode->data.getInstitution() << " added to wishlist." << endl;
			Util::sleep(1);
		}
	}

	// Update Inactive Account to Status 'INACTIVE'
	void updateUserStatus(LinkedList<Customer>* custList) {
		// Check by using checkInactiveStatus function
		// If true, update the status to 'INACTIVE'
		// Else, do nothing

		node <Customer>* tmp = custList->head;

		while (tmp != nullptr) {
			if (tmp->data.checkInactiveStatus()) {
				tmp->data.setAccountStatus(AccountStatus::INACTIVE);
			}
			tmp = tmp->nextAddress;
		}
	}

	// Getter Function
	string getPostcode() {
		return postcode;
	}

	string getCity() {
		return city;
	}

	string getState() {
		return state;
	}

	string getCountry() {
		return country;
	}
	string getLastLogDate() {
		return lastLogDate->toString();
	}

	string getAccountStatus() {
		return accountStatusToString(this->status);
	}

	// Setter Function
	void setPostcode(string data) {
		postcode = data;
	}

	void setCity(string data) {
		city = data;
	}

	void setState(string data) {
		state = data;
	}

	void setCountry(string data) {
		country = data;
	}
	void setLastLogDate(Date* data) {
		lastLogDate = data;
	}

	void setAccountStatus(AccountStatus data) {
		status = data;
	}
};