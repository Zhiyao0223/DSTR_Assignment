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
	Validation validator;
	string resourcePath = "resources/";
	string fileName = "2023 QS World University Rankings.csv";
	string filePath = resourcePath + fileName;

	// Read CSV file and store data into doubly linked list
	LinkedList<University> readFile() {
		ifstream file(filePath);

		// Print error message if file not founds
		if (!file) {
			cerr << "Failed to open file" << endl;
			exit(1);
		}

		LinkedList<University>* list = new LinkedList<University>;
		string line;

		while (getline(file, line)) {
			string institutionName = "";
			string locationCode = "";
			string location = "";

			int numericData[17];

			stringstream ss(line);
			string field;
			int commaCounter = 0, arrayCounter = 0;

			while (getline(ss, field, ',')) {
				if (validator.isEmpty(field)) {
					field = "-";
				}
				else if (commaCounter > 0 && commaCounter < 4) {
					if (commaCounter == 1) institutionName = field;
					else if (commaCounter == 2) locationCode = field;
					location = field;
				}
				else {
					numericData[arrayCounter] = stoi(field);
					arrayCounter++;
				}
				list->insertToEndList(new University(institutionName, locationCode, location, numericData));

				commaCounter++;
			}
		}
		return *list;
	}


};