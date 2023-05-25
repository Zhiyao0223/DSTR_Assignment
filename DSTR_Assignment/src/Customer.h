#pragma once

#include <iostream>
#include "User.h"
#include "Date.h"
#include "FileIO.h"
#include "Favorite.h"
#include "Util.h"
#include "LinkedList.h"
#include "Validation.h"
using namespace std;

// Customer class
class Customer : public User {
protected:
	string postcode;
	string address;
	string state;
	string country;
	Date* lastLogDate;
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

			if (!Validation::isUsername(tmpUsername)) {
				cout << "Username could only accept alphabet, number and underscore." << endl;
				Util::sleep(1);
				continue;
			}
			else if (tmpUsername == "-1") return NULL;

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
	void editProfile() {
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

		string index, newData;
		getline(cin, index);
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

	// View University
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
};