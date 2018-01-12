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
	int timeNow = 0;

public:
	Planner() {}
	Planner(const Planner&);

	int start();
	int refresh() {
		this->timeNow = this->dayList.pointer.syn();
		return 0;
	};
	int control();
	Item getItem() { return this->dayList.getItem(); }
	DayList getList() const { return this->dayList; }
	int getTime() const { return this->timeNow; }

};

Planner::Planner(const Planner& that) {
	this->dayList = that.getList();
	this->timeNow = that.getTime();
}


int Planner::control() {
	int time = this->dayList.pointer.getNumber();
	std::cout << "\nRefresh！！1�� Exit！！0\n" << std::endl;

	

	return 0;
}

int Planner::start() {
	this->dayList = getDayListFrom("C:/Users/HP/Desktop/main.txt");

	bool decFlag = true;
	while (decFlag == true) {
		time_t now = time(NULL);
		tm* t = localtime(&now);
		std::cout << "-> time: " << t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec << std::endl;

		this->control();

		int order = -1;
		std::cin >> order;
		switch (order) {
		case 0:
			decFlag = false;
			break;
		case 1:
			this->refresh();
			std::cout << this->getItem();
			break;
		case 2:
			break;
		default:
			std::cerr << "wrong order!";
			break;
		}

		Sleep(1000);
		system("cls");
	}//end while(decFlag)

	return 0;
}


