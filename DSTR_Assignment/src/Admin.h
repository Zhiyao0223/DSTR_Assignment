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

	
	// Login
	Admin* login(LinkedList<Admin>* list) {
		string tmpUsername, tmpPass;

		cout << "Username: ";
		getline(cin, tmpUsername);
		cout << "Password: ";
		getline(cin, tmpPass);

		// Check if username and password match
		return list->lookUpProfile(tmpUsername, tmpPass);
	}


	//Generate Report
	void generateReport() {}
};