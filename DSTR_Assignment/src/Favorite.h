#pragma once

#include <iostream>
#include "Customer.h"
#include "University.h"
#include "LinkedList.h"
using namespace std;

class Favorite {
protected:
	int ID;
	int UID;
	int insitution;

public:
	Favorite(int tmpID, int tmpUID, int tmpInstitution) {
		ID = tmpID;
		UID = tmpUID;
		insitution = tmpInstitution;
	}

	Favorite() {
		ID = UID = insitution = NULL;
	}

	//// Return specified column value
	//template <typename T>
	//T getColumn(int index) {
	//	/*
	//	*	Column Index:
	//	*	0 - ID
	//	*	1 - UID
	//	*	2 - institution
	//	*/
	//	switch (index) {
	//	case 0:
	//		return ID;
	//	case 1:
	//		return UID;
	//	case 2:
	//		return insitution;
	//	}
	//}

	// Get specific university from list
	University* getUniversity(int id) {
		FileIO file;
		LinkedList<University>* uniList = file.readFile();
		node<University>* tmp = uniList->head;

		while (tmp != NULL) {
			if (tmp->data.getRank() == id) return &tmp->data;
			tmp = tmp->nextAddress;
		}
		return NULL;
	}

	string toDataString() {
		//string username = custList->getName(custList, UID);
		//string insitutionName = uniList->getName(uniList, insitution);

		//return to_string(ID) + "," + username + "," + insitutionName;
		return to_string(ID) + "," + to_string(UID) + "," + to_string(insitution);
	}

	// Getter Function
	int getID() {
		return ID;
	}

	int getUID() {
		return UID;
	}

	int getInstitutionRank() {
		return insitution;
	}

	// Setter Function
	void setID(int tmp) {
		ID = tmp;
	}

	void setUID(int tmp) {
		UID = tmp;
	}

	void setInstition(int tmp) {
		insitution = tmp;
	}
};