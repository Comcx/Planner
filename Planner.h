#pragma once

#include <iostream>
#include <string>
#include <time.h>
#include <windows.h>

#include "Item.h"
#include "DayList.h"
#include "Pointer.h"

class Planner {

private:
	DayList dayList;
	int timeCode = 0;

	int getTimeCode() const { return this->timeCode; }
	int getTypeCode(std::string type) const;
	int compareType(std::string typeA, std::string typeB) const;

public:
	Planner() {}
	Planner(const std::string URL);
	Planner(const Planner&);

	int start();
	int refresh() {
		this->timeCode = this->dayList.pointer.syn();
		return 0;
	};
	Item getNewItem();
	Item getNewItem(int index);
	Item getItem() const { return this->dayList.getItem(); }
	Item getItem(int index) const { return this->dayList.getItem(index); };
	DayList getList() const { return this->dayList; }
	std::string getSystemTime() const;
	std::string getPanel();
	int searchToReplace() const;


};


Planner::Planner(const std::string URL) {
	this->dayList = getDayListFrom(URL);
}

Planner::Planner(const Planner& that) {
	this->dayList = that.getList();
	this->timeCode = that.getTimeCode();
}




int Planner::getTypeCode(std::string type) const {
	int ans = -1;

	if (type == "FREE") {
		ans = 16;
	} else if (type == "_DELAY") {
		ans = 0;
	} else if (type == "DELAY") {
		ans = 1;
	} else if (type == "_REPLACABLE") {
		ans = 2;
	} else if (type == "REPLACABLE") {
		ans = 3;
	}

	return ans;
}

std::string Planner::getSystemTime() const {
	time_t now = time(NULL);
	tm* t = localtime(&now);

	std::string ans("-> localTime: ");

	return ans + std::to_string(t->tm_hour) + ":" + 
		         std::to_string(t->tm_min) + ":" + std::to_string(t->tm_sec);
}

std::string Planner::getPanel() {
	this->refresh();

	std::string localTime = this->getSystemTime();
	Item item = this->getItem();
	std::string main = item.getMain();

	int timeCode = item.getTime();
	std::string time = std::to_string(timeCode / 2 + 6);
	if (timeCode % 2 == 1) {
		time += ":30 ~ " + std::to_string(timeCode / 2 + 6 + 1) + ":00";
	} else {
		time += ":00 ~ " + std::to_string(timeCode / 2 + 6) + ":30";
	}
	
	std::string type = item.getType();
	std::string note = item.getNote();

	std::string menu = "\nRefresh！！1, Next！！2, Skip！！3, Exit！！0\n";

	return localTime + "\n" + 
		"\n-> main: " + main +
		"\n-> time: " + time + 
		"\n-> type: " + type +
		"\n-> note: " + note +
		"\n" + menu;

}

int Planner::compareType(std::string typeA, std::string typeB) const {
	const int _DELAY = 0;
	const int DELAY = 1;
	const int _REPLACABLE = 2;
	const int REPLACABLE = 3;
	const int FREE = 16;

	int typeCodeA = this->getTypeCode(typeA);
	int typeCodeB = this->getTypeCode(typeB);

	return 0;
}

Item Planner::getNewItem() {
	int itemIndex = this->dayList.pointer.getNumber();
	std::cout << "-> Input your new item [format: main\ttype\tnote]" << std::endl;

	std::string line("2333");
	std::string main("");
	std::string type("");
	std::string note("");

	std::getline(std::cin, line);
	int counter = 0;
	for (char c : line) {
		if (c != '\t') {
			switch (counter) {
			case 0:
				main += c;
				break;
			case 1:
				type += c;
				break;
			case 2:
				note += c;
				break;
			default:
				std::cerr << "wrong format of input!";
			}//end switch
		}
		else {
			counter = counter + 1;
		}
	}//end for(char c : line)

	Item item(main, this->getTimeCode(), type, note);
	*(this->dayList.theItem(itemIndex)) = item;

	return item;
}

Item Planner::getNewItem(int index) {
	std::cout << "-> Input your new item [format: main\ttype\tnote]" << std::endl;

	std::string line("");
	std::string main("");
	std::string type("");
	std::string note("");

	getline(std::cin, line);
	int counter = 0;
	for (char c : line) {
		if (c != '\t') {
			switch (counter) {
			case 0:
				main += c;
				break;
			case 1:
				type += c;
				break;
			case 2:
				note += c;
				break;
			default:
				std::cerr << "wrong format of input!";
			}//end switch
		}
		else {
			counter = counter + 1;
		}
	}//end for(char c : line)

	Item item(main, this->getTimeCode(), type, note);

	return item;
}

int Planner::searchToReplace() const {
	int ans = -1;

	ans = this->dayList.searchByType("REPLACABLE", this->dayList.pointer.getNumber()+1);

	return ans;
}

int Planner::start() {

	bool decFlag = true;
	while (decFlag == true) {
		
		std::cout << this->getPanel() << std::endl;

		int order = -1;
		std::cin >> order;
		switch (order) {
		case 0:
			decFlag = false;
			break;
		case 1:
			this->refresh();
			break;
		case 2:
			std::cout << this->getItem(this->dayList.pointer.getNumber() + 1);
			break;
		case 3:
			if (this->getItem().getType() == "_DELAY" || 
				this->getItem().getType() == "FREE"   ||
				this->getItem().getType() == "REPLACABLE") {

				std::cin.get();
				*(this->dayList.theItem(this->dayList.pointer.getNumber())) = 
																	this->getNewItem();
			}
			else {
				std::cin.get();

				int replacedIndex = this->searchToReplace();
				if (replacedIndex == -1) {
					std::cout << "-> found no item to be replaced";
					break;
				} else {
					int currentIndex = this->dayList.pointer.getNumber();
					*(this->dayList.theItem(replacedIndex)) = this->dayList.getItem(currentIndex);
					*(this->dayList.theItem(currentIndex)) = this->getNewItem();
				}

			}
			break;
		default:
			std::cerr << "wrong order!";
			//there's something wrong here, this function is not prefect.
			break;
		}

		Sleep(1000);
		system("cls");
	}//end while(decFlag)

	return 0;
}


