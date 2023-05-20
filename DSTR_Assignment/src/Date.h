#pragma once

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class Date {
public:
	int year;
	int month;
	int day;

	// Constructor
	Date() {
		year = month = day = NULL;
	}

	Date(string tmpDate) {
		istringstream iss(tmpDate);
		string tmp;

		getline(iss, tmp, '/');
		day = stoi(tmp);

		getline(iss, tmp, '/');
		month = stoi(tmp);

		getline(iss, tmp);
		year = stoi(tmp);
	}

	Date(int tmpDay, int tmpMonth, int tmpYear) {
		day = tmpDay;
		month = tmpMonth;
		year = tmpYear;
	}
};