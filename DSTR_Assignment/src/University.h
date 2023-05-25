#pragma once

#include <iostream>
using namespace std;

class University {
protected:
	/*
		rank - primary key
		institution - university name
		location - country of university
		AR - academic reputation
		ER - employer reputation
		FSR - faculty / student ratio
		CPF - citations per faculty
		IFR - internation faculty ratio
		ISR - international student ratio
		IRN - international research network
		GER - employment outcome
		scoreScaled - overall score of institution
	*/

	int rank;
	string institution;
	string locationCode;
	string location;
	int ArScore;
	int ArRank;
	int ErScore;
	int ErRank;
	int FsrScore;
	int FsrRank;
	int CpfScore;
	int CpfRank;
	int IfrScore;
	int IfrRank;
	int IsrScore;
	int IsrRank;
	int IrnScore;
	int IrnRank;
	int GerScore;
	int GerRank;
	int scoreScaled;

public:
	// Constructor
	University() {
		// Delete this constructor later coz no use, declare for no error temporary.
	}

	University(string tmpName, string tmpLocationCode, string tmpLocation, float data[]) {
		institution = tmpName;
		location = tmpLocation;
		locationCode = tmpLocationCode;
		rank = data[0];
		ArScore = data[1];
		ArRank = data[2];
		ErScore = data[3];
		ErRank = data[4];
		FsrScore = data[5];
		FsrRank = data[6];
		CpfScore = data[7];
		CpfRank = data[8];
		IfrScore = data[9];
		IfrRank = data[10];
		IsrScore = data[11];
		IsrRank = data[12];
		IrnScore = data[13];
		IrnRank = data[14];
		GerScore = data[15];
		GerRank = data[16];
		scoreScaled = data[17];
	}

	// Display University Information
	void display() {
		cout << "Rank: " << getRank() << endl;
		cout << "Intitution Name: " << getInstitution() << endl;
		cout << "Location :" << getLocation() << " (" << getLocationCode() << ")" << endl;
		cout << "Academic Reputation (rank): " << getArScore() << " (" << getArRank() << ")" << endl;
		cout << "Employer Reputation (rank): " << getErScore() << " (" << getErRank() << ")" << endl;
		cout << "Faculty / Student Ratio (rank): " << getFsrScore() << " (" << getFsrRank() << ")" << endl;
		cout << "Citations Per Faculty (rank): " << getCpfScore() << " (" << getCpfRank() << ")" << endl;
		cout << "Internation Faculty Ratio (rank): " << getIfrScore() << " (" << getIfrRank() << ")" << endl;
		cout << "Internation Student Ratio (rank): " << getIsrScore() << " (" << getIsrRank() << ")" << endl;
		cout << "International Research Network (rank): " << getIrnScore() << " (" << getIrnRank() << ")" << endl;
		cout << "Employment Outcome (rank): " << getGerScore() << " (" << getGerRank() << ")" << endl;
		cout << "Score Scaled: " << scoreScaled << endl << endl;
	}

	/*
		Sort University (2 algorithm needed), parameter not fix yet depend design.
		@param data - Data to be sorted
		@return Sorted data
	*/
	University* sortUniversity(University* data) {
		// To complete
		return new University();
	}

	/*
		Compare two university. Param not fix yet can change
	*/
	University* compareUniversity(int university[]) {
		// To complete
		return new University();
	}

	// Getter Functions
	int getRank() {
		return rank;
	}

	string getInstitution() {
		return institution;
	}

	string getLocationCode() {
		return locationCode;
	}

	string getLocation() {
		return location;
	}

	int getArScore() {
		return ArScore;
	}

	int getArRank() {
		return ArRank;
	}

	int getErScore() {
		return ErScore;
	}

	int getErRank() {
		return ErRank;
	}

	int getFsrScore() {
		return FsrScore;
	}

	int getFsrRank() {
		return FsrRank;
	}

	int getCpfScore() {
		return CpfScore;
	}

	int getCpfRank() {
		return CpfRank;
	}

	int getIfrScore() {
		return IfrScore;
	}

	int getIfrRank() {
		return IfrRank;
	}

	int getIsrScore() {
		return IsrScore;
	}

	int getIsrRank() {
		return IsrRank;
	}

	int getIrnScore() {
		return IrnScore;
	}

	int getIrnRank() {
		return IrnRank;
	}

	int getGerScore() {
		return GerScore;
	}

	int getGerRank() {
		return GerRank;
	}

	int getScoreScaled() {
		return scoreScaled;
	}

	// Setter Functions
	void setRank(int tmpData) {
		rank = tmpData;
	}

	void setInstitution(string tmpData) {
		institution = tmpData;
	}

	void setLocationCode(string tmpData) {
		locationCode = tmpData;
	}

	void setLocation(string tmpData) {
		location = tmpData;
	}

	void setArScore(int tmpData) {
		ArScore = tmpData;
	}

	void setArRank(int tmpData) {
		ArRank = tmpData;
	}

	void setErScore(int tmpData) {
		ErScore = tmpData;
	}

	void setErRank(int tmpData) {
		ErRank = tmpData;
	}

	void setFsrScore(int tmpData) {
		FsrScore = tmpData;
	}

	void setFsrRank(int tmpData) {
		FsrRank = tmpData;
	}

	void setCpfScore(int tmpData) {
		CpfScore = tmpData;
	}

	void setCpfRank(int tmpData) {
		CpfRank = tmpData;
	}

	void setIfrScore(int tmpData) {
		IfrScore = tmpData;
	}

	void setIfrRank(int tmpData) {
		IfrRank = tmpData;
	}

	void setIsrScore(int tmpData) {
		IsrScore = tmpData;
	}

	void setIsrRank(int tmpData) {
		IsrRank = tmpData;
	}

	void setIrnScore(int tmpData) {
		IrnScore = tmpData;
	}

	void setIrnRank(int tmpData) {
		IrnRank = tmpData;
	}

	void setGerScore(int tmpData) {
		GerScore = tmpData;
	}

	void setGerRank(int tmpData) {
		GerRank = tmpData;
	}

	void setScoreScaled(int tmpData) {
		scoreScaled = tmpData;
	}
};