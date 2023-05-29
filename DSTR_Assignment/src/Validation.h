#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <regex>
using namespace std;

class Validation {
public:
	/*
		Check if string contains only numeric value

		@param test - string
		@return True if input is number
	*/
	static bool isNumber(string test) {
		try {
			int tmp = stoi(test);
			return true;
		}
		catch (exception) {
			return false;
		}
	}

	/*
		Check if string contains only double value

		@param test - string
		@return True if input is double
	*/
	static bool isDouble(string test) {
		int tmp = 0;

		try {
			tmp = ceil(stoi(test));
		}
		catch (exception) {
			return false;
		}
		return (tmp == stoi(test) + 1);
	}

	/*
		Check if string contains only float value

		@param test - string
		@return True if input is float
	*/
	static bool isFloat(string test) {
		try {
			float tmp = stof(test);
			return true;
		}
		catch (exception) {
			return false;
		}
	}

	/*
		Check if string contains alphabet only

		@param test - string
		@return True if input is alphabetic
	*/
	static bool isString(string test) {
		for (char c : test) {
			if (!isalpha(c)) return false;
		}

		return true;
	}

	/*
		Check if string is email address format

		@param test - string
		@return True if input is specific format
	*/
	static bool isEmail(string test) {
		regex format("^[a-zA-Z0-9_+&*-]+(?:\\.[a-zA-Z0-9_+&*-]+)*@(?:[a-zA-Z0-9-]+\\.)+[a-zA-Z]{2,7}$");
		return regex_match(test, format);
	}

	/*
		Check if string is phone number format

		@param test - string
		@return True if input is specific format
	*/
	static bool isPhoneNo(string test) {
		regex format("^[0-9]{10,11}$");
		return regex_match(test, format);
	}

	/*
		Check if string is a standard username

		@param test - string
		@return True if input match username format
	*/
	static bool isUsername(string test) {
		regex format("^[a-zA-Z_]{3,50}$");
		return regex_match(test, format);
	}

	/*
		Check if string is empty

		@param test - string
		@return True if input has only space character or is NULL
	*/
	static bool isEmpty(string test) {
		for (char c : test) {
			if (!isspace(c)) return false;
		}
		return true;
	}

	/*
		Check if a string has zero length

		@param test - string
		@return True if input has zero length
	*/
	static bool isZeroLength(string test) {
		return test.length() == 0;
	}

	/*
		Check if string contain backslash '\'

		@param test - string
		@return True if input has backslash
	*/
	static bool hasBackSlash(string test) {
		return test.find('\ "');
	}

	/*
		Check if a number is within range

		@param input - number to check
		@param min - minimum value
		@param max - maximum value
	*/
	static bool isNumberInRange(int input, int min, int max) {
		return ((input >= min) && (input <= max));
	}
};