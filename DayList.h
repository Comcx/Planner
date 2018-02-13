
#pragma once

#include "Item.h"
#include "lainlib.h"


namespace planner {

	class Pointer {

	private:
		int number_;
		bool syn_flag_;

	public:
		Pointer() : number_(0), syn_flag_(false) {}
		Pointer(const Pointer &that) : number_(that.number()), syn_flag_(that.syn_flag()) {}

		int number() const { return this->number_; }
		bool syn_flag() const { return this->syn_flag_; }
		int syn();
		int operator++(int) { return ++this->number_; }

	};


	int Pointer::syn() {
		time_t now = time(NULL);
		tm* t = localtime(&now);
		int timeCode = (t->tm_hour - 6) * 2 + (t->tm_min / 30);

		this->number_ = timeCode;
		this->syn_flag_ = true;

		return timeCode;
	}







	/**
	* @class: DayItem: records of the day
	* @author: Comcx
	* 
	* 
	*/

	class DayList {

	private:
		int week_ = 0;
		Item header_ = Item("header", -1, "HEADER", "just header, If you see me, you've got sth wrong");
		std::vector<Item> list_ = { header_ };

	public:
		Pointer pointer;
		int size = 0;

		DayList() {}
		DayList(const int week) { this->week_ = week; }
		DayList(const DayList &that): 
			week_(that.week()), list_(that.list()), size(that.size), pointer(that.pointer) {}

		DayList get_daylist_from(const std::string URL);
		int put_dayList_to(const std::string URL);
		
		int week() const { return this->week_; }
		std::vector<Item> list() const { return this->list_; }
		Item item() const;
		Item at(int index) const;
		int search_by_type(std::string type, int from) const;

		Item& operator[](int index);
		int operator+=(const Item&);
		friend std::ostream& operator<<(std::ostream& os, const DayList& that);

	};
	

	int DayList::operator+=(const Item& that) {
		this->list_.push_back(that);
		this->size++;

		return 0;
	}


	inline Item DayList::at(int index) const {
		if (index <= this->size)
			return this->list_[index];
		else {
			std::cerr << "-> illegal index!";
			return this->list_[0];
		}
	}

	inline Item& DayList::operator[](int index) {
		if (index <= this->size)
			return this->list_[index];
		else {
			std::cerr << "-> illegal index!";
			return this->list_[0];
		}
	}

	inline Item DayList::item() const {
		if (this->pointer.number() <= this->size) {
			return this->list_[this->pointer.number()];
		}
		else {
			std::cerr << "-> illegal index!";
			return this->list_[0];
		}
	}

	int DayList::search_by_type(std::string type, int from) const {
		int ans = -1;
		for (int i = from; i < this->size; i++) {
			if (this->at(i).type() == type) {
				ans = i;
				break;
			}
		}

		return ans;
	}



	DayList DayList::get_daylist_from(const std::string URL) {
		DayList list;

		std::ifstream file(URL);
		std::string line;

		int lineCounter = 1;
		while (getline(file, line)) {
			std::string main("");
			std::string type("");
			std::string note("");

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
						std::cerr << "wrong format of file!";
					}//end switch
				}
				else {
					counter = counter + 1;
				}
			}//end for(char c : line)

			list += Item(main, lineCounter++, type, note);

		}//end while(getline(file, line))

		file.close();
		return list;
	}


	int DayList::put_dayList_to(const std::string URL) {
		std::ofstream out(URL);


		out.close();
		return 0;
	}

	
	std::ostream& operator<<(std::ostream& os, const DayList& that) {
		for (int i = 1; i < that.size; i++) {
			os << i << ".  " << that.at(i) << std::endl;
		}

		return os;
	}



}// namespace planner






