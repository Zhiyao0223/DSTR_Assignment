#pragma once

#include <iostream>
#include <conio.h>
#include <chrono>
#include <thread>
#include <string>
#include "LinkedList.h"
using namespace std;

// Extra Features
class Util {
public:
	// Clean screen
	static void cleanScreen() {
		system("cls");
	}

	// Freeze system
	static void sleep(int second) {
		this_thread::sleep_for(chrono::seconds(second));
	}

	// Pause System
	static void pause() {
		system("pause");
	}

	// Freeze and sleep screen
	static void sleepClean(int second) {
		sleep(second);
		cleanScreen();
	}

	// Masking password field
	static string getPassword() {
		string tmpPass;
		char ch;

		// Capture input until Enter is pressed
		while ((ch = _getch()) != '\r') {
			// Handle backspace
			if (ch == '\b') {
				if (tmpPass.length() > 0) {
					cout << "\b \b";
					tmpPass.pop_back();
				}
			}
			else {
				tmpPass.push_back(ch);
				cout << "*";
			}
		}
		cout << endl;

		return tmpPass;
	}

	// Destroy 2d Array, prevent memory leak
	static void destroy2dArray(int** arr, int row) {
		for (int i = 0; i < row; i++) {
			delete[] arr[i];
		}
		delete[] arr;
	}

	// Print border line for header
	static void printBorderLine() {
		cout << "====================================================================================" << endl;
	}

	// Print header
	static void printHeader(string title) {
		Util::cleanScreen();
		Util::printBorderLine();
		cout << "\t\t\t\t" << title << endl;
		Util::printBorderLine();
		cout << endl;
	}
};