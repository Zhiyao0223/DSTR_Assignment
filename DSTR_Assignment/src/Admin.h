#pragma once

#include <iostream>
#include "User.h"
#include "Util.h"
#include "Validation.h"
#include <limits>
#include "LinkedList.h"
#include "University.h"
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
        tmpPass = Util::getPassword();

        // Check if username and password match
        return list->lookUpProfile(tmpUsername, tmpPass);
    }

    //Generate Report
    void generateReport() {}


    void addUniversity(LinkedList<University>* list) {
        string tmpName, tmpLocationCode, tmpLocation;
        float data[17];

        cout << "Enter University Name: ";
        getline(cin, tmpName);

        while (Validation::isEmpty(tmpName) || !Validation::isString(tmpName)) {
            cout << "Error: University name should only contain alphabetic characters and cannot be empty. Please re-enter: ";
            getline(cin, tmpName);
        }

        cout << "Enter Location Code: ";
        getline(cin, tmpLocationCode);

        while (Validation::isEmpty(tmpLocationCode) || !Validation::isString(tmpLocationCode)) {
            cout << "Error: Location code should only contain alphabetic characters and cannot be empty. "<< endl << "Please re - enter:";
            getline(cin, tmpLocationCode);
        }

        cout << "Enter Location: ";
        getline(cin, tmpLocation);

        string dataLabels[17] = {
            "AR Rank", "AR Score", "ER Score", "ER Rank", "FSR Score", "FSR Rank",
            "Cpf Score", "Cpf Rank", "Ifr Score", "Ifr Rank", "ISr Score", "ISr Rank",
            "Irn Score", "Irn Rank", "Ger Score", "Ger Rank", "Score Scaled"
        };

        for (int i = 0; i < 17; i++) {
            cout << "Enter " << dataLabels[i] << ": ";
            string input;
            getline(cin, input);

            while (!Validation::isFloat(input)) {
                cout << "Error: Invalid input for " << dataLabels[i] << ". Expected a float. Please re-enter: ";
                getline(cin, input);
            }

            data[i] = stof(input);
        }

        // Create a new University instance
        University* uni = new University(tmpName, tmpLocationCode, tmpLocation, data);

        // Add University to List
        list->insertToEndList(uni);

        cout << "University added successfully!" << endl;
    }



    //Edit University
    void editUniversity() {
        
    
    }
    
};
