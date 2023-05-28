#pragma once

#include <iostream>
#include "Customer.h"
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
	int dataCount;

	// Constructor
	University() {
		dataCount = 21;
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
		dataCount = 21;
	}

	string getColumn(int columnIndex) {
		/*
		*	Column index:
		*	0 - rank;
		*	1 - institution
		*	2 - locationCode
		*	3 - location
		*	4 - ArScore
		*	5 - ArRank
		*	6 - ErScore
		*	7 - ErRank
		*	8 - FsrScore
		*	9 - FsrRank
		*	10 - CpfScore
		*	11 - CpfRank
		*	12 - IfrScore
		*	13 - IfrRank
		*	14 - IsrScore
		*	15 - IsrRank
		*	16 - IrnScore
		*	17 - IrnRank
		*	18 - GerScore
		*	19 - GerRank
		*	20 - Scorescaled
		*/

		switch (columnIndex) {
		case 0:
			return to_string(rank);
		case 1:
			return institution;
		case 2:
			return locationCode;
		case 3:
			return location;
		case 4:
			return to_string(ArScore);
		case 5:
			return to_string(ArRank);
		case 6:
			return to_string(ErScore);
		case 7:
			return to_string(ErRank);
		case 8:
			return to_string(FsrScore);
		case 9:
			return to_string(FsrRank);
		case 10:
			return to_string(CpfScore);
		case 11:
			return to_string(CpfRank);
		case 12:
			return to_string(IfrScore);
		case 13:
			return to_string(IfrRank);
		case 14:
			return to_string(IsrScore);
		case 15:
			return to_string(IsrRank);
		case 16:
			return to_string(IrnScore);
		case 17:
			return to_string(IrnRank);
		case 18:
			return to_string(GerScore);
		case 19:
			return to_string(GerRank);
		case 20:
			return to_string(scoreScaled);
		}
	}

	// Display University Information
	void display() {
		string* arr = toStringArray();
		for (int i = 4; i < dataCount; i++) {
			if (arr[i] == "-1") {
				arr[i] = "-";
			}
			else if (arr[i] == "501" || arr[i] == "601") {
				arr[i] += "+";
			}
		}

		cout << "Rank " << "\t\t\t\t\t" << ": " << getRank() << endl;
		cout << "Intitution Name" << "\t\t\t\t" << ": " << getInstitution() << endl;
		cout << "Location " << "\t\t\t\t" << ": " << getLocation() << " (" << getLocationCode() << ")" << endl;
		cout << "Academic Reputation (rank)" << "\t\t" << ": " << arr[4] << " (" << arr[5] << ")" << endl;
		cout << "Employer Reputation (rank)" << "\t\t" << ": " << arr[6] << " (" << arr[7] << ")" << endl;
		cout << "Faculty / Student Ratio (rank)" << "\t\t" << ": " << arr[8] << " (" << arr[9] << ")" << endl;
		cout << "Citations Per Faculty (rank)" << "\t\t" << ": " << arr[10] << " (" << arr[11] << ")" << endl;
		cout << "Internation Faculty Ratio (rank)" << "\t" << ": " << arr[12] << " (" << arr[13] << ")" << endl;
		cout << "Internation Student Ratio (rank)" << "\t" << ": " << arr[14] << " (" << arr[15] << ")" << endl;
		cout << "International Research Network (rank)" << "\t" << ": " << arr[16] << " (" << arr[17] << ")" << endl;
		cout << "Employment Outcome (rank)" << "\t\t" << ": " << arr[18] << " (" << arr[19] << ")" << endl;
		cout << "Overall Score" << "\t\t\t\t" << ": " << arr[20] << endl;
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

	string* toStringArray() {
		return new string[21]{ to_string(rank),institution, locationCode, location, to_string(ArScore), to_string(ArRank),
			to_string(ErScore), to_string(ErRank), to_string(FsrScore), to_string(FsrRank), to_string(CpfScore),
			to_string(CpfRank), to_string(IfrScore), to_string(IfrRank), to_string(IsrScore), to_string(IsrRank),
			to_string(IrnScore), to_string(IrnRank), to_string(GerScore), to_string(GerRank), to_string(scoreScaled) };
	}

	string toDataString() {
		return to_string(rank) + "," + institution + "," + locationCode + "," + location + "," + to_string(ArScore) + ","
			+ to_string(ArRank) + "," + to_string(ErScore) + "," + to_string(ErRank) + "," + to_string(FsrScore) + ","
			+ to_string(FsrRank) + "," + to_string(CpfScore) + "," + to_string(CpfRank) + "," + to_string(IfrScore) + ","
			+ to_string(IfrRank) + "," + to_string(IsrScore) + "," + to_string(IsrRank) + "," + to_string(IrnScore) + ","
			+ to_string(IrnRank) + "," + to_string(GerScore) + "," + to_string(GerRank) + "," + to_string(scoreScaled);
	}

	/*
	*	Set object value from string array. Used in converting 2D array to linked list
	*	@param dataArr - linked list data in array format
	*/
	void setColumnValue(string* dataArr) {
		this->setRank(stoi(dataArr[0]));
		this->setInstitution(dataArr[1]);
		this->setLocationCode(dataArr[2]);
		this->setLocation(dataArr[3]);
		this->setArScore(stoi(dataArr[4]));
		this->setArRank(stoi(dataArr[5]));
		this->setErScore(stoi(dataArr[6]));
		this->setErRank(stoi(dataArr[7]));
		this->setFsrScore(stoi(dataArr[8]));
		this->setFsrRank(stoi(dataArr[9]));
		this->setCpfScore(stoi(dataArr[10]));
		this->setCpfRank(stoi(dataArr[11]));
		this->setIfrScore(stoi(dataArr[12]));
		this->setIfrRank(stoi(dataArr[13]));
		this->setIsrScore(stoi(dataArr[14]));
		this->setIsrRank(stoi(dataArr[15]));
		this->setIrnScore(stoi(dataArr[16]));
		this->setIrnRank(stoi(dataArr[17]));
		this->setGerScore(stoi(dataArr[18]));
		this->setGerRank(stoi(dataArr[19]));
		this->setScoreScaled(stoi(dataArr[20]));
	}

	// Getter Functions
	int getDataCount() {
		return dataCount;
	}

	int getRank() {
		return rank;
	}

	int getUID() {
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