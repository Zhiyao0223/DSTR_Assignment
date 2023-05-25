#pragma once

#include <iostream>
#include "FileIO.h"
#include "University.h"
#include "LinkedList.h"`
using namespace std;

template <class T>
void selectionSort() {
	FileIO file;
	LinkedList<University>* uniList = file.readFile();
	uniList
}