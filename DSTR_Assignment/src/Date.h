#pragma once

#include <iostream>
#include <ctime>
#include <chrono>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

class Date {
	const int maxInactiveMonth = 3;
	
public:
	int year;
	int month;
	int day;

	// Constructor
	Date() {
		year = month = day = -1;
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


	// Return date in string
	string toString() {
		return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
	}


	// Get today date
	tm getToday() {
		time_t currentTime = time(nullptr);
		tm localTime;
		localtime_s(&localTime, &currentTime);
		return localTime;
	}


	// Update login date to today
	void setToday() {
		tm localTime = getToday();

		// Extract the date components
		year = localTime.tm_year + 1900;   // Years since 1900
		month = localTime.tm_mon + 1;      // Months since January (0-11)
		day = localTime.tm_mday;           // Day of the month (1-31)
	}


	// Check if account is expired
	// Reference: https://stackoverflow.com/a/13788001
	bool isExpired() {
		tm today = getToday();

		string todays = to_string(today.tm_mday) + "/" + to_string(today.tm_mon + 1) + "/" + to_string(today.tm_year + 1900);
		char const* todayDate = todays.c_str();
		char const* userDate = toString().c_str();

		// Compare years
		// Start from 6th index with a length of 4
		int diff = strncmp(todayDate + 6, userDate + 6, 4);
		if (diff != 0)
			return true;

		// Compare months
		diff = strncmp(todayDate + 3, userDate + 3, 2);

		delete todayDate;
		delete userDate;

		return (diff > maxInactiveMonth);
	};
};