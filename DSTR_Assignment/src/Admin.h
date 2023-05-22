#pragma once

#include <iostream>
#include "User.h"
using namespace std;

class Admin : public User {
protected:

public:
	// Constructor
	Admin() : User() {

	}

	Admin(int UID, string username, string email, string password, string phoneNo)
		: User(UID, username, email, password, phoneNo) {

	}
	
	//Functions
	//Generate Report
	void generateReport() {
		

	}
};