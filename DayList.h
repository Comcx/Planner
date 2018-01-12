
#pragma once
#include "Pointer.h"
#include "Item.h"
#include <vector>

/**
	class DayItem: records of the day
*/

class DayList {

private:
	int week = 0;
	Item header = Item("header", -1, 'x', "just header, If you see me, you've got sth wrong");
	std::vector<Item> list = {header};

public:
	Pointer pointer;
	int size = 0;

	DayList() {};
	DayList(const int week) { this->week = week; }
	DayList(const DayList&);

	int addItem(const Item&);
	int getWeek() const { return this->week; }
	std::vector<Item> getList() const { return this->list; }
	Item getItem() const;
	Item getItem(int index) const;


};


DayList::DayList(const DayList& that) {
	this->week = that.getWeek();
	this->list = that.getList();
	this->size = that.size;
	this->pointer = that.pointer;
}

int DayList::addItem(const Item& that) {
	this->list.push_back(that);
	this->size++;

	return 0;
}


inline Item DayList::getItem(int index) const {
	if (index <= this->size)
		return this->list[index];
	else {
		std::cerr << "-> illegal index!";
		return this->list[0];
	}
}

inline Item DayList::getItem() const {
	if (this->pointer.getNumber() <= this->size) {
		return this->list[this->pointer.getNumber()];
	}else {
		std::cerr << "-> illegal index!";
		return this->list[0];
	}
}



DayList getDayListFrom(const std::string URL) {
	DayList list;

	std::ifstream file(URL);
	std::string line;

	int lineCounter = 1;
	while (getline(file, line)) {
		std::string main("");
		char type('x');
		std::string note("");

		int counter = 0;
		for (char c : line) {
			if (c != '\t') {
				switch (counter) {
				case 0:
					main += c;
					break;
				case 1:
					type = c;
					break;
				case 2:
					note += c;
					break;
				default:
					std::cerr << "wrong format of file!";
				}//end switch
			} else {
				counter = counter + 1;
			}
		}//end for(char c : line)

		Item item(main, lineCounter, type, note);
		list.addItem(item);

		lineCounter = lineCounter + 1;
	}//end while(getline(file, line))

	return list;
}











