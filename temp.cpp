﻿
#include "stdafx.h"
#include "lainlib.h"

#include "Item.h"
#include "DayList.h"
#include "Planner.h"

//================================================================================================
//Main Function
using std::cout;
using std::cin;
using std::endl;

int main(int argc, char *argv[]) {
	
	bool lain = true; while (lain) {
		
		planner::Planner planner("C:/Users/HP/Desktop/main.txt");
		planner.start();


		cout << "\nContinue——1，Exit——0\n" << endl;
		fflush(stdin);
		cin.clear();
		(cin >> lain).get();
	}
	//getchar();
	system("pause");
	return 0;
}

//===============================================================================================
//Function Blocks


















