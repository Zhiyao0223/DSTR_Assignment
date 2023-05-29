#pragma once

#include <ctime>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
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

	// Constructor with date format "DD/MM/YYYY"
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

	// Get today date in tm format
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
	bool isExpired() {
		// Get today date
		tm today = getToday();

		// Check if different year more than 1
		if ((today.tm_year + 1900) - year != 0) return true;

		// Check if different month more than maximum inactive month
		if ((today.tm_mon + 1) - month > maxInactiveMonth) return true;

		return false;
	};
};