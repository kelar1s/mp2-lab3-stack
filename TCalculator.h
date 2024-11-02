#pragma once
#include <iostream>
#include <string>
#include "TStack.h"
using namespace std;


class TCalculator {
	string infix;
	string postfix;
	TStack<double> stNum;
	TStack<char> stChar; 
public:
	TCalculator();

	void toPostfix();
	double CalcPostfix();
	
	//void Calc();

	void setInfix();
	string getInfix();
	void setPostfix();
	string getPostfix();
};