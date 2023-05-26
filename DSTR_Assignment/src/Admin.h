#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include "User.h"
#include "Util.h"
#include "Validation.h"
#include "Admin.h"
#include "Customer.h"
#include "Favorite.h"
#include "Feedback.h"
#include "LinkedList.h"
#include "University.h"
#include "Sort.h"

using namespace std;

// Admin class
class Admin : public User {
public:
	// Constructor
	Admin() : User() {}

	Admin(int UID, string username, string email, string password, string phoneNo)
		: User(UID, username, email, password, phoneNo) {}

	// Return specified column value
	//template <typename T>
	//T getColumn(int index) {
	//	/*
	//	*	Column Index:
	//	*	0 - UID
	//	*	1 - Username
	//	*	2 - Email
	//	*/
	//	switch (index) {
	//	case 0:
	//		return getUID();
	//	case 1:
	//		return getUsername();
	//	case 2:
	//		return getEmail();
	//	}
	//}

	/*
		Login
		@param list - admin list
		@return Admin* - pointer to the admin object if login successful, nullptr otherwise
	*/
	Admin* login(LinkedList<Admin>* list) {
		// Initialise temporary variables
		string tmpUsername, tmpPass;

		// Get username and password
		cout << endl << "Username: ";
		getline(cin, tmpUsername);
		cout << "Password: ";
		tmpPass = Util::getPassword();

		// Check if username and password match
		return list->lookUpProfile(tmpUsername, tmpPass);
	}

	/*
		Add new university to list
		@param list - university list
	*/
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
			cout << "Error: Location code should only contain alphabetic characters and cannot be empty. " << endl << "Please re - enter:";
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

	/*
		Change INACTIVE account to FREEZE account (AKA Soft Delete Inactive Account)
		@param custList: customer list
	*/ 
	void changeInactiveToFreeze(LinkedList<Customer>* custList) {
		node<Customer>* tmp = custList->head;

		// Display inactive accounts
		cout << "Inactive Accounts:\n";
		while (tmp != nullptr) {
			if (tmp->data.getAccountStatus() == tmp->data.accountStatusToString(AccountStatus::INACTIVE)) {
				cout << "Customer ID: " << tmp->data.getUID() << endl;
			}
			tmp = tmp->nextAddress;
		}

		int choice;
		cout << "\nEnter your choice:\n";
		cout << "1. Select and Delete an INACTIVE account\n";
		cout << "2. Delete all INACTIVE account\n";
		cin >> choice;

		// Change status based on user choice
		tmp = custList->head;
		while (tmp != nullptr) {
			if (tmp->data.getAccountStatus() == tmp->data.accountStatusToString(AccountStatus::INACTIVE)) {
				if (choice == 1) {
					int customerId;
					cout << "Enter customer ID to Delete: ";
					cin >> customerId;

					if (tmp->data.getUID() == customerId) {
						tmp->data.setAccountStatus(AccountStatus::FREEZE);
						cout << "Account status changed to FREEZE for customer ID " << customerId << endl;
						break;  // Exit loop after finding and changing the specific customer's account status
					}
				}
				else if (choice == 2) {
					tmp->data.setAccountStatus(AccountStatus::FREEZE);
				}
			}
			tmp = tmp->nextAddress;
		}
	}

	/*
		Delete all existing freeze function. Havn't apply to any function yet.
		@param custList: customer list
	*/
	void deleteFreezeAccount(LinkedList<Customer>* custList) {
		node<Customer>* tmp = custList->head;
		node<Customer>* prev = nullptr;

		while (tmp != nullptr) {
			if (tmp->data.getAccountStatus() == tmp->data.accountStatusToString(AccountStatus::FREEZE)) {
				// Delete the node
				if (prev == nullptr) {
					// Deleting the head node
					custList->head = tmp->nextAddress;
				}
				else {
					prev->nextAddress = tmp->nextAddress;
				}
				node<Customer>* toDelete = tmp;
				tmp = tmp->nextAddress;
				delete toDelete;
			}
			else {
				prev = tmp;
				tmp = tmp->nextAddress;
			}
		}
	}

	/*
		Display Registered User Detail
		@param cusList: customer list
	*/
	void displayRegisterUser(LinkedList<Customer>* cusList) {
		//If the list is empty
		if (cusList->head == nullptr) {
			cout << "No user registered yet." << endl;
			return;
		}

		//Display the list
		cout << "UID\tUsername\tEmail\t\t\tPhone No." << endl;
		node<Customer>* current = cusList->head;
		while (current != nullptr) {
			Customer tmp = current->data;
			cout << tmp.getUID() << "\t" << tmp.getUsername() << "\t\t" << tmp.getEmail() << "\t" << tmp.getPhoneNo() << endl;
			cout << "-----------------------------------------------------------------" << endl;
			current = current->nextAddress;
		}
	}

	/*
		Delete any user account
		@param currentAdmin: Pointer to current admin node
		@param cusList: customer list
	*/
	void deleteUserAccount(Admin* currentAdmin, LinkedList<Customer>* cusList) {
		// If the list is empty
		if (cusList->head == nullptr) {
			cout << "No user registered yet." << endl;
			return;
		}

		// Display the list
		currentAdmin->displayRegisterUser(cusList);

		// Ask for the UID to delete
		int UID;
		cout << "Enter the UID to delete: ";
		cin >> UID;

		// Check if the UID is valid
		while (UID <= 0 || UID > cusList->size) {
			cout << "Error: Invalid UID. Please re-enter: ";
			cin >> UID;
		}

		// Delete the user
		if (UID == 1) {
			cusList->deleteFromFrontList();
		}
		else if (UID == cusList->size) {
			cusList->deleteFromEndList();
		}
		else {
			cusList->deleteFromSpecificLocation(UID - 1);
		}

		cout << "User deleted successfully!" << endl;
	}

	/*
		Generate CSV reports upon system close. Include university, customer, feedback, and favorite.
		@param uniList: Universities list
		@param custList: Customers list
		@param feedbackList: Feedbacks list
		@param favList: Favorites list
	*/
	void generateReport(LinkedList<University>* uniList, LinkedList<Customer>* custList, LinkedList<Feedback>* feedbackList, LinkedList<Favorite>* favList) {
		// Open the input CSV file
		ofstream outputFile1("university.csv"); 

		outputFile1 << "Rank, Institution, Location Code, Location, AR Score, AR Rank, ER Score, ER Rank, FSR Score, FSR Rank, CPF Score, CPF Rank, IFR Score, IFR Rank, ISR Score, ISR Rank, IRN Score, IRN Rank, GER Score, GER Rank, Score Scaled\n";
		if (outputFile1.is_open()) {
			node<University>* current = uniList->head;
			while (current != nullptr) {
				University tmp = current->data;

				// Write to the CSV file
				outputFile1 << tmp.getRank() << ", "
							<< tmp.getInstitution() << ", "
							<< tmp.getLocationCode() << ", "
							<< tmp.getLocation() << ", "
							<< tmp.getArScore() << ", "
							<< tmp.getArRank() << ", "
							<< tmp.getErScore() << ", "
							<< tmp.getErRank() << ", "
							<< tmp.getFsrScore() << ", "
							<< tmp.getFsrRank() << ", "
							<< tmp.getCpfScore() << ", "
							<< tmp.getCpfRank() << ", "
							<< tmp.getIfrScore() << ", "
							<< tmp.getIfrRank() << ", "
							<< tmp.getIsrScore() << ", "
							<< tmp.getIsrRank() << ", "
							<< tmp.getIrnScore() << ", "
							<< tmp.getIrnRank() << ", "
							<< tmp.getGerScore() << ", "
							<< tmp.getGerRank() << ", "
							<< tmp.getScoreScaled() << "\n";

				current = current->nextAddress;
			}
			// Close the output file
			outputFile1.close(); 
		}
		else {
			cout << "Error opening the output file for attribute: " << endl;
		}
		// Close the input file
		outputFile1.close(); 

		// Open the input CSV file
		ofstream outputFile2("customer.csv");

		outputFile2 << "Username, Email, PhoneNo, Postcode, Address, State, Country\n";
		if (outputFile2.is_open()) {
			node<Customer>* current = custList->head;
			while (current != nullptr) {
				Customer tmp = current->data;

				// Write the data to the file
				outputFile2 << tmp.getUsername() << ", "
							<< tmp.getEmail() << ", "
							<< tmp.getPhoneNo() << ", "
							<< tmp.getPostcode() << ", "
							<< tmp.getAddress() << ", "
							<< tmp.getState() << ", "
							<< tmp.getCountry() << "\n";

				current = current->nextAddress;
			}
			// Close the output file
			outputFile2.close(); 
		}
		else {
			cout << "Error opening the output file for attribute: " << endl;
		}
		// Close the input file
		outputFile2.close(); 

		// Open the input CSV file
		ofstream outputFile3("favorite.csv"); 

		outputFile3 << "ID, UID, insitution\n";
		if (outputFile3.is_open()) {
			node<Favorite>* current = favList->head;
			while (current != nullptr) {
				Favorite tmp = current->data;

				// Write into CSV file
				outputFile3 << tmp.getID() << ", "
							<< tmp.getUID() << ", "
							<< tmp.getInstitutionRank() << "\n";

				current = current->nextAddress;
			}
			// Close the output file
			outputFile3.close(); 
		}
		else {
			cout << "Error opening the output file for attribute: " << endl;
		}
		// Close the input file
		outputFile3.close(); 

		// Open the input CSV file
		ofstream outputFile4("feedback.csv"); 

		outputFile4 << "ID, UID, comment, reply, status, role, date\n";
		if (outputFile4.is_open()) {
			node<Feedback>* current = feedbackList->head;
			while (current != nullptr) {
				Feedback tmp = current->data;

				// Write into CSV file
				outputFile4 << tmp.getID() << ", "
							<< tmp.getUID() << ", "
							<< tmp.getComment() << ", "
							<< tmp.getReply() << ", "
							<< tmp.getStatus() << ", "
							<< tmp.getRole() << ", "
							<< tmp.getDate() << "\n";

				current = current->nextAddress;
			}
			// Close the output file
			outputFile4.close(); 
		}
		else {
			cout << "Error opening the output file for attribute: " << endl;
		}

		// Close the input file
		outputFile4.close(); 
	}

	/*
		Generate summary report for top 10 preferred universities
		@param favoritesList - favorites list
	*/
	void summarizeTop10Preferred(LinkedList<Favorite>* favoritesList) {
		const int MAX_UNIVERSITIES = 10;
		int universityIDs[MAX_UNIVERSITIES] = { 0 };
		int universityFrequencies[MAX_UNIVERSITIES] = { 0 };

		// Count the frequency of each university in the favorites list
		node<Favorite>* current = favoritesList->head;
		while (current != NULL) {
			int universityID = current->data.getInstitutionRank();

			for (int i = 0; i < MAX_UNIVERSITIES; i++) {
				if (universityIDs[i] == 0) {
					// Found an empty slot, add the university ID and set frequency to 1
					universityIDs[i] = universityID;
					universityFrequencies[i] = 1;
					break;
				}
				else if (universityIDs[i] == universityID) {
					// Found a matching university ID, increase the frequency
					universityFrequencies[i]++;
					break;
				}
			}
			current = current->nextAddress;
		}

		// Sort the universities based on their frequency in descending order
		for (int i = 0; i < MAX_UNIVERSITIES; i++) {
			for (int j = i + 1; j < MAX_UNIVERSITIES; j++) {
				if (universityFrequencies[j] > universityFrequencies[i]) {
					// Swap university IDs
					int tempID = universityIDs[i];
					universityIDs[i] = universityIDs[j];
					universityIDs[j] = tempID;

					// Swap frequencies
					int tempFrequency = universityFrequencies[i];
					universityFrequencies[i] = universityFrequencies[j];
					universityFrequencies[j] = tempFrequency;
				}
			}
		}

		// Print the top 10 preferred universities
		cout << "Top 10 Preferred Universities by Parents in Malaysia:" << endl;
		for (int i = 0; i < MAX_UNIVERSITIES; i++) {
			if (universityIDs[i] == 0) {
				break;
			}
			node<Favorite>* currentUniversity = favoritesList->head; // New node pointer for iterating through the linked list
			while (currentUniversity != NULL) {
				int universityID = currentUniversity->data.getInstitutionRank();
				if (universityID == universityIDs[i]) {
					University* university = currentUniversity->data.getUniversity(universityID);
					if (university != NULL) {
						string universityName = university->getInstitution(); // Assuming the University class has a `getInstitution` method
						cout << "University Name: " << universityName << ", Frequency: " << universityFrequencies[i] << endl;
						break; // Exit the loop once the university is found
					}
				}
				currentUniversity = currentUniversity->nextAddress;
			}
		}
	}

	/*
		Change user details
		@param editUser - user list
	*/
	void modifyUser(LinkedList<Customer>* editUser) {
	// Display the list of users
		Util::printBorderLine();
		cout << "Customer List" << endl;
		Util::printBorderLine();

		node<Customer>* currentNode = editUser->head;
		while (currentNode != nullptr) {
			cout << "ID: " << currentNode->data.getUID() << endl;
			cout << "Username: " << currentNode->data.getUsername() << endl;
			cout << "Email: " << currentNode->data.getEmail() << endl;
			cout << "Phone: " << currentNode->data.getPhoneNo() << endl;
			cout << "Password: " << currentNode->data.getPassword() << endl;
			cout << "Postcode: " << currentNode->data.getPostcode() << endl;
			cout << "Address: " << currentNode->data.getAddress() << endl;
			cout << "State: " << currentNode->data.getState() << endl;
			cout << "Country: " << currentNode->data.getCountry() << endl;
			cout << "---------------------------------------" << endl;

			currentNode = currentNode->nextAddress;
		}

		// Ask for user selection
		string index;
		while (true) {
			try {
				cout << "Enter the user index you want to modify: ";
				getline(cin, index);
				stoi(index);
				break;
			}
			catch (exception) {
			}
		}	

		Util::cleanScreen();

		// Get the user from the linked list based on UID
		Customer* selectedUser = nullptr;
		node<Customer>* editNode = editUser->head;
		while (editNode != nullptr) {
			if (editNode->data.getUID() == stoi(index)) {
				selectedUser = &(editNode->data);
				break;
			}
			editNode = editNode->nextAddress;
		}

		if (selectedUser) {
			// Edit the profile of the selected user
			if (selectedUser->editProfile()) {
				selectedUser->toString();
			}
		}
		else {
			cout << "User with UID " << index << " not found." << endl;
			Util::sleepClean(1);
			modifyUser(editUser);
		}
	};

	/*
		Display Feedback sort by latest date
		@param feedbackList - feedback list
	*/
	void displayFeedbackByDate(LinkedList<Feedback>* feedbackList) {
		LinkedList<Feedback>* newSortedList = new LinkedList<Feedback>();
		string** arr = feedbackList->convertTo2DArray();

		quicksort(arr, 0, feedbackList->size - 1, 5, true);

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 6; j++) {
				cout << arr[i][j] << ", ";
			}
			cout << endl;
		}
	};
};