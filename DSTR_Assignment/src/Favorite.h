#pragma once

#include <iostream>
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