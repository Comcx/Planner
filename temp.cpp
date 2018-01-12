
#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cctype>
#include <cmath>
#include <time.h>
#include <windows.h>

#include "Item.h"
#include "DayList.h"
#include "Pointer.h"
#include "Planner.h"

#define OK 1
#define ERROR -1
#define TRUE 1
#define FALSE 0
#define STOP 0


//================================================================================================
//Main Function
using std::cout;
using std::cin;
using std::endl;

int main(int argc, char *argv[])
{
	int lain = 1;
	while (lain)
	{
		Planner planner;
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


















