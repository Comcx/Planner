// Planner.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "lainlib.h"
#include "Planner.h"

int main(int argc, char *argv[]) {

	bool lain = true; while (lain) {

		planner::Planner test;
		if (argc == 1) {
			test = planner::Planner("C:/Users/HP/Desktop/plan.txt");
		} else {
			test = planner::Planner(argv[1]);
		}
		
		//planner::Planner test("C:/Users/HP/Desktop/plan.txt");
		test.start();
		
		cout << "\nContinue__1，Exit__0\n" << endl;
		cin.clear();
		(cin >> lain).get();
	}
	system("pause");
	return 0;
}
