#pragma once

#include <iostream>
#include "User.h"
#include "Date.h"
#include "FileIO.h"
#include "Feedback.h"
#include "Favorite.h"
#include "Util.h"
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
	string address;
	string state;
	string country;
	Date* lastLogDate;
	AccountStatus status;
public:
	// Constructor
	Customer() : User() {
		postcode = address = state = country = "";
		lastLogDate = new Date();
	}

	Customer(int UID, string username, string email, string password, string phoneNo, string postCode, string address, string state, string country)
		: User(UID, username, email, password, phoneNo) {
		Date date;
		this->postcode = postCode;
		this->address = address;
		this->state = state;
		this->country = country;
		lastLogDate = new Date();
		updateLogDate();
	}

	template <typename T>
	T getColumn(int index) {
		/*
		*	Column Index:
		*	0 - UID
		*	1 - Username
		*	2 - Email
		*	3 - PostCode
		*	4 - Address
		*	5 - State
		*	6 - Country
		*/
		switch (index) {
		case 0:
			return getUID();
		case 1:
			return getUsername();
		case 2:
			return getEmail();
		case 3:
			return postcode;
		case 4:
			return address;
		case 5:
			return state;
		case 6:
			return country;
		}
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
		Util::cleanScreen();

		cout << "Welcome to Customer Platform" << endl;
		cout << "---------------------------------------" << endl;

		cout << "Please select your action:" << endl;
		cout << "[1] View University" << endl;
		cout << "[2] Search University" << endl;
		cout << "[3] Login" << endl;
		cout << "[4] Register" << endl;
		cout << "[5] Exit" << endl;
		cout << "Option: ";
	}

	void displayLoginMenu() {
		Util::cleanScreen();

		cout << "Welcome to Customer Platform" << endl;
		cout << "---------------------------------------" << endl;

		cout << "Please select your action:" << endl;
		cout << "[1] View University" << endl;
		cout << "[2] Search University" << endl;
		cout << "[3] Favorites" << endl;
		cout << "[4] MoHE Feedback" << endl;
		cout << "[5] Profile" << endl;
		cout << "[6] Logout" << endl;
		cout << "Option: ";
	}

	Customer* registration(LinkedList<Customer>* custList) {
		string tmpUsername, tmpEmail, tmpPass, confirmPass, tmpPhoneNo, tmpPostcode, tmpAddress, tmpState, tmpCountry;

		while (true) {
			Util::cleanScreen();

			cout << "Registration" << endl;
			cout << "---------------------------------------" << endl;
			cout << "Enter -1 if you want to cancel registration" << endl << endl;

			cout << "Username: ";
			getline(cin, tmpUsername);

			if (tmpUsername == "-1") return NULL;
			else if (!Validation::isUsername(tmpUsername)) {
				cout << "Username could only accept alphabet, number and underscore." << endl;
				Util::sleep(1);
				continue;
			}
			

			cout << "Password: ";
			tmpPass = Util::getPassword();

			cout << "Confirm Password: ";
			confirmPass = Util::getPassword();

			if (tmpPass != confirmPass) {
				cout << "Different password detected." << endl;
				Util::sleep(1);
				continue;
			}
			else if (tmpUsername == "-1") return NULL;

			cout << "Email: ";
			getline(cin, tmpEmail);

			if (!Validation::isEmail(tmpEmail)) {
				cout << "Invalid email format." << endl;
				Util::sleep(1);
				continue;
			}
			else if (tmpUsername == "-1") return NULL;

			cout << "Phone Number: ";
			getline(cin, tmpPhoneNo);

			if (!Validation::isPhoneNo(tmpPhoneNo)) {
				cout << "Invalid phone number format." << endl;
				Util::sleep(1);
				continue;
			}
			else if (tmpUsername == "-1") return NULL;

			cout << "Postcode: ";
			getline(cin, tmpPostcode);

			if (Validation::isEmpty(tmpPostcode)) {
				cout << "Postcode field cannot empty." << endl;
				Util::sleep(1);
				continue;
			}
			else if (tmpUsername == "-1") return NULL;

			cout << "Address: ";
			getline(cin, tmpAddress);

			if (Validation::isEmpty(tmpAddress)) {
				cout << "Address field cannot empty" << endl;
				Util::sleep(1);
				continue;
			}
			else if (tmpUsername == "-1") return NULL;

			cout << "State: ";
			getline(cin, tmpState);

			if (Validation::isEmpty(tmpState)) {
				cout << "State field cannot empty" << endl;
				Util::sleep(1);
				continue;
			}
			else if (tmpUsername == "-1") return NULL;

			cout << "Country: ";
			getline(cin, tmpCountry);

			if (Validation::isEmpty(tmpCountry)) {
				cout << "Country field cannot empty" << endl;
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

	// Profile Menu
	void profileMenu() {
		string tmp;

		while (true) {
			displayProfileMenu();

			getline(cin, tmp);
			try {
				switch (stoi(tmp)) {
				case 1:
					editProfile();
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
		Util::cleanScreen();

		cout << "Profile" << endl;
		cout << "---------------------------------------" << endl;
		toString();

		cout << "Please select your action:" << endl;
		cout << "[1] Edit Profile" << endl;
		cout << "[2] Back" << endl;
		cout << "Option: ";
	}

	// Edit Profile
	bool editProfile() {
		//Util::cleanScreen();

		string index, newData;
		while (true) {
			cout << "Edit Profile" << endl;
			cout << "---------------------------------------" << endl;
			toString();

			cout << "Please select your action:" << endl;
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
				stoi(index);

			} catch (exception) {
				cout << "Invalid option." << endl;
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
				setEmail(newData);
				cout << "Email updated." << endl;
				break;
			case 2:
				setPhoneNo(newData);
				cout << "Phone Number updated." << endl;
				break;
			case 3:
				setPostcode(newData);
				cout << "Postcode updated." << endl;
				break;
			case 4:
				setAddress(newData);
				cout << "Address updated." << endl;
				break;
			case 5:
				setState(newData);
				cout << "State updated." << endl;
				break;
			case 6:
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
	void toString() {
		cout << "Username: " << username << endl;
		cout << "Email: " << email << endl;
		cout << "Phone Number: " << getPhoneNo() << endl;
		cout << "Postcode: " << postcode << endl;
		cout << "Address: " << address << endl;
		cout << "State: " << state << endl;
		cout << "Country: " << country << endl;
	}

	/*
		Display University
		@para favList: Favorite List
	*/
	void viewUniversity(LinkedList<Favorite>* favList) {
		FileIO fileIO;
		LinkedList<University>* uniList = fileIO.readFile();

		while (true) {
			node<University>* selectedUni = uniList->displayAll();

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
		Util::cleanScreen();

		cout << "Favorite" << endl;
		cout << "---------------------------------------" << endl;

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
	void displayFeedback(LinkedList<Feedback>* feedbackList) {
		LinkedList<Feedback>* currentUserFeedbackList = new LinkedList<Feedback>();
		node<Feedback>* current = feedbackList->head;
		int ticketCounter = 1;

		Util::cleanScreen();
		cout << "Feedback" << endl;
		cout << "---------------------------------------" << endl << endl;

		while (current != NULL) {
			if (current->data.getUID() == this->getUID()) {
				if (ticketCounter == 1) {
					cout << "Ticket ID" << "\t" << "Latest Date" << "\t" << "Status" << endl;
				}

				cout << "   [" << ticketCounter << "] " << "\t\t" 
					<< current->data.getDate() << "\t" 
					<<  current->data.getStatus() << endl;

				ticketCounter++;
			}
			current = current->nextAddress;
		}
		cout << endl;

		if (ticketCounter == 1) {
			cout << "No ticket at the moment." << endl;

			cout << "Please select your action:" << endl;
			cout << "[1] Create Ticket" << endl;
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

		string selection;
		getline(cin, selection);

		if (selection == "1") {
			Util::cleanScreen();
			cout << "Create Ticket" << endl;
			cout << "---------------------------------------" << endl << endl;

			string title, description;
			cout << "Title: ";
			getline(cin, title);
			cout << "Description: ";
			getline(cin, description);

			feedbackList->insertToEndList(new Feedback(feedbackList->getNewUID(), this->getUID(), title, description));

			cout << endl << "Ticket created." << endl;
			Util::sleep(1);
		}
		else if (selection == "2" && ticketCounter != 1) {
			cout << endl << "Please enter the index number you wish to view: ";
			cin >> selection;

			try {
				int indexInt = stoi(selection);
				if (indexInt > 0 && indexInt < ticketCounter) {
					current = feedbackList->head;
					int counter = 0;

					while (current != NULL) {
						if (current->data.getUID() == this->getUID()) {
							if (counter == indexInt - 1) {
								current->data.displayDetail();
								break;
							}
							counter++;
						}
						current = current->nextAddress;
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
		else if ((selection == "2" && ticketCounter == 1) || (selection == "3" && ticketCounter != 1)) {
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

	// Getter Function
	string getPostcode() {
		return postcode;
	}

	string getAddress() {
		return address;
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

	void setAddress(string data) {
		address = data;
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
<<<<<<< HEAD
};

=======

	void setAccountStatus(AccountStatus data) {
		status = data;
	}
};
>>>>>>> a83d5256e068cd3782fef301ba3f1e000abf0aba
