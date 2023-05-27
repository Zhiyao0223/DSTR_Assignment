#pragma once

#include <iostream>
#include "Customer.h"
#include "University.h"
#include "LinkedList.h"
#include "Sort.h"
using namespace std;

// Prevent typo and easier manage data
enum class FeedbackStatus
{
	OPEN,
	IN_PROGRESS,
	RESOLVED,
	CLOSED
};

enum class UserRole {
	ADMIN,
	REGISTERED_USER,
	NORMAL_USER
};

class Feedback {
protected:
	int ID;
	int UID;
	string title;
	string comment;
	Feedback* reply;
	FeedbackStatus status;
	UserRole role;
	Date* date;
	bool isReply;

public:
	int dataCount;

	Feedback() {
		ID = UID = NULL;
		reply = NULL;
		comment = "";
		date = new Date();
		role = UserRole::NORMAL_USER;
		isReply = false;
	}

	Feedback(int tmpID, int tmpUID, string tmpTitle, string tmpComment, bool tmpIsReply=false, bool tmpIsAdmin=false) {
		ID = tmpID;
		UID = tmpUID;
		title = tmpTitle;
		comment = tmpComment;
		reply = NULL;
		status = FeedbackStatus::OPEN;
		date = new Date();
		setDate();
		dataCount = 6;
		isReply = tmpIsReply;

		role = (tmpIsAdmin) ? UserRole::ADMIN : UserRole::REGISTERED_USER;
	}

	/*
		Return specific column value indexed
	*/
	//template <typename T>
	//T getColumn(int index) {
	//	/*
	//	*	Column Index:
	//	*	0 - ID
	//	*	1 - UID
	//	*	2 - status
	//	*/
	//	switch (index) {
	//	case 0:
	//		return ID;
	//	case 1:
	//		return UID;
	//	case 2:
	//		return FeedbackStatusToString(status);
	//	}
	//}

	// Return string of data for csv export
	string toDataString() {
		//string username = custList->getName(custList, UID);

		//return to_string(ID) + "," + username + "," + UserRoleToString(role) + "," + title + "," + comment + ","
		//	+ getReply() + "," + enumToString(status) + "," + date->toString();
		return to_string(ID) + "," + to_string(UID) + "," + UserRoleToString(role) + "," + title + "," + comment + ","
			+ getReply() + "," + enumToString(status) + "," + date->toString();
	}

	/*
		Multi-level linked list for continous replies

		@param tmpID - Ticket ID
		@param tmpUID - userID who replied
		@param tmpComment - Comment
		@return Pointer of new feedback node
	*/
	Feedback* createNewReply(int tmpID, int tmpUID, string tmpTitle, string tmpComment, bool isAdmin) {
		return new Feedback(tmpID, tmpUID, tmpTitle, tmpComment, true, isAdmin);
	}

	string* toStringArray() {
		return new string[6]{to_string(getID()), to_string(getUID()), getTitle(), getComment(), getStatus(), getDate()};
	}

	/*
		Display feedback in detail
	*/
	void display(LinkedList<Feedback>* tmpFeedbackList, bool isAdmin = false) {
		LinkedList<Feedback>* feedbackList = new LinkedList<Feedback>();
		string** arr = tmpFeedbackList->convertTo2DArray();

		quicksort(arr, 0, tmpFeedbackList->size - 1, 5, true);
		feedbackList->convertToLinkedList(arr, tmpFeedbackList->size);

		Util::cleanScreen();

		cout << "Ticket ID" << "\t" << ": " << ID << endl
			<< "UID:" << "\t\t" << ": " << UID << endl
			<< "Status: " << "\t" << ": " << FeedbackStatusToString(status) << endl
			<< "Title" << "\t\t" << ": " << title << endl << endl
			<< "#-------- Comment ---------#" << endl << endl
			<< UserRoleToString(role) << " [" << date->toString() << "] :" << endl
			<< comment << endl << endl;

		Feedback* currentReply = this->reply;
		Feedback* tmp = currentReply;
		while (currentReply != NULL) {
			cout << UserRoleToString(currentReply->role) << " [" << date->toString() << "] :" << endl
				<< currentReply->getComment() << endl << endl;

			tmp = currentReply;
			currentReply = currentReply->reply;
		}

		cout << "Please select an option:" << endl
			<< "[1] Reply" << endl
			<< "[2] Back" << endl
			<< "Option: ";

		string option, tmpComment;
		int newUID = feedbackList->getNewUID();
		Feedback* newNode = new Feedback();
		cin >> option;

		if (option == "1") {
			cout << endl << endl << "Please enter your comment: ";
			cin.ignore();
			getline(cin, tmpComment);

			newNode = createNewReply(newUID, this->UID, this->title, tmpComment, isAdmin);
			feedbackList->insertToEndList(newNode);

			if (tmp == NULL) {
				this->reply = &(feedbackList->tail->data);
			}
			else {
				tmp->reply = &(feedbackList->tail->data);
			}

			this->setStatus(FeedbackStatus::IN_PROGRESS);

			cout << "Reply successfully" << endl;
			Util::sleep(1);
		}
		else if (option != "2") {
			cout << "Invalid option" << endl;
		}
		cin.clear();
	}

	/*
		Convert enum to string
		@param tmpStatus - enum FeedbackStatus
		@return value of enum
	*/
	string FeedbackStatusToString(FeedbackStatus tmpStatus) {
		switch (tmpStatus) {
		case FeedbackStatus::OPEN:
			return "OPEN";
		case FeedbackStatus::IN_PROGRESS:
			return "IN_PROGRESS";
		case FeedbackStatus::RESOLVED:
			return "RESOLVED";
		case FeedbackStatus::CLOSED:
			return "CLOSED";
		}
	}

	string UserRoleToString(UserRole tmpRole) {
		switch (tmpRole) {
		case UserRole::ADMIN:
			return "ADMIN";
		case UserRole::REGISTERED_USER:
			return "USER";
		case UserRole::NORMAL_USER:
			return "GUEST";
		}
	}

	// Getter
	int getID() {
		return ID;
	}

	int getDataCount() {
		return dataCount;
	}

	int getUID() {
		return UID;
	}

	string getTitle() {
		return title;
	}

	string getComment() {
		return comment;
	}

	string getReply() {
		Feedback* tmp = reply;

		if (tmp == NULL) {
			return "-";
		}

		string replyID = to_string(reply->getID());
		while(tmp->reply != NULL) {
			tmp = tmp->reply;
			replyID += "," + to_string(tmp->getID());
		}

		return replyID;
	}

	string enumToString(FeedbackStatus status) {
		switch (status) {
		case FeedbackStatus::OPEN:
			return "OPEN";
		case FeedbackStatus::IN_PROGRESS:
			return "IN_PROGRESS";
		case FeedbackStatus::RESOLVED:
			return "RESOLVED";
		case FeedbackStatus::CLOSED:
			return "CLOSED";
		}
	}

	string getStatus() {
		return FeedbackStatusToString(status);
	}

	string getRole() {
		return UserRoleToString(role);
	}

	string getDate() {
		return date->toString();
	}

	bool getIsReply() {
		return isReply;
	}

	// Setter
	void setID(int tmp) {
		ID = tmp;
	}

	void setUID(int tmp) {
		UID = tmp;
	}

	void setTitle(string tmp) {
		title = tmp;
	}

	void setComment(string tmp) {
		comment = tmp;
	}

	void setReply(int ID, int UID, string tmpTitle, string tmpComment, bool isAdmin=false) {
		reply = createNewReply(ID, UID, tmpTitle, tmpComment, isAdmin);
	}

	void setStatus(FeedbackStatus newStatus) {
		status = newStatus;
	}

	void setRole(UserRole tmpRole) {
		role = tmpRole;
	}

	void setDate() {
		date->setToday();
	}

	void setSpecificDate(string tmpDate) {
		this->date = new Date(tmpDate);
	}

	void setColumnValue(string* dataArr) {
		setID(stoi(dataArr[0]));
		setUID(stoi(dataArr[1]));
		setTitle(dataArr[2]);
		setComment(dataArr[3]);
		
		
		if (dataArr[4] == "OPEN") setStatus(FeedbackStatus::OPEN);
		else if (dataArr[4] == "IN_PROGRESS") setStatus(FeedbackStatus::IN_PROGRESS);
		else if (dataArr[4] == "RESOLVED") setStatus(FeedbackStatus::RESOLVED);
		else if (dataArr[4] == "CLOSED") setStatus(FeedbackStatus::CLOSED);

		setSpecificDate(dataArr[5]);
	}

	void setIsReply(bool tmp) {
		isReply = tmp;
	}

	void setIsAdmin() {
		this->setRole(UserRole::ADMIN);
	}
};