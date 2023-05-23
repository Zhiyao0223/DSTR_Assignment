#pragma once

#include <iostream>
#include "User.h"
#include "Date.h"
#include "LinkedList.h"
using namespace std;


// Customer class
class Customer : public User{
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
		: User(UID, username, email, password, phoneNo){
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

		cout << "Username: ";
		getline(cin, tmpUsername);
		cout << "Password: ";
		getline(cin, tmpPass);

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
		cout << "[5] Logout" << endl;
		cout << "Option: ";
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