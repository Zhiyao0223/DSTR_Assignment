#pragma once

#include <iostream>
#include "User.h"
#include "Date.h"
using namespace std;


class Customer : public User{
protected:
	int postcode;
	string address;
	string state;
	string country;
	Date* lastLogDate;
public:
	// Constructor
	Customer() : User() {
		postcode = NULL;
		address = state = country = "";
		lastLogDate = new Date();
	}

	Customer(int UID, string username, string email, string password, string phoneNo, int postCode, string address, string state, string country, Date* tmpDate) 
		: User(UID, username, email, password, phoneNo){
		this->postcode = postCode;
		this->address = address;
		this->state = state;
		this->country = country;
		this->lastLogDate = tmpDate;
	}


	// Update latest login date
	void updateLogDate() {
		lastLogDate->setToday();
	}


	// Check login date if inactive
	bool checkInactiveStatus() {
		return lastLogDate->isExpired();
	}


	// Getter Function
	int getPostcode() {
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
		postcode = stoi(data);
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