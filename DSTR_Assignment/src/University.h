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
	// Pointer to previous and next address
	University* prevAddress;
	University* nextAddress;


	// Constructor
	University() {
		// Get all data from dataset
	}

	University(string tmpName, string tmpLocation, int data[]) {
		institution = tmpName;
		location = tmpLocation;
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
		IfrRank = data[9];
		IsrScore = data[10];
		IsrRank = data[11];
		IrnScore = data[12];
		IrnRank = data[13];
		GerScore = data[14];
		GerRank = data[15];
		scoreScaled = data[16];
	}

	
	// Display Available University
	template<class T>
	void displayAllUniversity(T data) {
		// To Complete
		return;
	}

	// Sort University (2 algorithm needed)
	University* sortUniversity(University* data) {
		// To complete
		return new University();
	}

	// Compare two university
	University* compareUniversity(int university[]) {
		// To complete
		return new University();
	}


	// Getter Functions
	int getRank() {
		return rank;
	}

	string getInstitution(){
		return institution;
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

	int getIrnRank(){
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