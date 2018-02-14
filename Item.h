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

#include "lainlib.h"


namespace planner {

	/**
	class Item: one record of the event
	*/

	class Item {

	private:
		string main_;
		int time_;
		string type_;
		string note_;

	public:
		Item() {}
		Item(string main, int time, string type, string note) :
			main_(main), time_(time), type_(type), note_(note) {}
		Item(const Item &that) :
			main_(that.main()), time_(that.time()), type_(that.type()), note_(that.note()) {}
		~Item() {}

		bool operator==(const Item&);
		bool operator!=(const Item &that) { return !(*this == that); }
		friend std::ostream& operator<<(std::ostream& os, const Item& that);

		string main() const { return this->main_; }
		int time() const { return this->time_; }
		string type() const { return this->type_; }
		string note() const { return this->note_; }

		//std::map<string, std::function<int(string)>> change;
		
		int change_main(string main);
		int change_time(int time);
		int change_type(string type);
		int change_note(string note);
		
	};
	

	bool Item::operator==(const Item& that) {
		return this->main_ == that.main() &&
			   this->time_ == that.time() &&
			   this->type_ == that.type() &&
			   this->note_ == that.note();
	}
	
	int Item::change_main(string main) {
		this->main_ = main;
		return this->main_ == main ? 1 : 0;
	}

	int Item::change_time(int time) {
		this->time_ = time;
		return this->time_ == time ? 1 : 0;
	}
	
	int Item::change_type(string type) {
		this->type_ = type;
		return (this->type_ == type) ? 1 : 0;
	}

	int Item::change_note(string note) {
		this->note_ = note;
		return this->note_ == note ? 1 : 0;
	}

	std::ostream& operator<<(std::ostream& os, const Item& that) {
		os << that.main() << " " << that.time() << " " << that.type() << " " << that.note();
		return os;
	}



}// namespace planner




#endif
