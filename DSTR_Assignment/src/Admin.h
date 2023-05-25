#pragma once

#include <iostream>
#include "User.h"
#include "LinkedList.h"
using namespace std;

// Admin class
class Admin : public User {
protected:

public:
	// Constructor
	Admin() : User() {}

	Admin(int UID, string username, string email, string password, string phoneNo)
		: User(UID, username, email, password, phoneNo) {
	}

	// Return specified column value
	template <typename T>
	T getColumn(int index) {
		/*
		*	Column Index:
		*	0 - UID
		*	1 - Username
		*	2 - Email
		*/
		switch (index) {
		case 0:
			return getUID();
		case 1:
			return getUsername();
		case 2:
			return getEmail();
		}
	}


	// Login
	Admin* login(LinkedList<Admin>* list) {
		string tmpUsername, tmpPass;

		cout << "Username: ";
		getline(cin, tmpUsername);
		cout << "Password: ";
		tmpPass = Util::getPassword();

		// Check if username and password match
		return list->lookUpProfile(tmpUsername, tmpPass);
	}

	//Generate Report
	void generateReport() {}
};