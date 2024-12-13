#pragma once

#include <math.h>
#include <iostream>
#include <string>
#include "TStack.cpp"
enum Operations
{
	tAdd = '+',
	tSub = '-',
	tMult = '*',
	tDiv = '/',
	tPow = '^',
	tLeftBracket = '(',
	tSin = 's',
	tCos = 'c',
	tExp = 'e'
};
class TCalculator 
{
	std::string infix;
	std::string postfix;
	TStack<double> stNum;
	TStack<char> stChar;
public:
	TCalculator() : stNum(TStack<double>()), stChar(TStack<char>()) {};

	double CalcPostfix();
	double Calc();

	int Prior(char op);
	bool Check(std::string str);

	void setInfix(std::string str);
	std::string getInfix();
	void setPostfix();
	std::string getPostfix();
};