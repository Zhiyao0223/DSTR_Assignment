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
		postcode = nullptr;
		address = state = country = "";
		lastLogDate = new Date();
	}

	Customer(int UID, string username, string email, string password, string phoneNo, string postCode, string address, string state, string country) 
		: User(UID, username, email, password, phoneNo){
		Date date;
		this->postcode = postCode;
		this->address = address;
		this->state = state;
		this->country = country;
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
	bool login(LinkedList<Customer>* list, string tmpUsername, string tmpPass) {
		/*string** dataArray = list->extractUsernameAndPassword();*/

		//for (int i = 0; i < list->size; i++) {
		//	if (dataArray[i][0] == tmpUsername && dataArray[i][1] == tmpPass) {
		//		updateLogDate();
		//		return true;
		//	}
		//}
		return false;
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