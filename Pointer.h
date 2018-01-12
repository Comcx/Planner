/*
* Copyright (c) 2017 , LAIN
* All rights reserved
*
* name : Pointer.h
* contents : TOP SECRET
*
* developed by Comcx
* created time : 
*
*
*/

#ifndef _POINTER_H
#define _POINTER_H

#include <string>
#include <time.h>
#include "Item.h"
using std::string;

class Pointer {

private:
	int number = 0;
	int synFlag = 0;

public:
	Pointer(){};
	Pointer(Item* dayItem[]);
	Pointer(const Pointer&);

	int syn();
	int pointNext();
	int getNumber() const { return this->number; }

};

Pointer::Pointer(Item* dayItem[]) {
	this->number = 0;
	this->synFlag = 0;
}

Pointer::Pointer(const Pointer& that) {
	this->number = that.number;
	this->synFlag = that.synFlag;
}


int Pointer::syn() {
	time_t now = time(NULL);
	tm* t = localtime(&now);
	int timeCode = (t->tm_hour - 6) * 2 + (t->tm_min / 30);

	this->number = timeCode;

	return timeCode;
}

int Pointer::pointNext() {
	this->number = this->number + 1;
	return this->number;
}



#endif
