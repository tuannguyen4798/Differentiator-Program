// Laboratory2_group15.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "string.h"
#include "sstream"
#include "Laboratory2_group15.h"

int main(int argc, char *argv[])
{

	switch (argc)
	{
	case 1:
	{
		cout << "s3651585,s3651585@rmit.edu.vn,dat,tran" << endl;
		cout << "s3634951,s3634951@rmit.edu.vn,tuan,nguyen" << endl;
		cout << "s3577794,s3577794@rmit.edu.vn,hoang,le" << endl;
		break;
	}
	case 2:
	{
	term equation;
	equation.myDiff_ = argv[1];
	equation.Split(equation.myDiff_);
	if (equation.Calculate() == true) equation.printList();
	return 0;
	break;
	}
	default:
		cout << "No more than one input is accepted" << endl;
		return (1);
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
