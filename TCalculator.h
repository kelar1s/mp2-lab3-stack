#pragma once

#include <math.h>
#include <iostream>
#include <string>
#include "TStack.cpp"

using namespace std;

class TCalculator 
{
	string infix;
	string postfix;
	TStack<double> stNum;
	TStack<char> stChar;
public:
	TCalculator();

	double CalcPostfix();
	//void Calc();

	int Prior(char op);
	bool Check(string str);
	bool CheckOperators(string str);

	void setInfix(string str);
	string getInfix();
	void setPostfix();
	string getPostfix();
};