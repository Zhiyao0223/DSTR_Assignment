#pragma once

#include <iostream>
using namespace std;

enum class FeedbackStatus
{
	OPEN,
	IN_PROGRESS,
	RESOLVED,
	CLOSED
};


class Feedback {
protected:
	int ID;
	int UID;
	string comment;
	Feedback* reply;
	FeedbackStatus status;
public:
	Feedback(int tmpID, int tmpUID, string tmpComment) {
		ID = tmpID;
		UID = tmpUID;
		comment = tmpComment;
		reply = NULL;
		status = FeedbackStatus::OPEN;
	}

	// Multi-level linked list for continous replies
	Feedback* createNewReply(int tmpID, int tmpUID, string tmpComment) {
		return new Feedback(tmpID, tmpUID, tmpComment);
	}

	// Getter
	int getID() {
		return ID;
	}

	int getUID() {
		return UID;
	}

	string getComment() {
		return comment;
	}

	Feedback* getReply() {
		return reply;
	}

	// Setter
	void setID(int tmp) {
		ID = tmp;
	}

	void setUID(int tmp) {
		UID = tmp;
	}

	void setComment(string tmp) {
		comment = tmp;
	}

	void setReply(int ID, int UID, string tmpComment) {
		reply = createNewReply(ID, UID, tmpComment);
	}

	void setStatus(FeedbackStatus newStatus) {
		status = newStatus;
	}
};