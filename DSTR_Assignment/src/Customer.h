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
	Date lastLogDate;
public:
	Customer() : User() {
		postcode = NULL;
		address = state = country = "";
		lastLogDate = Date();
	}

	Customer(int UID, string username, string email, string password, string phoneNo, int postCode, string address, string state, string country, Date tmpDate) 
		: User(UID, username, email, password, phoneNo){
		this->postcode = postCode;
		this->address = address;
		this->state = state;
		this->country = country;
		this->lastLogDate = tmpDate;
	}
};