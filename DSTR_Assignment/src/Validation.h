#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <regex>
using namespace std;

class Validation {
public:
	bool isNumber(string test) {
        try {
            int tmp = stoi(test);
            return true;
        }
        catch (exception) {
            return false;
        }
	}

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

    bool isString(string test) {
        return !isNumber(test);
    }

    bool isEmail(string test) {
        regex format("^[a-zA-Z0-9_+&*-]+(?:\\.[a-zA-Z0-9_+&*-]+)*@(?:[a-zA-Z0-9-]+\\.)+[a-zA-Z]{2,7}$");
        return regex_match(test, format);
    }

    bool isPhoneNo(string test) {
        regex format("^[0-9]{10,11}$");
        return regex_match(test, format);
    }
    
    bool isName(string test) {
        regex format("^[a-zA-Z ]{3,50}$");
        return regex_match(test, format);
    }

    bool isEmpty(string test) {
        return test.empty();
    }
};