#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "University.h"
#include "LinkedList.h"
#include "Validation.h"
using namespace std;

class FileIO {
public:
	string resourcePath = "resources/";
	string fileName = "2023 QS World University Rankings.csv";
	string filePath = resourcePath + fileName;

	/*
		Read CSV file and store data into doubly linked list
		@return Doubly linked list contain of all institution records.
	*/
	LinkedList<University>* readFile() {
		ifstream file(filePath);

		// Print error message if file not founds
		if (!file) {
			cerr << "Failed to open file" << endl;
			exit(1);
		}

		LinkedList<University>* list = new LinkedList<University>();
		string line;

		// Ignore first line
		getline(file, line);
		float numericData[18];

		while (getline(file, line)) {
			string institutionName = "";
			string locationCode = "";
			string location = "";

			stringstream ss(line);
			string field;
			int commaCounter = 0, arrayCounter = 0;

			while (getline(ss, field, ',')) {
				if (Validation::isEmpty(field)) {
					field = "-";
				}
				else if (field[0] == ' ') {
					institutionName = field.substr(1);
				}
				else if (field.front() == '\"' && field.back() != '\"') {
					string nextSentence;

					while (getline(ss, nextSentence, ',')) {
						field += nextSentence;

						if (!Validation::isEmpty(nextSentence) && nextSentence.back() == '\"') {
							institutionName = field.substr(1, field.length() - 2);
							break;
						}
					}
				}
				else if (field.front() == '\"' && field.back() == '\"') {
					field.erase(remove(field.begin(), field.end(), '\"'), field.end());
					institutionName = field;
				}
				else if (commaCounter > 0 && commaCounter < 4) {
					if (commaCounter == 1) institutionName = field;
					else if (commaCounter == 2) locationCode = field;
					else location = field;
				}
				else {
					if (field == "-") field = "-1";

					numericData[arrayCounter] = stoi(field);
					arrayCounter++;
				}
				commaCounter++;
			}
			University* tmp = new University(institutionName, locationCode, location, numericData);
			list->insertToEndList(tmp);
			delete tmp;
		}
		return list;
	}

	// On progress
	template <class T>
	bool writeFile(LinkedList<T>* data) {
		// Write data to file
		ofstream file(filePath);

		// Print error message if file not founds
		cout << "File not found." << endl;
	}
};