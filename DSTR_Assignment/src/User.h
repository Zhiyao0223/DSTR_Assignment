#pragma once

#include <iostream>
#include "LinkedList.h"
#include "Util.h"
using namespace std;

class User {
protected:
	int ID;
	string username;
	string email;
	string password;
	string phoneNumber;
	bool loginStatus;

public:
	User() {
		ID = NULL;
		username = email = password = "";
	}

	User(int UID, string username, string email, string password, string phoneNo) {
		this->ID = UID;
		this->username = username;
		this->email = email;
		this->password = password;
		this->phoneNumber = phoneNo;
	}

	// Logout Function
	void logOut() {
		setLoginStatus(false);
		cout << this->getUsername() << " logging out." << endl;
		Util::sleepClean(1);
	}

	// Getter Function
	int getUID() {
		return ID;
	}

	string getUsername() {
		return username;
	}

	string getEmail() {
		return email;
	}

	string getPassword() {
		return password;
	}

	string getPhoneNo() {
		return phoneNumber;
	}

	bool getLoginStatus() {
		return loginStatus;
	}

	// Setter function
	void setUID(int tmpUID) {
		ID = tmpUID;
	}

	void setUsername(string tmpUsername) {
		username = tmpUsername;
	}

	void setEmail(string tmpEmail) {
		email = tmpEmail;
	}

	void setPassword(string tmpPass) {
		password = tmpPass;
	}

	void setPhoneNo(string tmpPhone) {
		phoneNumber = tmpPhone;
	}

	void setLoginStatus(bool status) {
		loginStatus = status;
	}
};