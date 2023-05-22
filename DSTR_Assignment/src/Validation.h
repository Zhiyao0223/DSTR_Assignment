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
	bool isNumber(string test) {
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
    bool isDouble(string test) {
        int tmp = 0;
        
        try {
            tmp = ceil(stoi(test));
        }
        catch (exception) {
            return false;
        }
        return (tmp == stoi(test)+1);
    }


    /*
        Check if string contains alphabet only
        @param test - string
        @return True if input is alphabetic
    */
    bool isString(string test) {
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
    bool isEmail(string test) {
        regex format("^[a-zA-Z0-9_+&*-]+(?:\\.[a-zA-Z0-9_+&*-]+)*@(?:[a-zA-Z0-9-]+\\.)+[a-zA-Z]{2,7}$");
        return regex_match(test, format);
    }


    /*
        Check if string is phone number format
        @param test - string
        @return True if input is specific format
    */
    bool isPhoneNo(string test) {
        regex format("^[0-9]{10,11}$");
        return regex_match(test, format);
    }
    

    /*
        Check if string is a standard username
        @param test - string
        @return True if input match username format
    */
    bool isUsername(string test) {
        regex format("^[a-zA-Z ]{3,50}$");
        return regex_match(test, format);
    }


    /*
        Check if string is empty
        @param test - string
        @return True if input has only space character or is NULL
    */
    bool isEmpty(string test) {
        return test.empty();
    }


    /*
        Check if string contain backslash '\'
        @param test - string
        @return True if input has backslash
    */
    bool hasBackSlash(string test) {
        return test.find('\ "');
    }
};