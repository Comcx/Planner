/*
* Copyright (c) 2017 , LAIN
* All rights reserved
*
* name : Item.h
* contents : TOP SECRET
*
* developed by Comcx
* created time : 
*
*
*/

#ifndef _ITEM_H
#define _ITEM_H

#include <string>
#include <fstream>
//#include "lain.h"


using std::string;

/**
	class Item: one record of the event
*/

class Item {

private:
	string main;
	int time;
	string type;
	string note;

public:
	Item(){};
	Item(string main, int time, string type, string note);
	Item(const Item&);
	//~Item(){};

	bool operator==(const Item&);
	bool operator!=(const Item&);
	friend std::ostream& operator<<(std::ostream& os, const Item& that);
	
	string getMain() const;
	int getTime() const;
	string getType() const;
	string getNote()const;

	int changeMain(string main);
	int changeTime(int time);
	int changeType(string type);
	int changeNote(string note);


};


Item::Item(string main, int time, string type, string note) {
	this->main = main;
	this->time = time;
	this->type = type;
	this->note = note;

}

Item::Item(const Item& that) {
	this->main = that.getMain();
	this->time = that.getTime();
	this->type = that.getType();
	this->note = that.getNote();
}

bool Item::operator==(const Item& that) {
	return this->main == that.getMain() &&
		   this->time == that.getTime() &&
		   this->type == that.getType() &&
		   this->note == that.getNote();
}
bool Item::operator!=(const Item& that) {
	return this->main != that.getMain() ||
		   this->time != that.getTime() ||
		   this->type != that.getType() ||
		   this->note != that.getNote();
}


string Item::getMain() const {
	return this->main;
}

int Item::getTime() const {
	return this->time;
}

string Item::getType() const {
	return this->type;
}

string Item::getNote() const {
	return this->note;
}


int Item::changeMain(string main) {
	this->main = main;
	return this->main == main? 1 : 0;
}

int Item::changeTime(int time) {
	this->time = time;
	return this->time == time? 1 : 0;
}

int Item::changeType(string type) {
	this->type = type;
	return (this->type == type)? 1 : 0;
}

int Item::changeNote(string note) {
	this->note = note;
	return this->note == note? 1 : 0;
}

std::ostream& operator<<(std::ostream& os, const Item& that){  
	os << that.getMain() << " " << that.getTime() << " " << that.getType() << " " << that.getNote();  
	return os;  
}  






#endif
