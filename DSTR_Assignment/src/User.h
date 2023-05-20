#pragma once

#include <iostream>
using namespace std;

class User {
protected:
	int UID;
	string username;
	string email;
	string password;
	string phoneNumber;

public:
	User() {
		UID = NULL;
		username = email = password = "";
	}

	User(int UID, string username, string email, string password, string phoneNo) {
		this->UID = UID;
		this->username = username;
		this->email = email;
		this->password = password;
		this->phoneNumber = phoneNo;
	}
	


	// Getter Function
	int getUID() {
		return UID;
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

	// Setter function
	void setUID(int tmpUID) {
		UID = tmpUID;
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
};